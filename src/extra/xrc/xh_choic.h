/////////////////////////////////////////////////////////////////////////////
// Name:        xh_choic.h
// Purpose:     XML resource handler for wxChoice
// Author:      Bob Mitchell
// Created:     2000/03/21
// RCS-ID:      $Id: xh_choic.h,v 1.2 2004/04/21 20:27:27 thementat Exp $
// Copyright:   (c) 2000 Bob Mitchell and Verant Interactive
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_CHOIC_H_
#define _WX_XH_CHOIC_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_choic.h"
#endif

#include "xmlres.h"

class WXXMLDLLEXPORT wxChoiceXmlHandler : public wxXmlResourceHandler
{
public:
    wxChoiceXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);
private:
    bool m_insideBox;
    wxArrayString strList;
};


#endif // _WX_XH_CHOIC_H_
