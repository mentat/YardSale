#include <sstream>

#include "ys_inv_type.h"
#include "wx/log.h"

using namespace std;

#if 0
void YardInvType::SetKey(int key) {
    
    if (m_key == -1)
        m_key = key;
    else
        throw YardDBIntegrityException("YardInvType::SetKey: You may not"
            " overwrite this value or DB integrity will be violated.");
}
#endif

string YardInvType::ToString(const string& delim, bool quotes) const {
    
    char q = '\'';
    stringstream output;
    output << GetKey() << delim 
        << q << GetName() << q << delim
        << q << GetSKU() << q << delim 
        << q << GetBarCode() << q << delim 
        << q << GetDescription() << q << delim 
        << q << GetDepartment() << q << delim 
        << GetQuantOnHandS() << delim 
        << GetQuantOnOrderS() << delim 
        << GetReorderLevelS() << delim 
        << GetReorderQuantityS() << delim 
        << q << GetType() << q << delim 
        << GetGroupIdS() << delim
        << GetTaxTypeS() << delim
        << GetVendorIdS() << delim
        << GetRetailPriceS() << delim
        << GetWholesalePriceS() << delim
        << q << GetBulkPricing() << q << delim;    
	if (GetDateLastReceived().GetYear() == 0)
        output << "now()" << delim;
    else
        output << q << GetDateLastReceived().ToString() << q << delim;
    output << GetWeightLbsS() << delim
        << q << IsOverSizedS() << q << delim
        << q << MustShipFreightS() << q << delim
        << q << GetComment() << q;
  
    wxLogDebug(output.str().c_str());
     
    return output.str();
        
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_INV_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardInvType test1;
    
    test1.SetBarCode("QWERTY");
    VERIFY(test1.GetBarCode(), string("QWERTY"));
    
    test1.SetDescription("A very nice object");
    VERIFY(test1.GetDescription(), string("A very nice object"));
    
    test1.SetDepartment("Sales");
    VERIFY(test1.GetDepartment(), string("Sales"))
    
    test1.SetQuantOnHand(69);
    VERIFY(test1.GetQuantOnHand(), 69);
    
    test1.SetQuantOnOrder(96);
    VERIFY(test1.GetQuantOnOrder(), 96);
    
    test1.SetReorderLevel(30);
    VERIFY(test1.GetReorderLevel(), 30);
   
    test1.SetType("Widget");
    VERIFY(test1.GetType(), string("Widget"));
    
    test1.SetWeightLbs(1000.45);
    VERIFY_FLOAT(test1.GetWeightLbs(), 1000.45);
    
    test1.SetTaxType(0);
    VERIFY(test1.GetTaxType(), 0);
    
    test1.SetRetailPrice(34.23);
    VERIFY_FLOAT(test1.GetRetailPrice(), 34.23);
    
    test1.SetWholesalePrice(1000.12);
    VERIFY_FLOAT(test1.GetWholesalePrice(), 1000.12);
   
    test1.AddBulkPrice(100, 0.12);
    VERIFY_FLOAT(test1.GetBulkPrice(100), 0.12);
    //cout << test1.child("INV_Bulk_Price").child("100").data() << endl;
    //cout << test1.GetBulkPrice(100) << endl;
    
    test1.AddBulkPrice(200, 0.23);
    VERIFY_FLOAT(test1.GetBulkPrice(200), 0.23);
    // should overwrite
    test1.AddBulkPrice(100, 0.50);
    VERIFY_FLOAT(test1.GetBulkPrice(100), 0.50);
    
    test1.RemoveBulkPrice(100);
    VERIFY_FLOAT(test1.GetBulkPrice(100), 0.0);
   
    test1.SetOverSized(true);
    VERIFY(test1.IsOverSized(), true);
    
    test1.SetShipFreight(false);
    VERIFY(test1.MustShipFreight(), false);
 
#if 0 
    vector<XMLNode> v = test1.children();
   
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].name() << endl;
    }
    
    cout << string(test1) << endl;
#endif
    YardInvType test2(test1);
    
    VERIFY(test2.GetBarCode(), test1.GetBarCode());
    
    YardInvType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetDepartment(), test2.GetDepartment());
    VERIFY(test3.IsOverSized(), test2.IsOverSized());


    vector<YardInvType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetDepartment(), anArray[2].GetDepartment());
    
    vector<YardInvType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetBarCode(), copyArray[0].GetBarCode());
      
    return failure;
}

#endif
