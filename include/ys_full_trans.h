#ifndef YS_TRANS_FULL_H
#define YS_TRANS_FULL_H

#include "ys_inv_type.h"
#include "ys_cust_type.h"
#include "ys_employee_type.h"
#include "ys_trans_type.h"
#include "xmlnode.h"

class YardFullTransaction: public XMLNode
{
 public:
     YardFullTransaction():XMLNode() {}
 
     vector<long> GetItemsId() const
    {
        vector<long> ret;
        for (NodeMap::const_iterator it = m_xmlData->m_children.begin();
             it != m_xmlData->m_children.end(); it++)
            ret.push_back(YardTransType(it->second).GetItem());
        return ret;
    }
        
    vector<YardTransType> GetTransactions() const
    {   // oh the sexiness of templates!
        return children<YardTransType>("Transaction_Log_Table");
    }
    
    unsigned int CountItems() const
    { 
        long count = 0;
        for (NodeMap::const_iterator it = m_xmlData->m_children.begin();
         it != m_xmlData->m_children.end(); it++)
            count += YardTransType(it->second).GetQuantity();
        return count;            
    }
        
    string GetQuantityS(long index) const
        { return YardTransType(child("Transaction_Log_Table", index)).GetQuantityS(); }
        
    long GetQuantity(long index) const
        { return ToLong(GetQuantityS(index)); }
        
   string GetComment(long index) const
        { return YardTransType(child("Transaction_Log_Table", index)).GetComment(); }
                
    YardDate GetTime(long index) const
        { return YardTransType(child("Transaction_Log_Table", index)).GetTime(); }
        
     /* member functions */
    double SubTotal(const vector<YardTransType> transVect);
    
    map<string, float> GetTaxes() const
        {
            map<string, float> tax;
            return tax;
        }

};

#endif
