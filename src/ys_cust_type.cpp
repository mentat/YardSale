#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"

#include "ys_cust_type.h"
#include "ys_util.h"
#include "ys_exception.h"

using namespace std;
   
YardCustType::YardCustType(const YardCustType& obj) {
    
    *this = obj;
    
}

string YardCustType::ToString(const string& delim) const {
    
    stringstream output;
    output << m_accountNumber << delim << m_custFirstName << delim 
        << m_custMiddleName << delim << m_custLastName << delim
        << m_custPhone << delim <<  m_custZip << delim 
        << m_custCCNumber << delim << m_custCCExpiration << delim
        << m_custCCName;
    return output.str();
        
}

void YardCustType::FillFromStream(otl_stream * stream)
{  
    
    
    if (!stream)
        return;
    
    YardCustType temp;
    
    
    try {
        *stream 
          >> m_custFirstName
          >> m_custMiddleName
          >> m_custLastName
          >> m_custPhone 
          >> m_custZip 
          >> m_custCCNumber
          >> m_custCCExpiration
          >> m_custCCName;    
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
}
    
YardCustType& YardCustType::operator=(const YardCustType& obj) {
    
    m_accountNumber = obj.m_accountNumber;
    m_custFirstName = obj.m_custFirstName;
    m_custMiddleName = obj.m_custMiddleName;
    m_custLastName = obj.m_custLastName;
    m_custAddress = obj.m_custAddress;
    m_custPhone = obj.m_custPhone;
    m_custCity = obj.m_custCity;
    m_custZip = obj.m_custZip;
    m_custCCNumber = obj.m_custCCNumber;
    m_custCCExpiration = obj.m_custCCNumber;
    m_custCCName = obj.m_custCCName;
    return *this;
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_CUST_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardCustType test1;
    
    test1.SetAccountNumber(12345);
    test1.SetCustFirstName("Doh");
    test1.SetCustMiddleName("Nuts");
    test1.SetCustLastName("AreGood");
    //test1.SetCustAddress("<ADDRESS><1>Somewhere</1><2>Else</2></ADDRESS>");
    test1.SetCustPhoneNumber("919.222.3333");
    test1.SetCustCity("SouthPark");
    test1.SetCustZip("80120");
    test1.SetCustCreditCardNumber("0000222230304444");
    test1.SetCustCreditCardExpiration("12/04");
    test1.SetCustCreditCardName("Doh Nuts AreGood");
    
    
    YardCustType test2(test1);
    
    VERIFY(test2.GetAccountNumber(), test1.GetAccountNumber());
    
    YardCustType test3;
    
    test3 = test2;
    VERIFY(test3.GetAccountNumber(), test2.GetAccountNumber());
    VERIFY(test2.GetCustomerPhone(), test1.GetCustomerPhone());


    vector<YardCustType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetAccountNumber(), anArray[2].GetAccountNumber());
    
    vector<YardCustType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetAccountNumber(), copyArray[0].GetAccountNumber());
    
    return failure;
}

#endif
