/////////////////////////////////////////////////////////////////////////////
// Name:        xh_tree.h
// Purpose:     XML resource handler for wxTreeCtrl
// Author:      Brian Gavin
// Created:     2000/09/09
// RCS-ID:      $Id: xh_tree.h,v 1.2 2004/04/21 20:28:15 thementat Exp $
// Copyright:   (c) 2000 Brian Gavin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_TREE_H_
#define _WX_XH_TREE_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_tree.h"
#endif

#include "xmlres.h"

class WXXMLDLLEXPORT wxTreeCtrlXmlHandler : public wxXmlResourceHandler
{
public:
    wxTreeCtrlXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif // _WX_XH_TREE_H_
