#include <sstream>

#include "ys_cust_type.h"

using namespace std;
   
string YardCustType::ToString(const string& delim, bool quotes) const {
    
    stringstream output;
    char q = '\'';
    output << GetAccountNumber() << delim 
        << q << GetFirstName() << q << delim 
        << q << GetMiddleName() << q << delim 
        << q << GetLastName() << q << delim 
        << q << GetAddress() << q << delim
        << q << GetPhone() << q << delim 
        << q << GetCity() << q << delim 
        << q << GetZip() << q << delim
        << q << GetCreditCardNumber() << q << delim
        << q << GetCreditCardExpiration() << q << delim
        << q << GetCreditCardName() << q << delim
        << q << GetSignaturePath() << q << delim
        << q << GetPhoto() << q;
    return output.str();
        
}
    
#if (defined(YS_TEST_MAIN) || defined(YS_TEST_CUST_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardCustType test1;
    
    test1.SetAccountNumber(12345);
    test1.SetCustFirstName("Doh");
    test1.SetCustMiddleName("Nuts");
    test1.SetCustLastName("AreGood");
    //test1.SetCustAddress("<ADDRESS><1>Somewhere</1><2>Else</2></ADDRESS>");
    test1.SetCustPhoneNumber("919.222.3333");
    test1.SetCustCity("SouthPark");
    test1.SetCustZip("80120");
    test1.SetCustCreditCardNumber("0000222230304444");
    test1.SetCustCreditCardExpiration("12/04");
    test1.SetCustCreditCardName("Doh Nuts AreGood");
    
    
    YardCustType test2(test1);
    
    VERIFY(test2.GetAccountNumber(), test1.GetAccountNumber());
    
    YardCustType test3;
    
    test3 = test2;
    VERIFY(test3.GetAccountNumber(), test2.GetAccountNumber());
    VERIFY(test2.GetCustomerPhone(), test1.GetCustomerPhone());


    vector<YardCustType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetAccountNumber(), anArray[2].GetAccountNumber());
    
    vector<YardCustType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetAccountNumber(), copyArray[0].GetAccountNumber());
    
    return failure;
}

#endif
