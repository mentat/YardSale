/////////////////////////////////////////////////////////////////////////////
// Name:        xh_unkwn.cpp
// Purpose:     XRC resource for unknown widget
// Author:      Vaclav Slavik
// Created:     2000/09/09
// RCS-ID:      $Id: xh_unkwn.cpp,v 1.2 2004/04/21 20:28:15 thementat Exp $
// Copyright:   (c) 2000 Vaclav Slavik
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
#pragma implementation "xh_unkwn.h"
#endif

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "xh_unkwn.h"
#include "wx/window.h"
#include "wx/log.h"
#include "wx/sizer.h"
#include "wx/panel.h"


class wxUnknownControlContainer : public wxPanel
{
public:
    wxUnknownControlContainer(wxWindow *parent,
                              const wxString& controlName,
                              wxWindowID id = -1,
                              const wxPoint& pos = wxDefaultPosition,
                              const wxSize& size = wxDefaultSize,
                              long style = 0)
        // Always add the wxTAB_TRAVERSAL and wxNO_BORDER styles to what comes
        // from the XRC if anything.
        : wxPanel(parent, id, pos, size, style | wxTAB_TRAVERSAL | wxNO_BORDER,
                  controlName + wxT("_container")),
          m_controlName(controlName), m_controlAdded(FALSE)
    {
        m_bg = GetBackgroundColour();
        SetBackgroundColour(wxColour(255, 0, 255));
    }

    virtual void AddChild(wxWindowBase *child);
    virtual void RemoveChild(wxWindowBase *child);

protected:
    wxString m_controlName;
    bool m_controlAdded;
    wxColour m_bg;
};

void wxUnknownControlContainer::AddChild(wxWindowBase *child)
{
    wxASSERT_MSG( !m_controlAdded, wxT("Couldn't add two unknown controls to the same container!") );

    wxPanel::AddChild(child);

    SetBackgroundColour(m_bg);
    child->SetName(m_controlName);
    child->SetId(wxXmlResource::GetXRCID(m_controlName));
    m_controlAdded = TRUE;

    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add((wxWindow*)child, 1, wxEXPAND);
    SetSizer(sizer);
    SetAutoLayout(TRUE);
    Layout();
}

void wxUnknownControlContainer::RemoveChild(wxWindowBase *child)
{
    wxPanel::RemoveChild(child);
    m_controlAdded = FALSE;
    GetSizer()->Remove((wxWindow*)child);
}

wxUnknownWidgetXmlHandler::wxUnknownWidgetXmlHandler()
: wxXmlResourceHandler()
{
    XRC_ADD_STYLE(wxNO_FULL_REPAINT_ON_RESIZE);
}

wxObject *wxUnknownWidgetXmlHandler::DoCreateResource()
{
    wxPanel *panel =
        new wxUnknownControlContainer(m_parentAsWindow,
                                      GetName(), -1,
                                      GetPosition(), GetSize(),
                                      GetStyle(wxT("style")));
    SetupWindow(panel);
    return panel;
}

bool wxUnknownWidgetXmlHandler::CanHandle(wxXmlNode *node)
{
    return IsOfClass(node, wxT("unknown"));
}

