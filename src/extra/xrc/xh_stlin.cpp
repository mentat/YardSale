/////////////////////////////////////////////////////////////////////////////
// Name:        xh_stbox.cpp
// Purpose:     XRC resource for wxStaticLine
// Author:      Brian Gavin
// Created:     2000/09/09
// RCS-ID:      $Id: xh_stlin.cpp,v 1.2 2004/04/21 20:28:08 thementat Exp $
// Copyright:   (c) 2000 Brian Gavin
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifdef __GNUG__
#pragma implementation "xh_stlin.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "xh_stlin.h"
#include "wx/statline.h"

#if wxUSE_STATLINE

wxStaticLineXmlHandler::wxStaticLineXmlHandler() 
: wxXmlResourceHandler() 
{
    XRC_ADD_STYLE(wxLI_HORIZONTAL);
    XRC_ADD_STYLE(wxLI_VERTICAL);
    AddWindowStyles();
}

wxObject *wxStaticLineXmlHandler::DoCreateResource()
{ 
    XRC_MAKE_INSTANCE(line, wxStaticLine)

    line->Create(m_parentAsWindow,
                GetID(),
                GetPosition(), GetSize(),
                GetStyle(wxT("style"), wxLI_HORIZONTAL),
                GetName());

    SetupWindow(line);
    
    return line;
}

bool wxStaticLineXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("wxStaticLine"));
}

#endif
