/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <config_folders.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#define LOK_USE_UNSTABLE_API
#include <LibreOfficeKit/LibreOfficeKit.h>
#include <LibreOfficeKit/LibreOfficeKitEnums.h>

#include <tools/errinf.hxx>
#include <osl/file.hxx>
#include <osl/process.h>
#include <rtl/strbuf.hxx>
#include <rtl/bootstrap.hxx>
#include <cppuhelper/bootstrap.hxx>
#include <comphelper/processfactory.hxx>

#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ucb/XUniversalContentBroker.hpp>

#include <vcl/svapp.hxx>
#include <tools/resmgr.hxx>
#include <tools/fract.hxx>
#include <vcl/graphicfilter.hxx>
#include <vcl/sysdata.hxx>
#include <vcl/virdev.hxx>
#include <vcl/ITiledRenderable.hxx>
#include <unotools/syslocaleoptions.hxx>
#include <unotools/mediadescriptor.hxx>
#include <osl/module.hxx>

#include <app.hxx>
#include <salinst.hxx>

#if defined(UNX) && !defined(MACOSX) && !defined(ENABLE_HEADLESS)
// Let's grab the SvpSalInstance and SvpSalVirtualDevice
#include <headless/svpinst.hxx>
#include <headless/svpframe.hxx>
#include <headless/svpvd.hxx>

#include <basebmp/bitmapdevice.hxx>
#endif

#include "../app/cmdlineargs.hxx"
// We also need to hackily be able to start the main libreoffice thread:
#include "../app/sofficemain.h"
#include "../app/officeipcthread.hxx"

using namespace css;
using namespace vcl;
using namespace desktop;
using namespace utl;

using namespace boost;

struct LibLODocument_Impl;
struct LibLibreOffice_Impl;

static LibLibreOffice_Impl *gImpl = NULL;
static weak_ptr< LibreOfficeKitClass > gOfficeClass;
static weak_ptr< LibreOfficeKitDocumentClass > gDocumentClass;

typedef struct
{
    const char *extn;
    const char *filterName;
} ExtensionMap;

// We need a shared_array for passing into the BitmapDevice (via
// VirtualDevice.SetOutputSizePixelScaleOffsetAndBuffer which goes via the
// SvpVirtualDevice, ending up in the basebmp BitmapDevice. However as we're
// given the array externally we can't delete it, and hence need to override
// shared_array's default of deleting its pointer.
template<typename T>
struct NoDelete
{
   void operator()(T* /* p */) {}
};

static const ExtensionMap aWriterExtensionMap[] =
{
    { "doc",   "MS Word 97" },
    { "docx",  "MS Word 2007 XML" },
    { "fodt",  "OpenDocument Text Flat XML" },
    { "html",  "HTML (StarWriter)" },
    { "odt",   "writer8" },
    { "ott",   "writer8_template" },
    { "pdf",   "writer_pdf_Export" },
    { "txt",   "Text" },
    { "xhtml", "XHTML Writer File" },
    { NULL, NULL }
};

static const ExtensionMap aCalcExtensionMap[] =
{
    { "csv",   "Text - txt - csv (StarCalc)" },
    { "fods",  "OpenDocument Spreadsheet Flat XML" },
    { "html",  "HTML (StarCalc)" },
    { "ods",   "calc8" },
    { "ots",   "calc8_template" },
    { "pdf",   "calc_pdf_Export" },
    { "xhtml", "XHTML Calc File" },
    { "xls",   "MS Excel 97" },
    { "xlsx",  "Calc MS Excel 2007 XML" },
    { NULL, NULL }
};

static const ExtensionMap aImpressExtensionMap[] =
{
    { "fodp",  "OpenDocument Presentation Flat XML" },
    { "html",  "impress_html_Export" },
    { "odg",   "impress8_draw" },
    { "odp",   "impress8" },
    { "otp",   "impress8_template" },
    { "pdf",   "impress_pdf_Export" },
    { "potm",  "Impress MS PowerPoint 2007 XML Template" },
    { "pot",   "MS PowerPoint 97 Vorlage" },
    { "pptx",  "Impress MS PowerPoint 2007 XML" },
    { "pps",   "MS PowerPoint 97 Autoplay" },
    { "ppt",   "MS PowerPoint 97" },
    { "svg",   "impress_svg_Export" },
    { "swf",   "impress_flash_Export" },
    { "xhtml", "XHTML Impress File" },
    { NULL, NULL }
};

static const ExtensionMap aDrawExtensionMap[] =
{
    { "fodg",  "draw_ODG_FlatXML" },
    { "html",  "draw_html_Export" },
    { "odg",   "draw8" },
    { "pdf",   "draw_pdf_Export" },
    { "svg",   "draw_svg_Export" },
    { "swf",   "draw_flash_Export" },
    { "xhtml", "XHTML Draw File" },
    { NULL, NULL }
};

static OUString getUString(const char* pString)
{
    if (pString == NULL)
        return OUString();

    OString sString(pString, strlen(pString));
    return OStringToOUString(sString, RTL_TEXTENCODING_UTF8);
}

// Try to convert a relative URL to an absolute one
static OUString getAbsoluteURL(const char* pURL)
{
    OUString aURL( getUString( pURL ) );
    OUString sAbsoluteDocUrl, sWorkingDir, sDocPathUrl;

    // FIXME: this would appear to kill non-file URLs.
    osl_getProcessWorkingDir(&sWorkingDir.pData);
    osl::FileBase::getFileURLFromSystemPath( aURL, sDocPathUrl );
    osl::FileBase::getAbsoluteFileURL(sWorkingDir, sDocPathUrl, sAbsoluteDocUrl);

    return sAbsoluteDocUrl;
}

extern "C"
{

static void doc_destroy(LibreOfficeKitDocument* pThis);
static int  doc_saveAs(LibreOfficeKitDocument* pThis, const char* pUrl, const char* pFormat, const char* pFilterOptions);
static int doc_getDocumentType(LibreOfficeKitDocument* pThis);
static int doc_getParts(LibreOfficeKitDocument* pThis);
static int doc_getPart(LibreOfficeKitDocument* pThis);
static void doc_setPart(LibreOfficeKitDocument* pThis, int nPart);
static char* doc_getPartName(LibreOfficeKitDocument* pThis, int nPart);
static void doc_setPartMode(LibreOfficeKitDocument* pThis, int nPartMode);
void        doc_paintTile(LibreOfficeKitDocument* pThis,
                          unsigned char* pBuffer,
                          const int nCanvasWidth, const int nCanvasHeight,
                          int* pRowStride,
                          const int nTilePosX, const int nTilePosY,
                          const int nTileWidth, const int nTileHeight);
static void doc_getDocumentSize(LibreOfficeKitDocument* pThis,
                                long* pWidth,
                                long* pHeight);
static void doc_initializeForRendering(LibreOfficeKitDocument* pThis);

static void doc_registerCallback(LibreOfficeKitDocument* pThis,
                                LibreOfficeKitCallback pCallback,
                                void* pData);
static void doc_postKeyEvent(LibreOfficeKitDocument* pThis,
                             int nType,
                             int nCharCode,
                             int nKeyCode);
static void doc_postMouseEvent (LibreOfficeKitDocument* pThis,
                                int nType,
                                int nX,
                                int nY,
                                int nCount);
static void doc_setTextSelection (LibreOfficeKitDocument* pThis,
                                  int nType,
                                  int nX,
                                  int nY);

struct LibLODocument_Impl : public _LibreOfficeKitDocument
{
    uno::Reference<css::lang::XComponent> mxComponent;
    shared_ptr< LibreOfficeKitDocumentClass > m_pDocumentClass;

    LibLODocument_Impl(const uno::Reference <css::lang::XComponent> &xComponent) :
        mxComponent( xComponent )
    {
        if (!(m_pDocumentClass = gDocumentClass.lock()))
        {
            m_pDocumentClass.reset(new LibreOfficeKitDocumentClass);

            m_pDocumentClass->nSize = sizeof(LibreOfficeKitDocument);

            m_pDocumentClass->destroy = doc_destroy;
            m_pDocumentClass->saveAs = doc_saveAs;
            m_pDocumentClass->getDocumentType = doc_getDocumentType;
            m_pDocumentClass->getParts = doc_getParts;
            m_pDocumentClass->getPart = doc_getPart;
            m_pDocumentClass->setPart = doc_setPart;
            m_pDocumentClass->getPartName = doc_getPartName;
            m_pDocumentClass->setPartMode = doc_setPartMode;
            m_pDocumentClass->paintTile = doc_paintTile;
            m_pDocumentClass->getDocumentSize = doc_getDocumentSize;
            m_pDocumentClass->initializeForRendering = doc_initializeForRendering;
            m_pDocumentClass->registerCallback = doc_registerCallback;
            m_pDocumentClass->postKeyEvent = doc_postKeyEvent;
            m_pDocumentClass->postMouseEvent = doc_postMouseEvent;
            m_pDocumentClass->setTextSelection = doc_setTextSelection;

            gDocumentClass = m_pDocumentClass;
        }
        pClass = m_pDocumentClass.get();
    }

    ~LibLODocument_Impl()
    {
        mxComponent->dispose();
    }
};

static void doc_destroy(LibreOfficeKitDocument *pThis)
{
    LibLODocument_Impl *pDocument = static_cast<LibLODocument_Impl*>(pThis);
    delete pDocument;
}

static void                    lo_destroy       (LibreOfficeKit* pThis);
static int                     lo_initialize    (LibreOfficeKit* pThis, const char* pInstallPath);
static LibreOfficeKitDocument* lo_documentLoad  (LibreOfficeKit* pThis, const char* pURL);
static char *                  lo_getError      (LibreOfficeKit* pThis);
static LibreOfficeKitDocument* lo_documentLoadWithOptions  (LibreOfficeKit* pThis,
                                                           const char* pURL,
                                                           const char* pOptions);


struct LibLibreOffice_Impl : public _LibreOfficeKit
{
    OUString maLastExceptionMsg;
    shared_ptr< LibreOfficeKitClass > m_pOfficeClass;
    pthread_t maThread;

    LibLibreOffice_Impl()
        : maThread(0)
    {
        if(!(m_pOfficeClass = gOfficeClass.lock())) {
            m_pOfficeClass.reset(new LibreOfficeKitClass);
            m_pOfficeClass->nSize = sizeof(LibreOfficeKitClass);

            m_pOfficeClass->destroy = lo_destroy;
            m_pOfficeClass->documentLoad = lo_documentLoad;
            m_pOfficeClass->getError = lo_getError;
            m_pOfficeClass->documentLoadWithOptions = lo_documentLoadWithOptions;

            gOfficeClass = m_pOfficeClass;
        }

        pClass = m_pOfficeClass.get();
    }
};

namespace
{

ITiledRenderable* getTiledRenderable(LibreOfficeKitDocument* pThis)
{
    LibLODocument_Impl* pDocument = static_cast<LibLODocument_Impl*>(pThis);
    return dynamic_cast<ITiledRenderable*>(pDocument->mxComponent.get());
}

} // anonymous namespace

// Wonder global state ...
static uno::Reference<css::uno::XComponentContext> xContext;
static uno::Reference<css::lang::XMultiServiceFactory> xSFactory;
static uno::Reference<css::lang::XMultiComponentFactory> xFactory;

static LibreOfficeKitDocument* lo_documentLoad(LibreOfficeKit* pThis, const char* pURL)
{
    return lo_documentLoadWithOptions(pThis, pURL, NULL);
}

static LibreOfficeKitDocument* lo_documentLoadWithOptions(LibreOfficeKit* pThis, const char* pURL, const char* pOptions)
{
    LibLibreOffice_Impl* pLib = static_cast<LibLibreOffice_Impl*>(pThis);

    SolarMutexGuard aGuard;

    OUString aURL = getAbsoluteURL(pURL);

    pLib->maLastExceptionMsg.clear();

    if (!xContext.is())
    {
        pLib->maLastExceptionMsg = "ComponentContext is not available!";
        SAL_INFO("lok", "ComponentContext is not available!");
        return NULL;
    }

    uno::Reference<frame::XDesktop2> xComponentLoader = frame::Desktop::create(xContext);

    if (!xComponentLoader.is())
    {
        pLib->maLastExceptionMsg = "ComponentLoader is not available!";
        SAL_INFO("lok", "ComponentLoader is not available!");
        return NULL;
    }

    try
    {
        uno::Sequence<css::beans::PropertyValue> aFilterOptions(1);
        aFilterOptions[0] = css::beans::PropertyValue( OUString("FilterOptions"),
                                                       0,
                                                       uno::makeAny(OUString::createFromAscii(pOptions)),
                                                       beans::PropertyState_DIRECT_VALUE);
        uno::Reference<lang::XComponent> xComponent;
        xComponent = xComponentLoader->loadComponentFromURL(
                                            aURL, OUString("_blank"), 0,
                                            aFilterOptions);

        if (!xComponent.is())
        {
            pLib->maLastExceptionMsg = "loadComponentFromURL returned an empty reference";
            SAL_INFO("lok", "Document can't be loaded - " << pLib->maLastExceptionMsg);
            return NULL;
        }

        return new LibLODocument_Impl(xComponent);

    }
    catch (const uno::Exception& exception)
    {
        pLib->maLastExceptionMsg = exception.Message;
        SAL_INFO("lok", "Document can't be loaded - exception: " << exception.Message);
    }

    return NULL;
}
static int doc_saveAs(LibreOfficeKitDocument* pThis, const char* sUrl, const char* pFormat, const char* pFilterOptions)
{
    LibLODocument_Impl* pDocument = static_cast<LibLODocument_Impl*>(pThis);

    OUString sFormat = getUString(pFormat);
    OUString aURL = getAbsoluteURL(sUrl);

    try
    {
        const ExtensionMap* pMap;

        switch (doc_getDocumentType(pThis))
        {
        case LOK_DOCTYPE_SPREADSHEET:
            pMap = (const ExtensionMap*) aCalcExtensionMap;
            break;
        case LOK_DOCTYPE_PRESENTATION:
            pMap = (const ExtensionMap*) aImpressExtensionMap;
            break;
        case LOK_DOCTYPE_DRAWING:
            pMap = (const ExtensionMap*) aDrawExtensionMap;
            break;
        case LOK_DOCTYPE_TEXT:
            pMap = (const ExtensionMap*) aWriterExtensionMap;
            break;
        case LOK_DOCTYPE_OTHER:
        default:
            return false;
        }

        if (pFormat == NULL)
        {
            // sniff from the extension
            sal_Int32 idx = aURL.lastIndexOf(".");
            if( idx > 0 )
            {
                sFormat = aURL.copy( idx + 1 );
            }
            else
            {
                gImpl->maLastExceptionMsg = "input filename without a suffix";
                return false;
            }
        }

        OUString aFilterName;
        for (sal_Int32 i = 0; pMap[i].extn; ++i)
        {
            if (sFormat.equalsIgnoreAsciiCaseAscii(pMap[i].extn))
            {
                aFilterName = getUString(pMap[i].filterName);
                break;
            }
        }
        if (aFilterName.isEmpty())
        {
            gImpl->maLastExceptionMsg = "no output filter found for provided suffix";
            return false;
        }

        OUString aFilterOptions = getUString(pFilterOptions);

        MediaDescriptor aSaveMediaDescriptor;
        aSaveMediaDescriptor["Overwrite"] <<= sal_True;
        aSaveMediaDescriptor["FilterName"] <<= aFilterName;
        aSaveMediaDescriptor[MediaDescriptor::PROP_FILTEROPTIONS()] <<= aFilterOptions;

        uno::Reference<frame::XStorable> xStorable(pDocument->mxComponent, uno::UNO_QUERY_THROW);
        xStorable->storeToURL(aURL, aSaveMediaDescriptor.getAsConstPropertyValueList());

        return true;
    }
    catch (const uno::Exception& exception)
    {
        gImpl->maLastExceptionMsg = "exception: " + exception.Message;
    }
    return false;
}

static int doc_getDocumentType (LibreOfficeKitDocument* pThis)
{
    LibLODocument_Impl* pDocument = static_cast<LibLODocument_Impl*>(pThis);

    try
    {
        uno::Reference<lang::XServiceInfo> xDocument(pDocument->mxComponent, uno::UNO_QUERY_THROW);

        if (xDocument->supportsService("com.sun.star.sheet.SpreadsheetDocument"))
        {
            return LOK_DOCTYPE_SPREADSHEET;
        }
        else if (xDocument->supportsService("com.sun.star.presentation.PresentationDocument"))
        {
            return LOK_DOCTYPE_PRESENTATION;
        }
        else if (xDocument->supportsService("com.sun.star.drawing.DrawingDocument"))
        {
            return LOK_DOCTYPE_DRAWING;
        }
        else if (xDocument->supportsService("com.sun.star.text.TextDocument"))
        {
            return LOK_DOCTYPE_TEXT;
        }
        else
        {
            gImpl->maLastExceptionMsg = "unknown document type";
        }
    }
    catch (const uno::Exception& exception)
    {
        gImpl->maLastExceptionMsg = "exception: " + exception.Message;
    }
    return LOK_DOCTYPE_OTHER;
}

static int doc_getParts (LibreOfficeKitDocument* pThis)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return 0;
    }

    return pDoc->getParts();
}

static int doc_getPart (LibreOfficeKitDocument* pThis)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return 0;
    }

    return pDoc->getPart();
}

static void doc_setPart(LibreOfficeKitDocument* pThis, int nPart)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return;
    }

    SolarMutexGuard aGuard;
    pDoc->setPart( nPart );
}

static char* doc_getPartName(LibreOfficeKitDocument* pThis, int nPart)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return 0;
    }

    OUString sName = pDoc->getPartName( nPart );
    OString aString = OUStringToOString(sName, RTL_TEXTENCODING_UTF8);
    char* pMemory = (char*) malloc(aString.getLength() + 1);
    strcpy(pMemory, aString.getStr());
    return pMemory;

}

static void doc_setPartMode(LibreOfficeKitDocument* pThis,
                            int nPartMode)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return;
    }

    SolarMutexGuard aGuard;

    int nCurrentPart = pDoc->getPart();

    pDoc->setPartMode(nPartMode);

    // We need to make sure the internal state is updated, just changing the mode
    // might not update the relevant shells (i.e. impress will keep rendering the
    // previous mode unless we do this).
    // TODO: we might want to do this within the relevant components rather than
    // here, but that's also dependent on how we implement embedded object
    // rendering I guess?
    // TODO: we could be clever and e.g. set to 0 when we change to/from
    // embedded object mode, and not when changing between slide/notes/combined
    // modes?
    if ( nCurrentPart < pDoc->getParts() )
    {
        pDoc->setPart( nCurrentPart );
    }
    else
    {
        pDoc->setPart( 0 );
    }
}

void doc_paintTile (LibreOfficeKitDocument* pThis,
                    unsigned char* pBuffer,
                    const int nCanvasWidth, const int nCanvasHeight,
                    int* pRowStride,
                    const int nTilePosX, const int nTilePosY,
                    const int nTileWidth, const int nTileHeight)
{
    SAL_INFO( "lok.tiledrendering", "paintTile: painting [" << nTileWidth << "x" << nTileHeight <<
              "]@(" << nTilePosX << ", " << nTilePosY << ") to [" <<
              nCanvasWidth << "x" << nCanvasHeight << "]px" );

    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return;
    }

    SolarMutexGuard aGuard;

#if defined(UNX) && !defined(MACOSX) && !defined(ENABLE_HEADLESS)

#ifndef IOS
    ImplSVData* pSVData = ImplGetSVData();
    SvpSalInstance* pSalInstance = static_cast< SvpSalInstance* >(pSVData->mpDefInst);
    pSalInstance->setBitCountFormatMapping( 32, ::basebmp::FORMAT_THIRTYTWO_BIT_TC_MASK_RGBA );

    VirtualDevice aDevice(0, Size(1, 1), (sal_uInt16)32);
    boost::shared_array< sal_uInt8 > aBuffer( pBuffer, NoDelete< sal_uInt8 >() );
    aDevice.SetOutputSizePixelScaleOffsetAndBuffer(
                Size(nCanvasWidth, nCanvasHeight), Fraction(1.0), Point(),
                aBuffer, true );

    pDoc->paintTile(aDevice, nCanvasWidth, nCanvasHeight,
                    nTilePosX, nTilePosY, nTileWidth, nTileHeight);

    SvpSalVirtualDevice* pSalDev = static_cast< SvpSalVirtualDevice* >(aDevice.getSalVirtualDevice());
    basebmp::BitmapDeviceSharedPtr pBmpDev = pSalDev->getBitmapDevice();

    *pRowStride = pBmpDev->getScanlineStride();
#else
    SystemGraphicsData aData;
    aData.rCGContext = reinterpret_cast<CGContextRef>(pBuffer);
    // the Size argument is irrelevant, I hope
    VirtualDevice aDevice(&aData, Size(1, 1), (sal_uInt16)0);

    pDoc->paintTile(aDevice, nCanvasWidth, nCanvasHeight,
                    nTilePosX, nTilePosY, nTileWidth, nTileHeight);

    (void) pRowStride;
#endif

    static bool bDebug = getenv("LOK_DEBUG") != 0;
    if (bDebug)
    {
        // Draw a small red rectangle in the top left corner so that it's easy to see where a new tile begins.
        Rectangle aRect(0, 0, 5, 5);
        aRect = aDevice.PixelToLogic(aRect);
        aDevice.Push(PushFlags::FILLCOLOR | PushFlags::LINECOLOR);
        aDevice.SetFillColor(COL_LIGHTRED);
        aDevice.SetLineColor();
        aDevice.DrawRect(aRect);
        aDevice.Pop();
    }

#else
    (void) pBuffer;
    (void) nCanvasWidth;
    (void) nCanvasHeight;
    (void) pRowStride;
    (void) nTilePosX;
    (void) nTilePosY;
    (void) nTileWidth;
    (void) nTileHeight;
#endif
}

static void doc_getDocumentSize(LibreOfficeKitDocument* pThis,
                                long* pWidth,
                                long* pHeight)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (pDoc)
    {
        Size aDocumentSize = pDoc->getDocumentSize();
        *pWidth = aDocumentSize.Width();
        *pHeight = aDocumentSize.Height();
    }
    else
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
    }
}

static void doc_initializeForRendering(LibreOfficeKitDocument* pThis)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (pDoc)
    {
        pDoc->initializeForTiledRendering();
    }
}

static void doc_registerCallback(LibreOfficeKitDocument* pThis,
                                LibreOfficeKitCallback pCallback,
                                void* pData)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return;
    }

    pDoc->registerCallback(pCallback, pData);
}

static void doc_postKeyEvent(LibreOfficeKitDocument* /*pThis*/, int nType, int nCharCode, int nKeyCode)
{
#if defined(UNX) && !defined(MACOSX) && !defined(ENABLE_HEADLESS)
    if (SalFrame *pFocus = SvpSalFrame::GetFocusFrame())
    {
        KeyEvent aEvent(nCharCode, nKeyCode, 0);
        switch (nType)
        {
        case LOK_KEYEVENT_KEYINPUT:
            Application::PostKeyEvent(VCLEVENT_WINDOW_KEYINPUT, pFocus->GetWindow(), &aEvent);
            break;
        case LOK_KEYEVENT_KEYUP:
            Application::PostKeyEvent(VCLEVENT_WINDOW_KEYUP, pFocus->GetWindow(), &aEvent);
            break;
        }
    }
#endif
}

static void doc_postMouseEvent(LibreOfficeKitDocument* pThis, int nType, int nX, int nY, int nCount)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return;
    }

    pDoc->postMouseEvent(nType, nX, nY, nCount);
}

static void doc_setTextSelection(LibreOfficeKitDocument* pThis, int nType, int nX, int nY)
{
    ITiledRenderable* pDoc = getTiledRenderable(pThis);
    if (!pDoc)
    {
        gImpl->maLastExceptionMsg = "Document doesn't support tiled rendering";
        return;
    }

    pDoc->setTextSelection(nType, nX, nY);
}

static char* lo_getError (LibreOfficeKit *pThis)
{
    LibLibreOffice_Impl* pLib = static_cast<LibLibreOffice_Impl*>(pThis);
    OString aString = OUStringToOString(pLib->maLastExceptionMsg, RTL_TEXTENCODING_UTF8);
    char* pMemory = (char*) malloc(aString.getLength() + 1);
    strcpy(pMemory, aString.getStr());
    return pMemory;
}

static void force_c_locale(void)
{
    // force locale (and resource files loaded) to en-US
    OUString aLangISO("en-US");
    LanguageTag aLocale(aLangISO);
    ResMgr::SetDefaultLocale(aLocale);
    SvtSysLocaleOptions aLocalOptions;
    aLocalOptions.SetLocaleConfigString(aLangISO);
    aLocalOptions.SetUILocaleConfigString(aLangISO);
}

static void aBasicErrorFunc(const OUString& rError, const OUString& rAction)
{
    OStringBuffer aBuffer("Unexpected dialog: ");
    aBuffer.append(OUStringToOString(rAction, RTL_TEXTENCODING_ASCII_US));
    aBuffer.append(" Error: ");
    aBuffer.append(OUStringToOString(rError, RTL_TEXTENCODING_ASCII_US));

    fprintf(stderr, "Unexpected basic error dialog '%s'\n", aBuffer.getStr());
}

static bool initialize_uno(const OUString& aAppProgramURL)
{
#ifdef IOS
    // For iOS we already hardocde the inifile as "rc" in the .app directory.
    (void) aAppProgramURL;
#else
    rtl::Bootstrap::setIniFilename(aAppProgramURL + "/" SAL_CONFIGFILE("soffice"));
#endif

    xContext = cppu::defaultBootstrap_InitialComponentContext();
    if (!xContext.is())
    {
        gImpl->maLastExceptionMsg = "XComponentContext could not be created";
        SAL_INFO("lok", "XComponentContext could not be created");
        return false;
    }

    xFactory = xContext->getServiceManager();
    if (!xFactory.is())
    {
        gImpl->maLastExceptionMsg = "XMultiComponentFactory could not be created";
        SAL_INFO("lok", "XMultiComponentFactory could not be created");
        return false;
    }

    xSFactory = uno::Reference<lang::XMultiServiceFactory>(xFactory, uno::UNO_QUERY_THROW);
    if (!xSFactory.is())
    {
        gImpl->maLastExceptionMsg = "XMultiServiceFactory could not be created";
        SAL_INFO("lok", "XMultiServiceFactory could not be created");
        return false;
    }
    comphelper::setProcessServiceFactory(xSFactory);

    SAL_INFO("lok", "Uno initialized  - " <<  xContext.is());

    // set UserInstallation to user profile dir in test/user-template
//    rtl::Bootstrap aDefaultVars;
//    aDefaultVars.set(OUString("UserInstallation"), aAppProgramURL + "../registry" );
    // configmgr setup ?

    return true;
}

static void* lo_startmain(void*)
{
    soffice_main();
    return 0;
}

static bool bInitialized = false;

static int lo_initialize(LibreOfficeKit* pThis, const char* pAppPath)
{
    LibLibreOffice_Impl* pLib = static_cast<LibLibreOffice_Impl*>(pThis);

    if (bInitialized)
        return 1;

    OUString aAppPath;
    if (pAppPath)
    {
        aAppPath = OUString(pAppPath, strlen(pAppPath), RTL_TEXTENCODING_UTF8);
    }
    else
    {
        // Fun conversion dance back and forth between URLs and system paths...
        OUString aAppURL;
        ::osl::Module::getUrlFromAddress( reinterpret_cast< oslGenericFunction >(lo_initialize),
                                          aAppURL);
        osl::FileBase::getSystemPathFromFileURL( aAppURL, aAppPath );
    }

    OUString aAppURL;
    if (osl::FileBase::getFileURLFromSystemPath(aAppPath, aAppURL) != osl::FileBase::E_None)
        return 0;

    try
    {
        SAL_INFO("lok", "Attempting to initalize UNO");
        if (!initialize_uno(aAppURL))
        {
            return false;
        }
        SAL_INFO("lok", "UNO successfully initalized");
        force_c_locale();

        // Force headless -- this is only for bitmap rendering.
        rtl::Bootstrap::set("SAL_USE_VCLPLUGIN", "svp");

        // We specifically need to make sure we have the "headless"
        // command arg set (various code specifically checks via
        // CommandLineArgs):
        desktop::Desktop::GetCommandLineArgs().setHeadless();

        Application::EnableHeadlessMode(true);

        // We could use InitVCL() here -- and used to before using soffice_main,
        // however that now deals with the initialisation for us (and it's not
        // possible to try to set up VCL twice.

        // Instead VCL init is done for us by soffice_main in a separate thread,
        // however we specifically can't proceed until this setup is complete
        // (or you get segfaults trying to use VCL and/or deadlocks due to other
        //  setup within soffice_main). Specifically the various Application::
        // functions depend on VCL being ready -- the deadlocks would happen
        // if you try to use loadDocument too early.

        // The OfficeIPCThread is specifically set to be read when all the other
        // init in Desktop::Main (run from soffice_main) is done. We can "enable"
        // the Thread from wherever (it's done again in Desktop::Main), and can
        // then use it to wait until we're definitely ready to continue.

        SAL_INFO("lok", "Enabling OfficeIPCThread");
        OfficeIPCThread::EnableOfficeIPCThread();
        SAL_INFO("lok", "Starting soffice_main");
        pthread_create(&(pLib->maThread), 0, lo_startmain, NULL);
        SAL_INFO("lok", "Waiting for OfficeIPCThread");
        OfficeIPCThread::WaitForReady();
        SAL_INFO("lok", "OfficeIPCThread ready -- continuing");

        // If the Thread has been disabled again that indicates that a
        // restart is required (or in any case we don't have a useable
        // process around).
        if (!OfficeIPCThread::IsEnabled())
        {
            fprintf(stderr, "LOK init failed -- restart required\n");
            return false;
        }

        ErrorHandler::RegisterDisplay(aBasicErrorFunc);

        SAL_INFO("lok", "LOK Initialized");
        bInitialized = true;
    }
    catch (css::uno::Exception& exception)
    {
        fprintf(stderr, "Bootstrapping exception '%s'\n",
                 OUStringToOString(exception.Message, RTL_TEXTENCODING_UTF8).getStr());
    }
    return bInitialized;
}

// Undo our clever trick of having SAL_DLLPUBLIC_EXPORT actually not
// meaning what is says in for the DISABLE_DYNLOADING case. See
// <sal/types.h>. Normally, when building just one big dylib (Android)
// or executable (iOS), most of our "public" symbols don't need to be
// visible outside that resulting dylib/executable. But
// libreofficekit_hook must be exported for dlsym() to find it,
// though, at least on iOS.

#if defined(__GNUC__) && defined(HAVE_GCC_VISIBILITY_FEATURE) && defined(DISABLE_DYNLOADING)
__attribute__ ((visibility("default")))
#else
SAL_DLLPUBLIC_EXPORT
#endif
LibreOfficeKit *libreofficekit_hook(const char* install_path)
{
    if (!gImpl)
    {
        SAL_INFO("lok", "Create libreoffice object");

        gImpl = new LibLibreOffice_Impl();
        if (!lo_initialize(gImpl, install_path))
        {
            lo_destroy(gImpl);
        }
    }
    return static_cast<LibreOfficeKit*>(gImpl);
}

static void lo_destroy(LibreOfficeKit* pThis)
{
    LibLibreOffice_Impl* pLib = static_cast<LibLibreOffice_Impl*>(pThis);
    gImpl = NULL;

    SAL_INFO("lok", "LO Destroy");

    Application::Quit();
    pthread_join(pLib->maThread, NULL);

    delete pLib;
    bInitialized = false;
    SAL_INFO("lok", "LO Destroy Done");
}

}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
