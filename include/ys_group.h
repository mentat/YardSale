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
#ifndef YS_GROUP_TYPE_H
#define YS_GROUP_TYPE_H

#include "xmlnode.h"
#include "ys_build.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class YardGroup: public XMLNode
{
 public:
   
    friend class YardDatabase;
      
    YardGroup() { setName("Inventory_Group_Table"); }
    YardGroup(const string& xml): XMLNode(xml, XMLNode::Str) {}
    
    /* Getters */
    string GetIdS() const
        { return child("INVGRP_Group_ID").data(); }
    long GetId() const
        { return ToLong(GetIdS()); }
    string GetName() const
        { return child("INVGRP_Group_Name").data(); }
        
    /* setters */
    void SetId(const int& a_num) 
        { child("INVGRP_Group_ID").setData(ToStr(a_num)); }
    void SetName(const string& a_str) 
        { child("INVGRP_Group_Name").setData(a_str); }
    
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",", bool quote = true) const;
        
};

#endif
