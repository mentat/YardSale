#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"

#include "ys_trans_type.h"
#include "ys_util.h"
#include "ys_exception.h"

using namespace std;
   
YardTransType::YardTransType(const YardTransType& obj) {
    
    *this = obj;
    
}

float YardTransType::SubTotal(const vector<YardTransType> transVect){
	float subTotal = 0;
        for(unsigned int i = 0 ;  i< transVect.size(); i++){
                subTotal += transVect[i].GetItemSalePrice() * transVect[i].GetQuantity();            
        }
        return subTotal;
} 

string YardTransType::ToString(const string& delim) const {
    
    stringstream output;
    output << strIToA(m_transKey) << delim << strIToA(m_empKey) << delim 
        << strIToA(m_invKey) << delim << strIToA(m_custKey) << delim
        << strFToA(m_salePrice) << delim <<  strIToA(m_transID) << delim 
        << strIToA(m_quantity) << delim << m_comment;
    return output.str();
        
}

void YardTransType::FillFromStream(otl_stream * stream)
{  
    
    
    if (!stream)
        return;
    
    YardTransType temp;
    
    
    try {
        *stream 
          >> m_transKey
          >> m_empKey
          >> m_invKey
          >> m_custKey 
          >> m_salePrice 
          >> m_transID
          >> m_quantity
          >> m_comment;    
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
}
    
YardTransType& YardTransType::operator=(const YardTransType& obj) {
    
    m_transKey = obj.m_transKey;
    m_empKey = obj.m_empKey;
    m_invKey = obj.m_invKey;
    m_custKey = obj.m_custKey;
    m_salePrice = obj.m_salePrice;
    m_transID = obj.m_transID;
    m_quantity  = obj.m_quantity;
    return *this;
} 

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_TRANS_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

/*
    Methods need to add an inventory type and a customer to the trans.
*/

int main()
{
    vector<YardTransType> currentTransaction;
    float subTotal=0;
    
    YardTransType test1;
    
    /* ring up an item */
    test1.SetEmpKey(12345);
    test1.SetInvKey(123);
    test1.SetCustKey(123);
    test1.SetItemSalePrice(4.20);
    test1.SetTransID(1);
    test1.SetQuantity(12);
    test1.SetComment("Pleasure doing bizniss BEATCH");
    
    /* add it to the transaction vector */
    currentTransaction.push_back(test1);
    
    /* calculate the subtotal */
    //subTotal =  SubTotal(currentTransaction);
    cout  << subTotal << endl;

    VERIFY(subTotal, test1.GetQuantity() * test1.GetItemSalePrice());

	YardTransType test2;

    /* ring up another item */
    test2.SetEmpKey(32345);
    test2.SetInvKey(323);
    test2.SetCustKey(423);
    test2.SetItemSalePrice(5.50);
    test2.SetTransID(1);
    test2.SetQuantity(1);
    test2.SetComment("Pleasure doing bizniss BEATCH");
    
    /* add to transaction vector */
    currentTransaction.push_back(test1);
    
    /* calculate the subtotal */
    //subTotal = SubTotal(currentTransaction);
    cout << subTotal << endl;
    
    VERIFY(subTotal, test2.GetQuantity() * test2.GetItemSalePrice());
    
    YardTransType test3;
    
    test3 = test2;
    VERIFY(test3.GetQuantity(), test2.GetQuantity());
    
    vector<YardTransType> copyArray;
    copyArray = currentTransaction;
    
    for(unsigned int i = 0; i < currentTransaction.size() ; i++){
        VERIFY(currentTransaction[i].GetQuantity(), copyArray[i].GetQuantity());
    }
    
    return failure;
}

#endif
