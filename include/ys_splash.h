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
#ifndef YARDSALE_SPLASH_H
#define YARDSALE_SPLASH_H

#include "wx/wx.h"

/**
 * Eye-candy splash screen
 * @author Jesse Lovelace
 * @version $Revision: 1.7 $
 */
class YardSplash: public wxDialog {
    public:
        
    YardSplash(wxWindow* parent, wxWindowID id, const wxString& title,
               const wxPoint& pos = wxDefaultPosition, 
               const wxSize& size = wxDefaultSize,
               long style = wxSTAY_ON_TOP);
        
    virtual ~YardSplash();
    
    /**
     * Mouse click event handler
     * @deprecated This handler is for testing only and will be removed
     */
    void OnClick(wxMouseEvent& event);
    /// Timer event handler
    void OnTimer(wxTimerEvent& event);
    
    /**
     * Called to nudge progress bar over
     * @param amount Number of pixels to nudge
     */
    void Bump(unsigned int amount = 10);
    
    private:
        
    int m_progress;
    int m_limit;
    
    wxBitmap * m_logo;
    
    wxStaticBitmap * m_bitmap;
    wxTimer * m_timer;
    
    DECLARE_EVENT_TABLE()
};


#endif
