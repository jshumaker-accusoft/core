/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_SD_SOURCE_UI_INC_LAYERTABBAR_HXX
#define INCLUDED_SD_SOURCE_UI_INC_LAYERTABBAR_HXX

#include <svtools/tabbar.hxx>
#include <svtools/transfer.hxx>

namespace sd {

/**
 * TabBar for layer administration
 */
class DrawViewShell;

class LayerTabBar
    : public TabBar,
      public DropTargetHelper
{
public:
    LayerTabBar (
        DrawViewShell* pDrViewSh,
        vcl::Window* pParent);
    virtual ~LayerTabBar (void);

    /** Inform all listeners of this control that the current layer has been
        activated.  Call this method after switching the current layer and is
        not done elsewhere (like when using ctrl + page up/down keys).
    */
    void SendActivatePageEvent (void);

    /** Inform all listeners of this control that the current layer has been
        deactivated.  Call this method before switching the current layer
        and is not done elsewhere (like when using ctrl page up/down keys).
    */
    void SendDeactivatePageEvent (void);

protected:
    DrawViewShell* pDrViewSh;

    // TabBar
    virtual void        Select() SAL_OVERRIDE;
    virtual void        DoubleClick() SAL_OVERRIDE;
    virtual void        MouseButtonDown(const MouseEvent& rMEvt) SAL_OVERRIDE;

    virtual void        Command(const CommandEvent& rCEvt) SAL_OVERRIDE;

    virtual bool        StartRenaming() SAL_OVERRIDE;
    virtual TabBarAllowRenamingReturnCode  AllowRenaming() SAL_OVERRIDE;
    virtual void        EndRenaming() SAL_OVERRIDE;

    virtual void        ActivatePage() SAL_OVERRIDE;

    // DropTargetHelper
    virtual sal_Int8    AcceptDrop( const AcceptDropEvent& rEvt ) SAL_OVERRIDE;
    virtual sal_Int8    ExecuteDrop( const ExecuteDropEvent& rEvt ) SAL_OVERRIDE;
};

} // end of namespace sd

#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
