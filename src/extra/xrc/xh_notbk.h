/////////////////////////////////////////////////////////////////////////////
// Name:        xh_notbk.h
// Purpose:     XML resource handler for wxNotebook
// Author:      Vaclav Slavik
// RCS-ID:      $Id: xh_notbk.h,v 1.2 2004/04/21 20:27:42 thementat Exp $
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_XH_NOTBK_H_
#define _WX_XH_NOTBK_H_

#if defined(__GNUG__) && !defined(__APPLE__)
#pragma interface "xh_notbk.h"
#endif

#include "xmlres.h"

#if wxUSE_NOTEBOOK

class WXDLLEXPORT wxNotebook;

class WXXMLDLLEXPORT wxNotebookXmlHandler : public wxXmlResourceHandler
{
public:
    wxNotebookXmlHandler();
    virtual wxObject *DoCreateResource();
    virtual bool CanHandle(wxXmlNode *node);

private:
    bool m_isInside;
    wxNotebook *m_notebook;
};

#endif

#endif // _WX_XH_NOTBK_H_
