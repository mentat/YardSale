#ifndef YARD_ABOUT_GL_H
#define YARD_ABOUT_GL_H

#include "wx/dialog.h"

#ifdef YS_OGL_ABOUT
class TestGLCanvas;
    
class YardAboutGL: public wxDialog
{
 public: /** 
     * Constructs an Inventory screen
     */    
    YardAboutGL(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardAboutGL"));
    
    /// Destructor
    virtual ~YardAboutGL() {}
 
    void OnOK(wxCommandEvent& event);
 private:
     
     TestGLCanvas * m_gl;
     DECLARE_EVENT_TABLE()
};

#endif // YS_OGL_ABOUT

#endif
