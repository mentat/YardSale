#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"
#include "ys_vend_type.h"
#include "ys_exception.h"

using namespace std;

YardVendType::YardVendType(const YardVendType& obj) {
    
    *this = obj;
    
}

string YardVendType::ToString(const string& delim) const {
    
    stringstream output;
    output << m_vendID << delim << m_vendName << delim << m_vendAddr 
        << delim << m_vendCity << delim << m_vendState 
        << delim << m_vendZip << delim << m_vendPhone 
        << delim << m_vendSalesRep << delim << m_vendSpecialty
        << delim << m_vendEmail << delim << m_vendHomePage;
    
    return output.str();
        
}

void YardVendType::FillFromStream(otl_stream * stream)
{  
    if (!stream)
        return;
    /// maybe throw here
    
    char oversized, freight;
    otl_datetime lastRec;
    
    YardVendType temp;
        
    try {
        *stream 
            >> m_vendID 
            >> m_vendName 
            >> m_vendAddr
            >> m_vendCity 
            >> m_vendState
            >> m_vendZip
            >> m_vendPhone
            >> m_vendSalesRep
            >> m_vendSpecialty 
			>> m_vendEmail
            >> m_vendHomePage;
            
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
}

YardVendType& YardVendType::operator=(const YardVendType& obj) {
    
    m_vendID = obj.m_vendID;
    m_vendName = obj.m_vendName;
    m_vendAddress = obj.m_vendAddress;
    m_vendCity = obj.m_vendCity;
    m_vendState = obj.m_vendState;
    m_vendZip = obj.m_vendZip;
    m_vendPhone = obj.m_vendPhone;
    m_vendSalesRep = obj.m_vendSalesRep;
    m_vendSpecialty = obj.m_vendSpecialty;
    m_vendEmail = obj.m_vendEmail;
    m_vendHomePage = obj.m_vendHomePage;
    
    return *this;
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_VEND_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardVendType test1;
    test1.SetVendName("MIKE");
    test1.SetVendAddress("111 faffafe lane");
    test1.SetVendCity("raleigh");
    test1.SetVendState("NC");
    test1.SetVendZip("27606");
    test1.SetVendPhone("999 999-1212");
    test1.SetVendSalesRep("Al");
    test1.SetVendSpecialty("rubber products");
    test1.SetVendEmail("al@blah.com");
    test1.SetVendHomePage("www.al.com");
       

    YardVendType test2(test1);
    
    VERIFY(test2.GetVendName(), test1.GetVendName());
    
    YardVendType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetVendCity(), test2.GetVendCity());
    VERIFY(test3.GetVendSpecialty(), test2.GetVendSpecialty());


    vector<YardVendType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetVendName(), anArray[2].GetVendName());
    
    vector<YardVendType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetVendName(), copyArray[0].GetVendName());

    return failure;
}

#endif
