#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"
#include "ys_carrier_type.h"
#include "ys_exception.h"

using namespace std;

YardCarrierType::YardCarrierType(const YardCarrierType& obj) {
    
    *this = obj;
    
}

string YardCarrierType::ToString(const string& delim) const {
    
    stringstream output;
    output << m_carrierID << delim << m_carrierName   
        << delim << m_pickupLoc << delim << m_phoneNum;
    
    return output.str();
        
}

void YardCarrierType::FillFromStream(otl_stream * stream)
{  
    if (!stream)
        return;
    /// maybe throw here
    
    //char oversized, freight;
    otl_datetime lastRec;
    
    YardCarrierType temp;
        
    try {
        *stream 
            >> m_carrierID 
            >> m_carrierName
            >> m_pickupLoc
            >> m_phoneNum;
            
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
}

YardCarrierType& YardCarrierType::operator=(const YardCarrierType& obj) {
    
    m_carrierID = obj.m_carrierID;
    m_carrierName = obj.m_carrierName;
    m_pickupLoc = obj.m_pickupLoc;
    m_phoneNum = obj.m_phoneNum;
    
    return *this;
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_CARRIER_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardCarrierType test1;
    test1.SetCarrierName("Big A");
    test1.SetPickupLoc("mommas place");
    test1.SetPhoneNum("555-1212");

    YardCarrierType test2(test1);
    
    VERIFY(test2.GetCarrierID(), test1.GetCarrierID());
    
    YardCarrierType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetCarrierName(), test2.GetCarrierName());
    VERIFY(test3.GetPickupLoc(), test2.GetPickupLoc());


    vector<YardCarrierType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetCarrierID(), anArray[2].GetCarrierID());
    
    vector<YardCarrierType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetCarrierID(), copyArray[0].GetCarrierID());

    return failure;
}

#endif
