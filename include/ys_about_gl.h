/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
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
