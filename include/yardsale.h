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
#ifndef YARDSALE_H
#define YARDSALE_H
#include "wx/app.h"

class YardDatabase;
class YardBitmaps;

/**	\mainpage YardSale
 * <h1>Design and Reference Manual</h1>
 *
 * YardSale is an open source point of sale program.
 * YardSale uses C++, OTL, and wxWindows.  YardSale runs on 
 * any system that supports ANSI C++ including, but not limited
 * to, Linux (most architectures), FreeBSD, Microsoft Windows, 
 * and Mac OSX.
 *
 * Copyright (C) 2004 - YardSale authors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * From the Main screen you can select: 
 * \image html program_flow_1.png
 * \image latex program_flow_1.png "Program Flow" 
 * @author Jesse Lovelace - jllovela at ncsu dot edu
 * @author Adam Parrish - waparris at ncsu dot edu
 * @author Mike Swigon - mrswigon at ncsu dot edu
 * @author Jay Johnston - jkjohnst at ncsu dot edu
 * @author John Lamb - jwlamb at ncsu dot edu
 */

/**
 * This is the main application object.
 * @author Jesse Lovelace
 * @version \$Revision: 1.15 $$
 */
class YardSale: public wxApp {
 public:
        
    /**
     * This is the function were top level windows are created
     * @return True if application initialized ok
     */
    virtual bool OnInit();
 
    /// Run before the program exists, returns program return value
    /// @return Non-zero if program error
    int OnExit();
 
    /**
     * Returns a reference to the database object.
     * @throws Exception if pointer error.
     * @returns Reference to YardDatabase object.
     */
    YardDatabase& DB();
 
    /// Returns a reference to the YardBitmaps object which contains 
    /// the images loaded by the loader.
    YardBitmaps& Images();
 
    wxString GetUser() const { return m_user; }
 
 private:
     
     void LoadConfig();
     wxString m_user;
     wxString m_pass;
     YardBitmaps * m_bitmaps;
     YardDatabase * m_db;
};

        
#endif
