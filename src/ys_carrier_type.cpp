#include <sstream>
#include "ys_carrier_type.h"

using namespace std;

string YardCarrierType::ToString(const string& delim, bool quotes) const {
    
    stringstream ret;
    char q = '\'';
    ret << child("CRR_ID").data() << delim
        << q << child("CRR_Name").data() << q << delim
        << q << child("CRR_Pickup_Location").data() << q << delim
        << q << child("CRR_Phone_Number").data() << q;
    return ret.str();
 
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
