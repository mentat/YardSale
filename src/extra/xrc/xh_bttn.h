/////////////////////////////////////////////////////////////////////////////
// Name:        xh_bttn.h
// Purpose:     XML resource handler for buttons
// Author:      Vaclav Slavik
// Created:     2000/03/05
// RCS-ID:      $Id: xh_bttn.h,v 1.2 2004/04/21 20:27:25 thementat Exp $
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_BTTN_H_
#define _WX_XH_BTTN_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_bttn.h"
#endif

#include "xmlres.h"

class WXXMLDLLEXPORT wxButtonXmlHandler : public wxXmlResourceHandler
{
public:
    wxButtonXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif // _WX_XH_BTTN_H_
