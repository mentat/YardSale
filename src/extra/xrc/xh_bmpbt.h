/////////////////////////////////////////////////////////////////////////////
// Name:        xh_bmpbt.h
// Purpose:     XML resource handler for bitmap buttons
// Author:      Brian Gavin
// Created:     2000/03/05
// RCS-ID:      $Id: xh_bmpbt.h,v 1.2 2004/04/21 20:27:24 thementat Exp $
// Copyright:   (c) 2000 Brian Gavin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_BMPBT_H_
#define _WX_XH_BMPBT_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_bmpbt.h"
#endif

#include "xmlres.h"


class WXXMLDLLEXPORT wxBitmapButtonXmlHandler : public wxXmlResourceHandler
{
public:
    wxBitmapButtonXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};


#endif // _WX_XH_BMPBT_H_
