#include "ys_shipping_type.h"

string YardShipType::ToString(const string& delim) const {
    
    stringstream output;
    char q = '\'';
    output << 
        q << GetShipType() q << delim 
        << GetCarrierIdS() << delim 
        << GetCostS() << delim
        << GetEnabledS();
    
    return output.str();
        
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_SHIPPING_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardShipType test1;
    test1.SetShipType("overnight");
    test1.SetCarrierID(420420);
    test1.SetCost(254.25);
	test1.SetEnabled(1);
    
    YardShipType test2(test1);
    
    VERIFY(test2.GetShipType(), test1.GetShipType());
    
    YardShipType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetCarrierID(), test2.GetCarrierID());
    VERIFY(test3.GetCost(), test2.GetCost());
	VERIFY(test3.GetEnabled(), test2.GetEnabled());


    vector<YardShipType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetCarrierID(), anArray[2].GetCarrierID());
    
    vector<YardShipType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetCost(), copyArray[0].GetCost());

    return failure;
}

#endif
