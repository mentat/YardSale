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

#include <string>
#include <sstream>
using namespace std;
class otl_stream;

/**
 * Abstract base class for datebase objects in YardSale.
 * All DB types are assignable and contain a ToString method
 * to format the type to text.
 *
 * @see YardInvType
 * @see YardEmployeeType
 * @version \$Revision: 1.11 $$
 * @ingroup database
 * @author Jesse Lovelace
 */
class YardDBType{
    public:
        
    /** Empty constructor */
    YardDBType() {}
        
    /** Empty copy constructor */
    YardDBType(const YardDBType& obj) {}
        
    /** 
     * To string method formats the datatype internals into string form.
     * This method is pure virtual and must be implemented in derived classes.
     * @param delim The string to delimit internal fields with, defaults to newline.
     **/
    virtual string ToString(const string& delim = ",") const = 0;
  
        
    virtual void FillFromStream(otl_stream * stream) = 0;
    /** Virtual destructor */
    virtual ~YardDBType() {}
    
};

/**
 * A temporary structure for holding date information
 */
class DateTime {
 public:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    unsigned long fraction;
    int frac_precision;
    
    string ToString() const {
        stringstream str;
        str <<month<<"/"<<day<<"/"<<year<<" "<<hour<<":"<<minute<<":"<<second<<"."<<fraction;
        return str.str();
        
    }
};

#endif
