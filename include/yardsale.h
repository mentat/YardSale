/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004  Jesse Lovelace <jllovela@ncsu.edu>
 
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

/**	\mainpage YardSale
 * <h1>Reference Manual</h1>
 * <p>Yardsale is an open source point of sale program. 
 * The program execution of YardSale goes as follows:
 * Splash (load windows, db in backgorund)->Login->Main
 * From the Main screen you can select: </p>
 * <ul>
 * <li>Employee Managment @see YardEmployee
 * <li>Sales
 * <li>Inventory Managment
 * <li>Reports
 * <li>Customer Managment
 * <li>Logout
 * </ul>
 * <p>
 *
 * Main Web Page: <a href="http://yardsale.sf.net">YardSale</a> 
 * @author Jesse Lovelace
 * @author Adam Parrish
 * @author Mike Swigon
 * @author Jay Jonston
 * @author John Lamb
 */

/**
 * This is the main application object.
 * @author Jesse Lovelace
 * @version $Revision: 1.6 $
 */
class YardSale: public wxApp {
    public:
        
    /**
     * This is the function were top level windows are created
     * @return True if application initialized ok
     */
    virtual bool OnInit();
};

wxBitmap * GetBitmap(int id);
        

#endif
