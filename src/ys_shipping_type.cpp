#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"
#include "ys_shipping_type.h"
#include "ys_exception.h"

using namespace std;

YardShippingType::YardShippingType(const YardShippingType& obj) {
    
    *this = obj;
    
}

string YardShippingType::ToString(const string& delim) const {
    
    stringstream output;
    output << m_shipType << delim << m_carrierID << delim << m_cost;
    
    return output.str();
        
}

void YardShippingType::FillFromStream(otl_stream * stream)
{  
    if (!stream)
        return;
    /// maybe throw here
    
    //char oversized, freight;
    otl_datetime lastRec;
    
    YardShippingType temp;
        
    try {
        *stream 
            >> m_shipType 
            >> m_carrierID
            >> m_cost;
            
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
}

YardShippingType& YardShippingType::operator=(const YardShippingType& obj) {
    
    m_shipType = obj.m_shipType;
    m_carrierID = obj.m_carrierID;
    m_cost = obj.m_cost;
    
    return *this;
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_SHIPPING_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardShippingType test1;
    test1.SetShipType("overnight");
    test1.SetCarrierID("420420");
    test1.SetCost("254.25");
    
    YardShippingType test2(test1);
    
    VERIFY(test2.GetShipType(), test1.GetShipType());
    
    YardShippingType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetCarrierID(), test2.GetCarrierID());
    VERIFY(test3.GetCost(), test2.GetCost());


    vector<YardShippingType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetCarrierID(), anArray[2].GetCarrierID());
    
    vector<YardShippingType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetCost(), copyArray[0].GetCost());

    return failure;
}

#endif
