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
#include "wx/bitmap.h"
#include "wx/font.h"
class wxStaticBitmap;
class wxTimer;
class wxTimerEvent;
class wxPaintEvent;

/**
 * This is a scrolly, eye-candy about screen.
 * It shows the authors and the packages that we use.
 * @author Jesse Lovelace
 */
class YardAboutGL: public wxDialog
{
 public: 
     /** 
     * Constructs an About screen
     */    
    YardAboutGL(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxDEFAULT_FRAME_STYLE,
               const wxString& name = wxT("YardAboutGL"));
    
    /// Destructor
    virtual ~YardAboutGL();
 
    /// The OK button was pressed.
    void OnOK(wxCommandEvent& event);
    /// The timer loop for "animation"
    /// @todo Do something better here, this is CPU intensive.
    void OnTimer(wxTimerEvent& event);
    /// The window paint event
    /// @todo Optimize.
    void OnPaint(wxPaintEvent& event);
    void OnIdle(wxIdleEvent& event);
        
 private:
     wxStaticBitmap * m_bitmapWin;
     wxBitmap m_bitmap;
     wxBitmap m_cpy;
     wxBitmap m_textBmp;
     wxTimer * m_timer;
 
     wxFont m_font;
     wxString m_text;
 
     int m_txtWidth;
     int m_txtHeight;
 
     int m_y;
     DECLARE_EVENT_TABLE()
};


#endif
