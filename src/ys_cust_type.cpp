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
        << q << GetSigLocal() << q << delim
        << q << GetPicLocal() << q << delim
        << q << GetSince().ToString() << q << delim
        << GetHashS();
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
    
    test1.SetAccountNumber(1234567);
    VERIFY(test1.GetAccountNumber(), 1234567);
    
    test1.SetFirstName("Ralph");
    VERIFY(test1.GetFirstName(), string("Ralph"));
    
    test1.SetMiddleName("Francis");
    VERIFY(test1.GetMiddleName(), string("Francis"))
    
    test1.SetLastName("Wiggum");
    VERIFY(test1.GetLastName(), string("Wiggum"));
    
    test1.SetAddress("4201 Evergreen Terrace");
    VERIFY(test1.GetAddress(), string("4201 Evergreen Terrace"));
    
    test1.SetPhoneNumber("999 999 9999");
    VERIFY(test1.GetPhone(), string("999 999 9999"));
   
    test1.SetCity("Sanford");
    VERIFY(test1.GetCity(), string("Sanford"));
    
    test1.SetZip("28146");
    VERIFY(test1.GetZip(), string("28146"));
    
    test1.SetCreditCardNumber("1111 2222 3333 4444");
    VERIFY(test1.GetCreditCardNumber(), string("1111 2222 3333 4444"));
    
    test1.SetCreditCardExpiration("04 07");
    VERIFY(test1.GetCreditCardExpiration(), string("04 07"));
    
    test1.SetCreditCardName("Big Daddy Mike");
    VERIFY(test1.GetCreditCardName(), string("Big Daddy Mike"));
   
    test1.SetSignature("i don't understand");
    VERIFY(test1.GetSignaturePath(), string("i don't understand"));

    test1.SetPhoto("what??");
    VERIFY(test1.GetPhoto(), string("what??"))
 
#if 0 
    vector<XMLNode> v = test1.children();
   
    for (int i = 0; i < v.size(); i++)
    {
        cout << v[i].name() << endl;
    }
    
    cout << string(test1) << endl;
#endif
    YardCustType test2(test1);
    
    VERIFY(test2.GetAccountNumber(), test1.GetAccountNumber());
    
    YardCustType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetFirstName(), test2.GetFirstName());
    VERIFY(test3.GetLastName(), test2.GetLastName());


    vector<YardCustType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetAddress(), anArray[2].GetAddress());
    
    vector<YardCustType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetPhone(), copyArray[0].GetPhone());
      
    return failure;
}

#endif
