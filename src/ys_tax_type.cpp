#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"

#include "ys_tax_type.h"
#include "ys_util.h"
#include "ys_exception.h"

using namespace std;
   
YardTaxType::YardTaxType(const YardTaxType& obj) {
    
    *this = obj;
    
}

string YardTaxType::ToString(const string& delim) const {
    
    stringstream output;
    output << strIToA(m_taxID) << delim << m_taxName << delim 
        << strFToA(m_percent);
    return output.str();
        
}

void YardTaxType::FillFromStream(otl_stream * stream)
{  
    
    
    if (!stream)
        return;
    
    YardTaxType temp;
    
    
    try {
        *stream 
          >> m_taxID
          >> m_taxName
          >> m_percent;    
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
}
    
YardTaxType& YardTaxType::operator=(const YardTaxType& obj) {
    
    m_taxID = obj.m_taxID;
    m_taxName = obj.m_taxName;
    m_percent = obj.m_percent;
    return *this;
} 

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_TRANS_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    
    
    YardTaxType test1;
  
    test1.SetTaxId(1);
    test1.SetTaxName(
    
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
