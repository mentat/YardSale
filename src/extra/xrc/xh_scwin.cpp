/////////////////////////////////////////////////////////////////////////////
// Name:        xh_scwin.cpp
// Purpose:     XRC resource for wxScrolledWindow
// Author:      Vaclav Slavik
// Created:     2002/10/18
// RCS-ID:      $Id: xh_scwin.cpp,v 1.2 2004/04/21 20:27:51 thementat Exp $
// Copyright:   (c) 2002 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifdef __GNUG__
#pragma implementation "xh_scwin.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "xh_scwin.h"
#include "wx/scrolwin.h"


wxScrolledWindowXmlHandler::wxScrolledWindowXmlHandler() 
: wxXmlResourceHandler() 
{
    XRC_ADD_STYLE(wxHSCROLL);
    XRC_ADD_STYLE(wxVSCROLL);
    AddWindowStyles();
}

wxObject *wxScrolledWindowXmlHandler::DoCreateResource()
{ 
    XRC_MAKE_INSTANCE(control, wxScrolledWindow)

    control->Create(m_parentAsWindow,
                    GetID(),
                    GetPosition(), GetSize(),
                    GetStyle(wxT("style"), wxHSCROLL | wxVSCROLL),
                    GetName());

    SetupWindow(control);
    
    return control;
}

bool wxScrolledWindowXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("wxScrolledWindow"));
}
