/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Adam Parrish <waparris@ncsu.edu>
 
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
#ifndef YS_TAX_TYPE_H
#define YS_TAX_TYPE_H

#include "xmlnode.h"
#include "ys_build.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class YardTaxType: public XMLNode
{
 public:
   
    friend class YardDatabase;
      
    YardTaxType() { setName("Tax_Table"); }
    YardTaxType(const string& xml):XMLNode(xml, XMLNode::Str) {}
        
    static const char * GetUnique() { return "TAX_Name"; }
    
    /* Getters */
    string GetIdS() const
        { return child("TAX_ID").data(); }
    long GetId() const
        { return ToLong(GetIdS()); }
    string GetName() const
        { return child("TAX_Name").data(); }
    string GetPercentS() const
        { return child("TAX_Percent").data(); }
    double GetPercent() const
        { return ToDouble(GetPercentS()); }
    
    /* setters */
    void SetId(const int& a_num) 
        { child("TAX_ID").setData(ToStr(a_num)); }
    void SetName(const string& a_str) 
        { child("TAX_Name").setData(a_str); }
    void SetPercent(const double a_num) 
        { child("TAX_Percent").setData(ToStr(a_num, YS_TAX_PRECISION)); }
    
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quote = true) const;
        
};

#endif
