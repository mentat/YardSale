#include <sstream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif


#include "otlv4.h"
#include "ys_inv_type.h"
#include "ys_exception.h"

using namespace std;

void YardInvType::SetItemType(const string& str) {
    m_itemType = str;
    
}

void YardInvType::SetDepartment(const string& str) {
    m_itemDepartment = str;
}
        
void YardInvType::SetBarCode(const string& str) {
    m_barCode = str;
}
   
YardInvType::YardInvType(const YardInvType& obj) {
    
    *this = obj;
    
}

string YardInvType::ToString(const string& delim) const {
    
    stringstream output;
    output 
        << '\'' << m_skuNumber << '\'' << delim 
        << '\'' << m_barCode << '\'' << delim 
        << '\'' << m_itemDescription << '\'' << delim 
        << '\'' << m_itemDepartment << '\'' << delim 
        << m_quantityOnHand << delim 
        << m_quantityOnOrder << delim 
        << m_reorderLevel << delim 
        << m_reorderQuantity << delim 
        << '\'' << m_itemType << '\'' << delim 
        << m_taxType << delim
        << m_vendorId << delim 
        << m_retailPrice << delim 
        << m_wholesalePrice << delim 
        << m_bulkPrice << delim;
    if (m_key == -1)
        output << "now()" << delim;
    else
        output << m_dateLastReceived.ToString() << delim;
        
    output << m_itemWeight << delim;
    
    if (m_oversized)
        output << "'T'";
    else
        output << "'F'";
    output << delim;
    
    if (m_mustShipFreight)
        output << "'T'";
    else
        output << "'F'";
    output << delim;
    
    output << '\'' << m_comment << '\'';
     
    return output.str();
        
}

void YardInvType::FillFromStream(otl_stream * stream)
{  
    if (!stream)
        return;
    /// maybe throw here
    
    char oversized, freight;
    otl_datetime lastRec;
    
    YardInvType temp;
        
    try {
        *stream 
            >> m_skuNumber 
            >> m_barCode 
            >> m_itemDescription
            >> m_itemDepartment 
            >> m_quantityOnHand
            >> m_quantityOnOrder
            >> m_reorderLevel
            >> m_reorderQuantity
            >> m_itemType >> m_taxType
            >> m_vendorId
            >> m_retailPrice
            >> m_wholesalePrice
            >> m_bulkPrice
            >> lastRec
            >> m_itemWeight
            >> oversized
            >> freight
            >> m_comment;
            
        if (oversized == 'F')
            m_oversized = false;
        else 
            m_oversized = true;
            
        if (freight == 'F')
            m_mustShipFreight = false;
        else
            m_mustShipFreight = true;
            
    } catch (otl_exception &e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
    }
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
    m_bulkPrice = obj.m_bulkPrice;
    m_dateLastReceived = obj.m_dateLastReceived;
    m_comment = obj.m_comment;
    
    m_oversized = obj.m_oversized;
    m_mustShipFreight = obj.m_mustShipFreight;

    return *this;
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
    test1.SetDescription("A very nice object");
    test1.SetDepartment("Sales");
    test1.SetQuantOnHand(69);
    test1.SetQuantOnOrder(96);
    test1.SetReorderLevel(30);
   
    test1.SetItemType("Widget");
    test1.SetItemWeightLbs(1000.45);
    test1.SetTaxType(0);
//    test1.SetVentorId(12345);
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
    
    cout << test3.ToString();
    
    return failure;
}

#endif
