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
#ifndef YS_TRANSACTION_TYPE_H
#define YS_TRANSACTION_TYPE_H

#include "ys_dbtype.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;
    
class YardTransType: public YardDBType
{
 public:
   
    friend class YardDatabase;
      
    YardTransType() {}
    
    /**
     * Copy constructor
     */
    YardTransType(const YardTransType& obj);
    
    YardTransType& operator=(const YardTransType& obj);
    
    /* Getters */
    int GetTransKey() const { return m_transKey; }
    int GetEmpKey() const { return m_empKey; }
    int GetInvKey() const { return m_invKey; }
    int GetCustKey() const { return m_custKey; }
    float GetItemSalePrice() const { return m_salePrice; }
    int GetTransID() const { return m_transID; }
    int GetQuantity() const { return m_quantity; }
    string GetComment() const { return m_comment; }
      
    /* setters */
    void SetTransKey(const int& a_num) { m_transKey = a_num; }
    void SetEmpKey(const int& a_num) { m_empKey = a_num; }
    void SetInvKey(const int& a_num) { m_invKey = a_num; }
    void SetCustKey(const int& a_num) { m_custKey = a_num; }
    void SetItemSalePrice(const float& a_num) { m_salePrice = a_num; }
    void SetTransID(const int& a_num) { m_transID = a_num; }
    void SetQuantity(const int& a_num) { m_quantity = a_num; }
    void SetComment(const string& str) { m_comment = exstr; }
    
    /* member functions */
    float SubTotal(const vector<YardTransType> transVect);
       /* float subTotal = 0;
        for(unsigned int i = 0 ;  i< transVect.size(); i++){
                subTotal += transVect[i].GetItemSalePrice() * transVect[i].GetQuantity();            
        }
        return subTotal;
    } */
   
    /**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",") const;
    
    void FillFromStream(otl_stream * stream);
   
 private:
    
    /* These variables directly correspond with the database */
    int m_transKey;
    int m_empKey;
    int m_invKey;
    int m_custKey;
    float m_salePrice;
    int m_transID;
    int m_quantity;
    string m_comment;
    

};

#endif
