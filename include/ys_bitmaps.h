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
#ifndef YS_BITMAPS_H
#define YS_BITMAPS_H

class wxBitmap;
    
class YardBitmaps
{
 public:
     
    enum { 
        MAIN_LOGO = 1,
        MAIN_INV = 12,
        MAIN_EMPLOY = 0,
        MAIN_SALE = 15,
        MAIN_CUST = 10,
        MAIN_LOGOUT = 13,
        MAIN_REPORT = 14,
        SALE_DONE = 4,
        SALE_REMOVE = 16,
        SALE_CANCEL = 5,
        SALE_BACK = 2,
        CALC_PLUS = 11,
        CALC_MINUS = 16,
        CALC_EQUALS = 3,
        FOOTER_CALC = 9, // not done
        FOOTER_KEY = 9, // not done
        FOOTER_UNDO = 9, //not done
        USER_PIC1 = 6,
        USER_PIC2 = 7,
        USER_PIC3 = 8,
        TUX = 9,
        FOOT_CALC = 17,
        FOOT_KEY = 18,
        FOOT_UNDO = 19,
        TRASH = 20
    };
        
    YardBitmaps();
 
    ~YardBitmaps();
        
    /**
     * Loads bitmaps to memory, returns the number of bitmaps remaining
    */
    int LoadBitmaps();
    
    /**
     * Returns a bitmap.
     * @param id The enumerated ID of the bitmap;
     * @return A reference to the wxBitmap
     */
    wxBitmap& GetBitmap(unsigned int id);
    
    unsigned short GetCount() const { return m_length; }
        
 private:
     
     wxBitmap ** m_bitmaps;
     unsigned short m_length;
     unsigned short m_index;
        
};

#endif
