/////////////////////////////////////////////////////////////////////////////
// Name:        xh_scwin.h
// Purpose:     XML resource handler for wxScrolledWindow
// Author:      Vaclav Slavik
// Created:     2002/10/18
// RCS-ID:      $Id: xh_scwin.h,v 1.2 2004/04/21 20:27:51 thementat Exp $
// Copyright:   (c) 2002 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_SCWIN_H_
#define _WX_XH_SCWIN_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_scwin.h"
#endif

#include "xmlres.h"
#include "wx/defs.h"



class WXXMLDLLEXPORT wxScrolledWindowXmlHandler : public wxXmlResourceHandler
{
public:
    wxScrolledWindowXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif // _WX_XH_SCWIN_H_
