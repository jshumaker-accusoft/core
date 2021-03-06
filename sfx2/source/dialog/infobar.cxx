/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <basegfx/polygon/b2dpolygon.hxx>
#include <drawinglayer/primitive2d/polygonprimitive2d.hxx>
#include <drawinglayer/primitive2d/polypolygonprimitive2d.hxx>
#include <drawinglayer/processor2d/baseprocessor2d.hxx>
#include <drawinglayer/processor2d/processorfromoutputdevice.hxx>
#include <sfx2/bindings.hxx>
#include <sfx2/dispatch.hxx>
#include <sfx2/infobar.hxx>
#include <sfx2/objsh.hxx>
#include <sfx2/sfx.hrc>
#include <sfx2/viewsh.hxx>
#include <vcl/svapp.hxx>
#include <vcl/settings.hxx>

using namespace std;
using namespace drawinglayer::geometry;
using namespace drawinglayer::processor2d;
using namespace drawinglayer::primitive2d;
using namespace drawinglayer::attribute;
using namespace drawinglayer::geometry;
using namespace basegfx;

namespace
{

const long INFO_BAR_BASE_HEIGHT = 40;

const BColor constLightColor(1.0, 1.0, 191.0 / 255.0);
const BColor constDarkColor(217.0 / 255.0, 217.0 / 255.0, 78.0 / 255.0);

void lclDetermineLightDarkColor(BColor& rLightColor, BColor& rDarkColor)
{
    const StyleSettings& rSettings = Application::GetSettings().GetStyleSettings();
    if (rSettings.GetHighContrastMode())
    {
        rLightColor = rSettings.GetLightColor().getBColor();
        rDarkColor = rSettings.GetDialogTextColor().getBColor();
    }
    else
    {
        rLightColor = constLightColor;
        rDarkColor = constDarkColor;
    }
}

class SfxCloseButton : public PushButton
{
public:
    SfxCloseButton(vcl::Window* pParent) : PushButton(pParent, 0)
    {}

    virtual ~SfxCloseButton() {}

    virtual void Paint(const Rectangle& rRect) SAL_OVERRIDE;
};

void SfxCloseButton::Paint(const Rectangle&)
{
    const ViewInformation2D aNewViewInfos;
    const unique_ptr<BaseProcessor2D> pProcessor(
        createBaseProcessor2DFromOutputDevice(*this, aNewViewInfos));

    const Rectangle aRect(Point(0, 0), PixelToLogic(GetSizePixel()));

    drawinglayer::primitive2d::Primitive2DSequence aSeq(2);

    BColor aLightColor;
    BColor aDarkColor;
    lclDetermineLightDarkColor(aLightColor, aDarkColor);

    // Light background
    B2DPolygon aPolygon;
    aPolygon.append(B2DPoint(aRect.Left(), aRect.Top()));
    aPolygon.append(B2DPoint(aRect.Right(), aRect.Top()));
    aPolygon.append(B2DPoint(aRect.Right(), aRect.Bottom()));
    aPolygon.append(B2DPoint(aRect.Left(), aRect.Bottom()));
    aPolygon.setClosed(true);

    PolyPolygonColorPrimitive2D* pBack =
        new PolyPolygonColorPrimitive2D(B2DPolyPolygon(aPolygon), aLightColor);
    aSeq[0] = pBack;

    LineAttribute aLineAttribute(aDarkColor, 2.0);

    // Cross
    B2DPolyPolygon aCross;

    B2DPolygon aLine1;
    aLine1.append(B2DPoint(aRect.Left(), aRect.Top()));
    aLine1.append(B2DPoint(aRect.Right(), aRect.Bottom()));
    aCross.append(aLine1);

    B2DPolygon aLine2;
    aLine2.append(B2DPoint(aRect.Right(), aRect.Top()));
    aLine2.append(B2DPoint(aRect.Left(), aRect.Bottom()));
    aCross.append(aLine2);

    PolyPolygonStrokePrimitive2D* pCross =
        new PolyPolygonStrokePrimitive2D(aCross, aLineAttribute, StrokeAttribute());

    aSeq[1] = pCross;

    pProcessor->process(aSeq);
}

} // anonymous namespace

SfxInfoBarWindow::SfxInfoBarWindow(vcl::Window* pParent, const OUString& sId,
       const OUString& sMessage) :
    Window(pParent, 0),
    m_sId(sId),
    m_pMessage(new FixedText(this, 0)),
    m_pCloseBtn(new SfxCloseButton(this)),
    m_aActionBtns()
{
    sal_Int32 nScaleFactor = GetDPIScaleFactor();
    long nWidth = pParent->GetSizePixel().getWidth();
    SetPosSizePixel(Point(0, 0), Size(nWidth, INFO_BAR_BASE_HEIGHT * nScaleFactor));

    m_pMessage->SetText(sMessage);
    m_pMessage->SetBackground(Wallpaper(Color(constLightColor)));
    m_pMessage->Show();

    m_pCloseBtn->SetClickHdl(LINK(this, SfxInfoBarWindow, CloseHandler));
    m_pCloseBtn->Show();

    Resize();
}

SfxInfoBarWindow::~SfxInfoBarWindow()
{}

void SfxInfoBarWindow::addButton(PushButton* pButton) {
    pButton->SetParent(this);
    pButton->Show();
    m_aActionBtns.push_back(pButton);
    Resize();
}

void SfxInfoBarWindow::Paint(const Rectangle& rPaintRect)
{
    const ViewInformation2D aNewViewInfos;
    const unique_ptr<BaseProcessor2D> pProcessor(
        createBaseProcessor2DFromOutputDevice(*this, aNewViewInfos));

    const Rectangle aRect(Point(0, 0), PixelToLogic(GetSizePixel()));

    drawinglayer::primitive2d::Primitive2DSequence aSeq(2);

    BColor aLightColor;
    BColor aDarkColor;
    lclDetermineLightDarkColor(aLightColor, aDarkColor);

    // Update the label background color
    m_pMessage->SetBackground(Wallpaper(Color(aLightColor)));

    // Light background
    B2DPolygon aPolygon;
    aPolygon.append(B2DPoint(aRect.Left(), aRect.Top()));
    aPolygon.append(B2DPoint(aRect.Right(), aRect.Top()));
    aPolygon.append(B2DPoint(aRect.Right(), aRect.Bottom()));
    aPolygon.append(B2DPoint(aRect.Left(), aRect.Bottom()));
    aPolygon.setClosed(true);

    PolyPolygonColorPrimitive2D* pBack =
        new PolyPolygonColorPrimitive2D(B2DPolyPolygon(aPolygon), aLightColor);
    aSeq[0] = pBack;

    LineAttribute aLineAttribute(aDarkColor, 1.0);

    // Bottom dark line
    B2DPolygon aPolygonBottom;
    aPolygonBottom.append(B2DPoint(aRect.Left(), aRect.Bottom()));
    aPolygonBottom.append(B2DPoint(aRect.Right(), aRect.Bottom()));

    PolygonStrokePrimitive2D* pLineBottom =
            new PolygonStrokePrimitive2D (aPolygonBottom, aLineAttribute);

    aSeq[1] = pLineBottom;

    pProcessor->process(aSeq);

    Window::Paint(rPaintRect);
}

void SfxInfoBarWindow::Resize()
{
    sal_Int32 nScaleFactor = GetDPIScaleFactor();

    long nWidth = GetSizePixel().getWidth();
    m_pCloseBtn->SetPosSizePixel(Point(nWidth - 25 * nScaleFactor, 15 * nScaleFactor), Size(10 * nScaleFactor, 10 * nScaleFactor));

    // Reparent the buttons and place them on the right of the bar
    long nX = m_pCloseBtn->GetPosPixel().getX() - 15 * nScaleFactor;
    long nButtonGap = 5 * nScaleFactor;

    boost::ptr_vector<PushButton>::iterator it;
    for (it = m_aActionBtns.begin(); it != m_aActionBtns.end(); ++it)
    {
        long nButtonWidth = it->GetSizePixel().getWidth();
        nX -= nButtonWidth;
        it->SetPosSizePixel(Point(nX, 5 * nScaleFactor), Size(nButtonWidth, 30 * nScaleFactor));
        nX -= nButtonGap;
    }

    Point aMessagePosition(10 * nScaleFactor, 10 * nScaleFactor);
    Size aMessageSize(nX - 20 * nScaleFactor, 20 * nScaleFactor);

    m_pMessage->SetPosSizePixel(aMessagePosition, aMessageSize);
}

IMPL_LINK_NOARG(SfxInfoBarWindow, CloseHandler)
{
    static_cast<SfxInfoBarContainerWindow*>(GetParent())->removeInfoBar(this);
    return 0;
}

SfxInfoBarContainerWindow::SfxInfoBarContainerWindow(SfxInfoBarContainerChild* pChildWin ) :
    Window(pChildWin->GetParent(), 0),
    m_pChildWin(pChildWin),
    m_pInfoBars()
{
}

SfxInfoBarContainerWindow::~SfxInfoBarContainerWindow()
{
}

SfxInfoBarWindow* SfxInfoBarContainerWindow::appendInfoBar(const OUString& sId, const OUString& sMessage)
{
    Size aSize = GetSizePixel();

    SfxInfoBarWindow* pInfoBar = new SfxInfoBarWindow(this, sId, sMessage);
    pInfoBar->SetPosPixel(Point(0, aSize.getHeight()));
    pInfoBar->Show();
    m_pInfoBars.push_back(pInfoBar);

    long nHeight = pInfoBar->GetSizePixel().getHeight();
    aSize.setHeight(aSize.getHeight() + nHeight);
    SetSizePixel(aSize);
    return pInfoBar;
}

SfxInfoBarWindow* SfxInfoBarContainerWindow::getInfoBar(const OUString& sId)
{
    boost::ptr_vector<SfxInfoBarWindow>::iterator it;
    for (it = m_pInfoBars.begin(); it != m_pInfoBars.end(); ++it)
    {
        if (it->getId() == sId)
            return &(*it);
    }
    return NULL;
}

void SfxInfoBarContainerWindow::removeInfoBar(SfxInfoBarWindow* pInfoBar)
{
    boost::ptr_vector<SfxInfoBarWindow>::iterator it;
    for (it = m_pInfoBars.begin(); it != m_pInfoBars.end(); ++it)
    {
        if (pInfoBar == &(*it))
        {
            m_pInfoBars.erase(it);
            break;
        }
    }

    long nY = 0;
    for (it = m_pInfoBars.begin(); it != m_pInfoBars.end(); ++it)
    {
        it->SetPosPixel(Point(0, nY));
        nY += it->GetSizePixel().getHeight();
    }

    Size aSize = GetSizePixel();
    aSize.setHeight(nY);
    SetSizePixel(aSize);

    m_pChildWin->Update();
}

void SfxInfoBarContainerWindow::Resize()
{
    // Only need to change the width of the infobars
    long nWidth = GetSizePixel().getWidth();

    boost::ptr_vector<SfxInfoBarWindow>::iterator it;
    for (it = m_pInfoBars.begin(); it != m_pInfoBars.end(); ++it)
    {
        Size aSize = it->GetSizePixel();
        aSize.setWidth(nWidth);
        it->SetSizePixel(aSize);
        it->Resize();
    }
}

SFX_IMPL_POS_CHILDWINDOW_WITHID(SfxInfoBarContainerChild, SID_INFOBAR, SFX_OBJECTBAR_OBJECT);

SfxInfoBarContainerChild::SfxInfoBarContainerChild( vcl::Window* _pParent, sal_uInt16 nId, SfxBindings* pBindings, SfxChildWinInfo* ) :
    SfxChildWindow(_pParent, nId),
    m_pBindings(pBindings)
{
    pWindow = new SfxInfoBarContainerWindow(this);
    pWindow->SetPosSizePixel(Point(0, 0), Size(_pParent->GetSizePixel().getWidth(), 0));
    pWindow->Show();

    eChildAlignment = SFX_ALIGN_LOWESTTOP;
}

SfxInfoBarContainerChild::~SfxInfoBarContainerChild()
{
}

SfxChildWinInfo SfxInfoBarContainerChild::GetInfo() const
{
    SfxChildWinInfo aInfo = SfxChildWindow::GetInfo();
    return aInfo;
}

void SfxInfoBarContainerChild::Update()
{
    // Refresh the frame to take the infobars container height change into account
    const sal_uInt16 nId = GetChildWindowId();
    SfxViewFrame* pVFrame = m_pBindings->GetDispatcher()->GetFrame();
    pVFrame->ShowChildWindow(nId);

    // Give the focus to the document view
    pVFrame->GetWindow().GrabFocusToDocument();
}

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
