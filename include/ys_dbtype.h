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
#ifndef YS_DB_TYPE_H
#define YS_DB_TYPE_H

/**
 * @ingroup database
 *
 * Abstract base class for datebase objects in YardSale
 * @author Jesse Lovelace
 */
class YardDBType{
    public:
        
    /** Empty constructor */
    YardDBType() {}
        
    /** Empty copy constructor */
    YardDBType(const YardDBType& obj) {}
  
    /** Virtual destructor */
    virtual ~YardDBType() {}
    
};

/**
 * A temporary structure for holding date information
 */
struct DateTime {
    
    unsigned int year;
    unsigned char month;
    unsigned char day;
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
};

#endif
