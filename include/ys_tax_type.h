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

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;
    
class YardTaxType: public YardDBType
{
 public:
   
    friend class YardDatabase;
      
    YardTaxType() {}
    
    /**
     * Copy constructor
     */
    YardTaxType(const YardTaxType& obj);
    
    YardTaxType& operator=(const YardTaxType& obj);
    
    /* Getters */
    int GetTaxId() { return m_taxID; }
    string GetTaxName() { return m_taxName; }
    float GetTaxPercent() { return m_percent; }
    
        
    /* setters */
    void SetTaxId(const int& a_num) { m_taxID = a_num; }
    void SetTaxName(const string a_str) { m_taxName = a_str; }
    void SetPercent(const float a_num) { m_percent = a_num; }
    
    
   
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",") const;
    
    void FillFromStream(otl_stream * stream);
   
 private:
    
    /* These variables directly correspond with the database */
    int m_taxID;
    string m_taxName;
    float m_percent;
    
};

#endif
