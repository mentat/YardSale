#include "ys_inv_type.h"

void YardInvType::SetItemType(const wxString& str) {
    m_itemType = str;
    
}

void YardInvType::SetDepartment(const wxString& str) {
    m_itemDepartment = str;
}
        
void YardInvType::SetBarCode(const wxString& str) {
    m_barCode = str;
}
   
YardInvType::YardInvType(const YardInvType& obj) {
    
    *this = obj;
    
}
    
YardInvType& YardInvType::operator=(const YardInvType& obj) {
    
    m_skuNumber = obj.m_skuNumber;
    m_barCode = obj.m_barCode;
    m_itemDescription = obj.m_itemDescription;
    m_itemDepartment = obj.m_itemDepartment;
    m_quantityOnHand = obj.m_quantityOnHand;
    m_quantityOnOrder = obj.m_quantityOnOrder;
    m_reorderLevel = obj.m_reorderLevel;
    m_reorderQuantity = obj.m_reorderQuantity;
    m_itemType = obj.m_itemType;
    m_itemWeight = obj.m_itemWeight;
    m_taxType = obj.m_taxType;
    m_vendorId = obj.m_vendorId;
    m_retailPrice = obj.m_retailPrice;
    m_wholesalePrice = obj.m_wholesalePrice;
    
    /*   struct BulkPricing  */
    /*     { */
    /*         unsigned long quantity; */
    /*         float percent; */
    /*     }; */
    m_bulkPricing = obj.m_bulkPricing;
    
    m_dateLastReceived = obj.m_dateLastReceived;
    
    m_oversized = obj.m_oversized;
    m_mustShipFreight = obj.m_mustShipFreight;


}

#ifdef YS_TEST_MAIN
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardInvType test1;
    test1.SetBarCode("QWERTY");
    test1.SetDescription("A very nice object");
    test1.SetDepartment("Sales");
    test1.SetQuantOnHand(69);
    test1.SetQuantOnOrder(96);
    test1.SetReorderLevel(30);
   
    test1.SetItemType("Widget");
    test1.SetItemWeightLbs(1000.45);
    test1.SetTaxType(0.06);
    test1.SetVentorId(12345);
    test1.SetRetailPrice(34.23);
    test1.SetWholesalePrice(1000.12);
   
    //test1.AddBulkPrice();
    //test1.RemoveBulkPrice(unsigned int level);
   
    test1.SetOverSized(true);
    test1.SetShipFreight(false);
    
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
