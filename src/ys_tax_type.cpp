#include <sstream>
#include "ys_tax_type.h"

using namespace std;
   
string YardTaxType::ToString(const string& delim, bool quote) const {
    
    stringstream output;
    char q = '\'';
    output 
        << GetIdS() << delim
        << q << GetName() << q << delim 
        << GetPercentS();
    
    return output.str();    
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_TRANS_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    
    
    YardTaxType test1;
  
    test1.SetTaxId(1);
    test1.SetTaxName(
    
    /* add it to the transaction vector */
    currentTransaction.push_back(test1);
    
    /* calculate the subtotal */
    //subTotal =  SubTotal(currentTransaction);
    cout  << subTotal << endl;

    VERIFY(subTotal, test1.GetQuantity() * test1.GetItemSalePrice());

	YardTransType test2;

    /* ring up another item */
    test2.SetEmpKey(32345);
    test2.SetInvKey(323);
    test2.SetCustKey(423);
    test2.SetItemSalePrice(5.50);
    test2.SetTransID(1);
    test2.SetQuantity(1);
    test2.SetComment("Pleasure doing bizniss BEATCH");
    
    /* add to transaction vector */
    currentTransaction.push_back(test1);
    
    /* calculate the subtotal */
    //subTotal = SubTotal(currentTransaction);
    cout << subTotal << endl;
    
    VERIFY(subTotal, test2.GetQuantity() * test2.GetItemSalePrice());
    
    YardTransType test3;
    
    test3 = test2;
    VERIFY(test3.GetQuantity(), test2.GetQuantity());
    
    vector<YardTransType> copyArray;
    copyArray = currentTransaction;
    
    for(unsigned int i = 0; i < currentTransaction.size() ; i++){
        VERIFY(currentTransaction[i].GetQuantity(), copyArray[i].GetQuantity());
    }
    
    return failure;
}

#endif
