/////////////////////////////////////////////////////////////////////////////
// Name:        xh_stlin.h
// Purpose:     XML resource handler for wxStaticLine
// Author:      Vaclav Slavik
// Created:     2000/09/00
// RCS-ID:      $Id: xh_stlin.h,v 1.2 2004/04/21 20:28:13 thementat Exp $
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_STLIN_H_
#define _WX_XH_STLIN_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_stlin.h"
#endif

#include "xmlres.h"

#if wxUSE_STATLINE

class WXXMLDLLEXPORT wxStaticLineXmlHandler : public wxXmlResourceHandler
{
public:
    wxStaticLineXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
};

#endif

#endif // _WX_XH_STLIN_H_
