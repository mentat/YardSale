#include "ys_inv_type.h"

void YardInvType::SetItemType(const wxString& str) {
    
    
}

void YardInvType::SetDepartment(const wxString& str) {
    
}
        
void YardInvType::SetBarCode(const wxString& str) {
    
}
   
YardInvType::YardInvType(const YardInvType& obj) {
    
    *this = obj;
    
}
    
YardInvType& YardInvType::operator=(const YardInvType& obj) {
    
    m_skuNumber = obj.m_skuNumber;
//    wxChar m_barCode[30+1];
    m_itemDescription = obj.m_itemDescription;
   // wxChar m_itemDepartment[30+1];
    m_quantityOnHand = obj.m_quantityOnHand;
    m_quantityOnOrder = obj.m_quantityOnOrder;
    m_reorderLevel = obj.m_reorderLevel;
    m_reorderQuantity = obj.m_reorderQuantity;
    //wxChar m_itemType[30+1];
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
