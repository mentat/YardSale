/////////////////////////////////////////////////////////////////////////////
// Name:        xh_radbt.cpp
// Purpose:     XRC resource for wxRadioButton
// Author:      Bob Mitchell
// Created:     2000/03/21
// RCS-ID:      $Id: xh_radbt.cpp,v 1.2 2004/04/21 20:27:43 thementat Exp $
// Copyright:   (c) 2000 Bob Mitchell and Verant Interactive
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////
 
#ifdef __GNUG__
#pragma implementation "xh_radbt.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "xh_radbt.h"
#include "wx/radiobut.h"

#if wxUSE_RADIOBOX

wxRadioButtonXmlHandler::wxRadioButtonXmlHandler() 
: wxXmlResourceHandler() 
{
    XRC_ADD_STYLE(wxRB_GROUP);
    AddWindowStyles();
}

wxObject *wxRadioButtonXmlHandler::DoCreateResource()
{ 
    /* BOBM - implementation note.
     * once the wxBitmapRadioButton is implemented.
     * look for a bitmap property. If not null, 
     * make it a wxBitmapRadioButton instead of the 
     * normal radio button.
     */ 

    XRC_MAKE_INSTANCE(control, wxRadioButton)

    control->Create(m_parentAsWindow,
                    GetID(),
                    GetText(wxT("label")),
                    GetPosition(), GetSize(),
                    GetStyle(),
                    wxDefaultValidator,
                    GetName());

    control->SetValue(GetBool(wxT("value"), 0));
    SetupWindow(control);
    
    return control;
}

bool wxRadioButtonXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("wxRadioButton"));
}

#endif
