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

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_CARR_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{

    YardCarrierType test1;
    
    test1.SetName("BigMike");
    VERIFY(test1.GetName(), string("BigMike"));
    
    test1.SetPickupLoc("Foxxxy Lady");
    VERIFY(test1.GetPickupLoc(), string("Foxxxy Lady"));
    
    test1.SetPhone("999 123 4567");
    VERIFY(test1.GetPhone(), string("999 123 4567"))
 
#if 0 
    vector<XMLNode> v = test1.children();
   
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].name() << endl;
    }
    
    cout << string(test1) << endl;
#endif
    YardCarrierType test2(test1);
    
    VERIFY(test2.GetName(), test1.GetName());
    
    YardCarrierType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetPickupLoc(), test2.GetPickupLoc());
    VERIFY(test3.GetPhone(), test2.GetPhone());
    
    vector<YardCarrierType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetPhone(), anArray[2].GetPhone());
    
    vector<YardCarrierType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetPhone(), copyArray[0].GetPhone());
      
    return failure;

}

#endif
