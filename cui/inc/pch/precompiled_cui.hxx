/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

/*
 This file has been autogenerated by update_pch.sh . It is possible to edit it
 manually (such as when an include file has been moved/renamed/removed. All such
 manual changes will be rewritten by the next run of update_pch.sh (which presumably
 also fixes all possible problems, so it's usually better to use it).
*/

#include "com/sun/star/system/SystemShellExecute.hpp"
#include "com/sun/star/system/SystemShellExecuteFlags.hpp"
#include "com/sun/star/task/PasswordContainer.hpp"
#include "com/sun/star/task/XPasswordContainer2.hpp"
#include "com/sun/star/ui/dialogs/TemplateDescription.hpp"
#include "comphelper/anytostring.hxx"
#include "cppuhelper/bootstrap.hxx"
#include "cppuhelper/exc_hlp.hxx"
#include "cppuhelper/factory.hxx"
#include "editeng/flstitem.hxx"
#include "editeng/fontitem.hxx"
#include "editeng/lineitem.hxx"
#include "sal/config.h"
#include "sal/types.h"
#include "sfx2/opengrf.hxx"
#include "svtools/restartdialog.hxx"
#include "svtools/svlbitm.hxx"
#include "svtools/treelistentry.hxx"
#include "svtools/viewdataentry.hxx"
#include "svx/anchorid.hxx"
#include "svx/dlgutil.hxx"
#include "svx/drawitem.hxx"
#include "svx/flagsdef.hxx"
#include "svx/globl3d.hxx"
#include "svx/ofaitem.hxx"
#include "svx/svdmodel.hxx"
#include "svx/svxgrahicitem.hxx"
#include "svx/xattr.hxx"
#include "svx/xoutbmp.hxx"
#include "ucbhelper/content.hxx"
#include <algorithm>
#include <avmedia/mediawindow.hxx>
#include <basegfx/color/bcolortools.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>
#include <basegfx/matrix/b2dhommatrixtools.hxx>
#include <basegfx/numeric/ftools.hxx>
#include <basegfx/polygon/b2dpolygon.hxx>
#include <basegfx/polygon/b2dpolygontools.hxx>
#include <basegfx/polygon/b2dpolypolygontools.hxx>
#include <basegfx/range/b2drange.hxx>
#include <basic/basicmanagerrepository.hxx>
#include <basic/basmgr.hxx>
#include <basic/sbmod.hxx>
#include <basic/sbstar.hxx>
#include <basic/sbx.hxx>
#include <basic/sbxmeth.hxx>
#include <bitset>
#include <boost/make_shared.hpp>
#include <boost/ref.hpp>
#include <boost/scoped_array.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <cassert>
#include <cmath>
#include <com/sun/star/awt/ContainerWindowProvider.hpp>
#include <com/sun/star/awt/KeyModifier.hpp>
#include <com/sun/star/awt/PosSize.hpp>
#include <com/sun/star/awt/XBitmap.hpp>
#include <com/sun/star/awt/XContainerWindowEventHandler.hpp>
#include <com/sun/star/awt/XControl.hpp>
#include <com/sun/star/awt/XWindow.hpp>
#include <com/sun/star/beans/NamedValue.hpp>
#include <com/sun/star/beans/Property.hpp>
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/beans/XProperty.hpp>
#include <com/sun/star/beans/XPropertyAccess.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/beans/XPropertyState.hpp>
#include <com/sun/star/configuration/theDefaultProvider.hpp>
#include <com/sun/star/container/NoSuchElementException.hpp>
#include <com/sun/star/container/XChild.hpp>
#include <com/sun/star/container/XContainerQuery.hpp>
#include <com/sun/star/container/XContentEnumerationAccess.hpp>
#include <com/sun/star/container/XEnumeration.hpp>
#include <com/sun/star/container/XEnumerationAccess.hpp>
#include <com/sun/star/container/XHierarchicalName.hpp>
#include <com/sun/star/container/XHierarchicalNameAccess.hpp>
#include <com/sun/star/container/XIndexAccess.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/container/XNameContainer.hpp>
#include <com/sun/star/container/XNameReplace.hpp>
#include <com/sun/star/container/XSet.hpp>
#include <com/sun/star/datatransfer/XTransferable.hpp>
#include <com/sun/star/datatransfer/clipboard/XClipboard.hpp>
#include <com/sun/star/document/XEmbeddedScripts.hpp>
#include <com/sun/star/document/XEventsSupplier.hpp>
#include <com/sun/star/document/XLinkTargetSupplier.hpp>
#include <com/sun/star/document/XScriptInvocationContext.hpp>
#include <com/sun/star/drawing/FillStyle.hpp>
#include <com/sun/star/embed/Aspects.hpp>
#include <com/sun/star/embed/ElementModes.hpp>
#include <com/sun/star/embed/EmbedStates.hpp>
#include <com/sun/star/embed/FileSystemStorageFactory.hpp>
#include <com/sun/star/embed/MSOLEObjectSystemCreator.hpp>
#include <com/sun/star/embed/StorageFactory.hpp>
#include <com/sun/star/embed/XInsertObjectDialog.hpp>
#include <com/sun/star/embed/XTransactedObject.hpp>
#include <com/sun/star/form/XReset.hpp>
#include <com/sun/star/frame/Desktop.hpp>
#include <com/sun/star/frame/DispatchInformation.hpp>
#include <com/sun/star/frame/FrameSearchFlag.hpp>
#include <com/sun/star/frame/ModuleManager.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/frame/XController.hpp>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/frame/XDispatchInformationProvider.hpp>
#include <com/sun/star/frame/XDispatchProvider.hpp>
#include <com/sun/star/frame/XFrame.hpp>
#include <com/sun/star/frame/XFrames.hpp>
#include <com/sun/star/frame/XFramesSupplier.hpp>
#include <com/sun/star/frame/XLayoutManager.hpp>
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/frame/XModuleManager.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/frame/theGlobalEventBroadcaster.hpp>
#include <com/sun/star/frame/theUICommandDescription.hpp>
#include <com/sun/star/geometry/RealRectangle2D.hpp>
#include <com/sun/star/graphic/GraphicProvider.hpp>
#include <com/sun/star/i18n/CollatorOptions.hpp>
#include <com/sun/star/i18n/ScriptType.hpp>
#include <com/sun/star/i18n/TextConversionOption.hpp>
#include <com/sun/star/i18n/TransliterationModules.hpp>
#include <com/sun/star/i18n/XForbiddenCharacters.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <com/sun/star/lang/Locale.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XInitialization.hpp>
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XServiceDisplayName.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/linguistic2/ConversionDictionaryList.hpp>
#include <com/sun/star/linguistic2/ConversionDictionaryType.hpp>
#include <com/sun/star/linguistic2/ConversionDirection.hpp>
#include <com/sun/star/linguistic2/DictionaryListEvent.hpp>
#include <com/sun/star/linguistic2/DictionaryListEventFlags.hpp>
#include <com/sun/star/linguistic2/LinguProperties.hpp>
#include <com/sun/star/linguistic2/LinguServiceManager.hpp>
#include <com/sun/star/linguistic2/SpellFailure.hpp>
#include <com/sun/star/linguistic2/XAvailableLocales.hpp>
#include <com/sun/star/linguistic2/XDictionaryList.hpp>
#include <com/sun/star/linguistic2/XDictionaryListEventListener.hpp>
#include <com/sun/star/linguistic2/XHyphenator.hpp>
#include <com/sun/star/linguistic2/XMeaning.hpp>
#include <com/sun/star/linguistic2/XProofreader.hpp>
#include <com/sun/star/linguistic2/XSpellAlternatives.hpp>
#include <com/sun/star/linguistic2/XSpellChecker.hpp>
#include <com/sun/star/linguistic2/XThesaurus.hpp>
#include <com/sun/star/loader/CannotActivateFactoryException.hpp>
#include <com/sun/star/mozilla/MozillaBootstrap.hpp>
#include <com/sun/star/office/Quickstart.hpp>
#include <com/sun/star/plugin/PluginDescription.hpp>
#include <com/sun/star/plugin/PluginManager.hpp>
#include <com/sun/star/plugin/XPluginManager.hpp>
#include <com/sun/star/registry/XRegistryKey.hpp>
#include <com/sun/star/script/XInvocation.hpp>
#include <com/sun/star/script/browse/BrowseNodeFactoryViewTypes.hpp>
#include <com/sun/star/script/browse/BrowseNodeTypes.hpp>
#include <com/sun/star/script/browse/XBrowseNode.hpp>
#include <com/sun/star/script/browse/XBrowseNodeFactory.hpp>
#include <com/sun/star/script/browse/theBrowseNodeFactory.hpp>
#include <com/sun/star/script/provider/ScriptErrorRaisedException.hpp>
#include <com/sun/star/script/provider/ScriptExceptionRaisedException.hpp>
#include <com/sun/star/script/provider/ScriptFrameworkErrorType.hpp>
#include <com/sun/star/script/provider/XScriptProvider.hpp>
#include <com/sun/star/script/provider/XScriptProviderSupplier.hpp>
#include <com/sun/star/sdb/DatabaseContext.hpp>
#include <com/sun/star/sdbc/DriverManager.hpp>
#include <com/sun/star/sdbc/XResultSet.hpp>
#include <com/sun/star/sdbc/XRow.hpp>
#include <com/sun/star/security/DocumentDigitalSignatures.hpp>
#include <com/sun/star/setup/UpdateCheck.hpp>
#include <com/sun/star/setup/UpdateCheckConfig.hpp>
#include <com/sun/star/smarttags/XSmartTagAction.hpp>
#include <com/sun/star/smarttags/XSmartTagRecognizer.hpp>
#include <com/sun/star/style/NumberingType.hpp>
#include <com/sun/star/style/XStyleFamiliesSupplier.hpp>
#include <com/sun/star/system/SystemShellExecute.hpp>
#include <com/sun/star/system/SystemShellExecuteFlags.hpp>
#include <com/sun/star/task/InteractionHandler.hpp>
#include <com/sun/star/task/PasswordContainer.hpp>
#include <com/sun/star/task/UrlRecord.hpp>
#include <com/sun/star/task/XPasswordContainer2.hpp>
#include <com/sun/star/text/DefaultNumberingProvider.hpp>
#include <com/sun/star/text/HoriOrientation.hpp>
#include <com/sun/star/text/RelOrientation.hpp>
#include <com/sun/star/text/TextContentAnchorType.hpp>
#include <com/sun/star/text/VertOrientation.hpp>
#include <com/sun/star/text/XDefaultNumberingProvider.hpp>
#include <com/sun/star/text/XNumberingFormatter.hpp>
#include <com/sun/star/text/XNumberingTypeInfo.hpp>
#include <com/sun/star/ucb/CommandAbortedException.hpp>
#include <com/sun/star/ucb/SimpleFileAccess.hpp>
#include <com/sun/star/ucb/XContentAccess.hpp>
#include <com/sun/star/ucb/XContentProvider.hpp>
#include <com/sun/star/ui/GlobalAcceleratorConfiguration.hpp>
#include <com/sun/star/ui/ImageManager.hpp>
#include <com/sun/star/ui/ImageType.hpp>
#include <com/sun/star/ui/ItemStyle.hpp>
#include <com/sun/star/ui/ItemType.hpp>
#include <com/sun/star/ui/UIConfigurationManager.hpp>
#include <com/sun/star/ui/UIElementType.hpp>
#include <com/sun/star/ui/XModuleUIConfigurationManager.hpp>
#include <com/sun/star/ui/XUIConfiguration.hpp>
#include <com/sun/star/ui/XUIConfigurationListener.hpp>
#include <com/sun/star/ui/XUIConfigurationManager.hpp>
#include <com/sun/star/ui/XUIConfigurationManagerSupplier.hpp>
#include <com/sun/star/ui/XUIConfigurationPersistence.hpp>
#include <com/sun/star/ui/XUIConfigurationStorage.hpp>
#include <com/sun/star/ui/XUIElement.hpp>
#include <com/sun/star/ui/dialogs/ExecutableDialogResults.hpp>
#include <com/sun/star/ui/dialogs/ExtendedFilePickerElementIds.hpp>
#include <com/sun/star/ui/dialogs/FilePicker.hpp>
#include <com/sun/star/ui/dialogs/FolderPicker.hpp>
#include <com/sun/star/ui/dialogs/TemplateDescription.hpp>
#include <com/sun/star/ui/dialogs/XAsynchronousExecutableDialog.hpp>
#include <com/sun/star/ui/dialogs/XExecutableDialog.hpp>
#include <com/sun/star/ui/dialogs/XFilePicker.hpp>
#include <com/sun/star/ui/dialogs/XFilePickerControlAccess.hpp>
#include <com/sun/star/ui/dialogs/XFilterManager.hpp>
#include <com/sun/star/ui/theModuleUIConfigurationManagerSupplier.hpp>
#include <com/sun/star/ui/theUICategoryDescription.hpp>
#include <com/sun/star/ui/theWindowStateConfiguration.hpp>
#include <com/sun/star/uno/Any.h>
#include <com/sun/star/uno/Any.hxx>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Reference.hxx>
#include <com/sun/star/uno/RuntimeException.hpp>
#include <com/sun/star/uno/Sequence.h>
#include <com/sun/star/uno/Sequence.hxx>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/util/URLTransformer.hpp>
#include <com/sun/star/util/XChangesBatch.hpp>
#include <com/sun/star/util/XFlushable.hpp>
#include <com/sun/star/util/XURLTransformer.hpp>
#include <com/sun/star/util/thePathSettings.hpp>
#include <com/sun/star/xml/sax/Parser.hpp>
#include <com/sun/star/xml/sax/XParser.hpp>
#include <comphelper/anytostring.hxx>
#include <comphelper/broadcasthelper.hxx>
#include <comphelper/classids.hxx>
#include <comphelper/configuration.hxx>
#include <comphelper/docpasswordrequest.hxx>
#include <comphelper/documentinfo.hxx>
#include <comphelper/extract.hxx>
#include <comphelper/getexpandeduri.hxx>
#include <comphelper/namedvaluecollection.hxx>
#include <comphelper/processfactory.hxx>
#include <comphelper/proparrhlp.hxx>
#include <comphelper/propertycontainer.hxx>
#include <comphelper/random.hxx>
#include <comphelper/seqstream.hxx>
#include <comphelper/sequence.hxx>
#include <comphelper/sequenceashashmap.hxx>
#include <comphelper/string.hxx>
#include <comphelper/types.hxx>
#include <comphelper/uno3.hxx>
#include <config_buildid.h>
#include <config_features.h>
#include <config_folders.h>
#include <config_vclplug.h>
#include <cppuhelper/compbase4.hxx>
#include <cppuhelper/exc_hlp.hxx>
#include <cppuhelper/implbase1.hxx>
#include <cppuhelper/implementationentry.hxx>
#include <cppuhelper/supportsservice.hxx>
#include <cstddef>
#include <editeng/acorrcfg.hxx>
#include <editeng/adjustitem.hxx>
#include <editeng/autokernitem.hxx>
#include <editeng/blinkitem.hxx>
#include <editeng/boxitem.hxx>
#include <editeng/brushitem.hxx>
#include <editeng/charhiddenitem.hxx>
#include <editeng/charreliefitem.hxx>
#include <editeng/charrotateitem.hxx>
#include <editeng/charscaleitem.hxx>
#include <editeng/cmapitem.hxx>
#include <editeng/colritem.hxx>
#include <editeng/contouritem.hxx>
#include <editeng/crossedoutitem.hxx>
#include <editeng/eerdll.hxx>
#include <editeng/emphasismarkitem.hxx>
#include <editeng/escapementitem.hxx>
#include <editeng/fhgtitem.hxx>
#include <editeng/flstitem.hxx>
#include <editeng/fontitem.hxx>
#include <editeng/formatbreakitem.hxx>
#include <editeng/frmdiritem.hxx>
#include <editeng/hyphenzoneitem.hxx>
#include <editeng/justifyitem.hxx>
#include <editeng/keepitem.hxx>
#include <editeng/kernitem.hxx>
#include <editeng/langitem.hxx>
#include <editeng/lrspitem.hxx>
#include <editeng/lspcitem.hxx>
#include <editeng/numitem.hxx>
#include <editeng/optitems.hxx>
#include <editeng/orphitem.hxx>
#include <editeng/paperinf.hxx>
#include <editeng/paravertalignitem.hxx>
#include <editeng/pbinitem.hxx>
#include <editeng/pgrditem.hxx>
#include <editeng/pmdlitem.hxx>
#include <editeng/postitem.hxx>
#include <editeng/prszitem.hxx>
#include <editeng/shaditem.hxx>
#include <editeng/shdditem.hxx>
#include <editeng/sizeitem.hxx>
#include <editeng/spltitem.hxx>
#include <editeng/splwrap.hxx>
#include <editeng/svxacorr.hxx>
#include <editeng/svxenum.hxx>
#include <editeng/tstpitem.hxx>
#include <editeng/twolinesitem.hxx>
#include <editeng/udlnitem.hxx>
#include <editeng/ulspitem.hxx>
#include <editeng/unolingu.hxx>
#include <editeng/wghtitem.hxx>
#include <editeng/widwitem.hxx>
#include <editeng/writingmodeitem.hxx>
#include <editeng/wrlmitem.hxx>
#include <i18nlangtag/lang.h>
#include <i18nlangtag/languagetag.hxx>
#include <i18nlangtag/mslangid.hxx>
#include <i18nutil/unicode.hxx>
#include <iostream>
#include <limits>
#include <linguistic/lngprops.hxx>
#include <linguistic/misc.hxx>
#include <map>
#include <memory>
#include <officecfg/Office/Common.hxx>
#include <officecfg/Office/OptionsDialog.hxx>
#include <osl/diagnose.h>
#include <osl/file.hxx>
#include <osl/module.hxx>
#include <osl/mutex.hxx>
#include <osl/process.h>
#include <osl/security.hxx>
#include <osl/thread.h>
#include <rtl/bootstrap.hxx>
#include <rtl/math.hxx>
#include <rtl/strbuf.hxx>
#include <rtl/textenc.h>
#include <rtl/ustrbuf.hxx>
#include <rtl/ustring.hxx>
#include <sal/config.h>
#include <sal/macros.h>
#include <sal/types.h>
#include <sax/tools/converter.hxx>
#include <set>
#include <sfx2/app.hxx>
#include <sfx2/basedlgs.hxx>
#include <sfx2/bindings.hxx>
#include <sfx2/dialoghelper.hxx>
#include <sfx2/dispatch.hxx>
#include <sfx2/docfac.hxx>
#include <sfx2/docfile.hxx>
#include <sfx2/docfilt.hxx>
#include <sfx2/evntconf.hxx>
#include <sfx2/fcontnr.hxx>
#include <sfx2/filedlghelper.hxx>
#include <sfx2/frame.hxx>
#include <sfx2/frmdescr.hxx>
#include <sfx2/htmlmode.hxx>
#include <sfx2/imgmgr.hxx>
#include <sfx2/itemconnect.hxx>
#include <sfx2/linkmgr.hxx>
#include <sfx2/linksrc.hxx>
#include <sfx2/lnkbase.hxx>
#include <sfx2/minfitem.hxx>
#include <sfx2/mnumgr.hxx>
#include <sfx2/module.hxx>
#include <sfx2/msg.hxx>
#include <sfx2/msgpool.hxx>
#include <sfx2/objsh.hxx>
#include <sfx2/opengrf.hxx>
#include <sfx2/printer.hxx>
#include <sfx2/printopt.hxx>
#include <sfx2/request.hxx>
#include <sfx2/sfxcommands.h>
#include <sfx2/sfxdefs.hxx>
#include <sfx2/sfxdlg.hxx>
#include <sfx2/sfxresid.hxx>
#include <sfx2/sfxuno.hxx>
#include <sfx2/shell.hxx>
#include <sfx2/tabdlg.hxx>
#include <sfx2/tplpitem.hxx>
#include <sfx2/viewfrm.hxx>
#include <sfx2/viewsh.hxx>
#include <sfx2/zoomitem.hxx>
#include <sot/exchange.hxx>
#include <sot/formats.hxx>
#include <sot/stg.hxx>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <svl/adrparse.hxx>
#include <svl/aeitem.hxx>
#include <svl/asiancfg.hxx>
#include <svl/cjkoptions.hxx>
#include <svl/cntwall.hxx>
#include <svl/ctloptions.hxx>
#include <svl/currencytable.hxx>
#include <svl/eitem.hxx>
#include <svl/filenotation.hxx>
#include <svl/flagitem.hxx>
#include <svl/ilstitem.hxx>
#include <svl/int64item.hxx>
#include <svl/intitem.hxx>
#include <svl/itemiter.hxx>
#include <svl/itempool.hxx>
#include <svl/itemset.hxx>
#include <svl/languageoptions.hxx>
#include <svl/lngmisc.hxx>
#include <svl/macitem.hxx>
#include <svl/ownlist.hxx>
#include <svl/rectitem.hxx>
#include <svl/slstitm.hxx>
#include <svl/srchitem.hxx>
#include <svl/stritem.hxx>
#include <svl/style.hxx>
#include <svl/szitem.hxx>
#include <svl/undo.hxx>
#include <svl/urihelper.hxx>
#include <svl/urlbmk.hxx>
#include <svl/whiter.hxx>
#include <svl/zforlist.hxx>
#include <svtools/acceleratorexecute.hxx>
#include <svtools/accessibilityoptions.hxx>
#include <svtools/apearcfg.hxx>
#include <svtools/colorcfg.hxx>
#include <svtools/colrdlg.hxx>
#include <svtools/ctrlbox.hxx>
#include <svtools/ctrltool.hxx>
#include <svtools/editbrowsebox.hxx>
#include <svtools/extcolorcfg.hxx>
#include <svtools/fontsubstconfig.hxx>
#include <svtools/grfmgr.hxx>
#include <svtools/headbar.hxx>
#include <svtools/helpopt.hxx>
#include <svtools/htmlcfg.hxx>
#include <svtools/imagemgr.hxx>
#include <svtools/imapcirc.hxx>
#include <svtools/imappoly.hxx>
#include <svtools/imaprect.hxx>
#include <svtools/insdlg.hxx>
#include <svtools/langhelp.hxx>
#include <svtools/langtab.hxx>
#include <svtools/menuoptions.hxx>
#include <svtools/miscopt.hxx>
#include <svtools/optionsdrawinglayer.hxx>
#include <svtools/ruler.hxx>
#include <svtools/soerr.hxx>
#include <svtools/stdctrl.hxx>
#include <svtools/svlbitm.hxx>
#include <svtools/svmedit.hxx>
#include <svtools/svtabbx.hxx>
#include <svtools/transfer.hxx>
#include <svtools/treelistbox.hxx>
#include <svtools/treelistentry.hxx>
#include <svtools/unitconv.hxx>
#include <svx/SmartTagMgr.hxx>
#include <svx/SpellDialogChildWindow.hxx>
#include <svx/algitem.hxx>
#include <svx/anchorid.hxx>
#include <svx/connctrl.hxx>
#include <svx/dialmgr.hxx>
#include <svx/dlgutil.hxx>
#include <svx/drawitem.hxx>
#include <svx/flagsdef.hxx>
#include <svx/fmsrccfg.hxx>
#include <svx/fmsrcimp.hxx>
#include <svx/frmsel.hxx>
#include <svx/gallery.hxx>
#include <svx/gallery1.hxx>
#include <svx/galtheme.hxx>
#include <svx/grfcrop.hxx>
#include <svx/langbox.hxx>
#include <svx/measctrl.hxx>
#include <svx/numfmtsh.hxx>
#include <svx/numinf.hxx>
#include <svx/numvset.hxx>
#include <svx/ofaitem.hxx>
#include <svx/pageitem.hxx>
#include <svx/postattr.hxx>
#include <svx/rectenum.hxx>
#include <svx/rotmodit.hxx>
#include <svx/sderitm.hxx>
#include <svx/sdtagitm.hxx>
#include <svx/sdtaitm.hxx>
#include <svx/sdtcfitm.hxx>
#include <svx/sdtditm.hxx>
#include <svx/sdtfsitm.hxx>
#include <svx/srchdlg.hxx>
#include <svx/strarray.hxx>
#include <svx/svdattr.hxx>
#include <svx/svddef.hxx>
#include <svx/svdmark.hxx>
#include <svx/svdmodel.hxx>
#include <svx/svdobj.hxx>
#include <svx/svdocirc.hxx>
#include <svx/svdoedge.hxx>
#include <svx/svdomeas.hxx>
#include <svx/svdopath.hxx>
#include <svx/svdorect.hxx>
#include <svx/svdotext.hxx>
#include <svx/svdpage.hxx>
#include <svx/svdpagv.hxx>
#include <svx/svdview.hxx>
#include <svx/svxdlg.hxx>
#include <svx/svxerr.hxx>
#include <svx/swframevalidation.hxx>
#include <svx/sxcaitm.hxx>
#include <svx/sxcecitm.hxx>
#include <svx/sxcgitm.hxx>
#include <svx/sxcllitm.hxx>
#include <svx/sxctitm.hxx>
#include <svx/sxekitm.hxx>
#include <svx/sxelditm.hxx>
#include <svx/sxenditm.hxx>
#include <svx/sxmbritm.hxx>
#include <svx/sxmfsitm.hxx>
#include <svx/sxmlhitm.hxx>
#include <svx/sxmsuitm.hxx>
#include <svx/sxmtfitm.hxx>
#include <svx/sxmtpitm.hxx>
#include <svx/sxmtritm.hxx>
#include <svx/sxmuitm.hxx>
#include <svx/transfrmhelper.hxx>
#include <svx/ucsubset.hxx>
#include <svx/unobrushitemhelper.hxx>
#include <svx/viewlayoutitem.hxx>
#include <svx/xdef.hxx>
#include <svx/xfillit.hxx>
#include <svx/xflbckit.hxx>
#include <svx/xfltrit.hxx>
#include <svx/xlineit.hxx>
#include <svx/xlineit0.hxx>
#include <svx/xoutbmp.hxx>
#include <svx/xpool.hxx>
#include <svx/xtable.hxx>
#include <svx/zoom_def.hxx>
#include <time.h>
#include <toolkit/helper/vclunohelper.hxx>
#include <tools/config.hxx>
#include <tools/date.hxx>
#include <tools/debug.hxx>
#include <tools/diagnose_ex.h>
#include <tools/fract.hxx>
#include <tools/mapunit.hxx>
#include <tools/rc.h>
#include <tools/rcid.h>
#include <tools/resary.hxx>
#include <tools/shl.hxx>
#include <tools/stream.hxx>
#include <tools/time.hxx>
#include <tools/urlobj.hxx>
#include <ucbhelper/content.hxx>
#include <unotools/bootstrap.hxx>
#include <unotools/charclass.hxx>
#include <unotools/collatorwrapper.hxx>
#include <unotools/compatibility.hxx>
#include <unotools/configitem.hxx>
#include <unotools/configmgr.hxx>
#include <unotools/confignode.hxx>
#include <unotools/defaultoptions.hxx>
#include <unotools/dynamicmenuoptions.hxx>
#include <unotools/eventcfg.hxx>
#include <unotools/extendedsecurityoptions.hxx>
#include <unotools/fltrcfg.hxx>
#include <unotools/fontoptions.hxx>
#include <unotools/intlwrapper.hxx>
#include <unotools/lingucfg.hxx>
#include <unotools/linguprops.hxx>
#include <unotools/localedatawrapper.hxx>
#include <unotools/localfilehelper.hxx>
#include <unotools/misccfg.hxx>
#include <unotools/moduleoptions.hxx>
#include <unotools/optionsdlg.hxx>
#include <unotools/pathoptions.hxx>
#include <unotools/printwarningoptions.hxx>
#include <unotools/saveopt.hxx>
#include <unotools/searchopt.hxx>
#include <unotools/securityoptions.hxx>
#include <unotools/syslocale.hxx>
#include <unotools/syslocaleoptions.hxx>
#include <unotools/ucbhelper.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <unotools/useroptions.hxx>
#include <unotools/viewoptions.hxx>
#include <utility>
#include <vcl/IconThemeInfo.hxx>
#include <vcl/bitmap.hxx>
#include <vcl/bmpacc.hxx>
#include <vcl/builder.hxx>
#include <vcl/button.hxx>
#include <vcl/configsettings.hxx>
#include <vcl/controllayout.hxx>
#include <vcl/decoview.hxx>
#include <vcl/dialog.hxx>
#include <vcl/edit.hxx>
#include <vcl/field.hxx>
#include <vcl/fixed.hxx>
#include <vcl/font.hxx>
#include <vcl/graph.hxx>
#include <vcl/graphicfilter.hxx>
#include <vcl/group.hxx>
#include <vcl/help.hxx>
#include <vcl/i18nhelp.hxx>
#include <vcl/image.hxx>
#include <vcl/keycodes.hxx>
#include <vcl/layout.hxx>
#include <vcl/lstbox.hxx>
#include <vcl/menu.hxx>
#include <vcl/metric.hxx>
#include <vcl/mnemonic.hxx>
#include <vcl/morebtn.hxx>
#include <vcl/msgbox.hxx>
#include <vcl/scrbar.hxx>
#include <vcl/settings.hxx>
#include <vcl/stdtext.hxx>
#include <vcl/svapp.hxx>
#include <vcl/textdata.hxx>
#include <vcl/timer.hxx>
#include <vcl/toolbox.hxx>
#include <vcl/vclmedit.hxx>
#include <vcl/virdev.hxx>
#include <vcl/waitobj.hxx>
#include <vcl/wrkwin.hxx>
#include <vector>

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
