#include <sstream>

#include "ys_vend_type.h"

using namespace std;

string YardVendType::ToString(const string& delim, bool quote) const {
    
    stringstream output;
    char q = '\'';
    
    output << GetId() << delim 
        << q << GetName() << q << delim 
        << q << GetAddress() << q << delim 
        << q << GetCity() << q << delim 
        << q << GetState() << q << delim 
        << q << GetZip() << q << delim 
        << q << GetPhone() << q << delim 
        << q << GetSalesRep() << q << delim 
        << q << GetSpecialty() << q << delim
        << q << GetEmail() << q << delim
        << q << GetHomePage() << q;
    
    return output.str();
        
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_VEND_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardVendType test1;
    
    test1.SetName("ACME");
    VERIFY(test1.GetName(), string("ACME"));    

    test1.SetAddress("29 Lynwood");
    VERIFY(test1.GetAddress(), string("29 Lynwood"));
    
    test1.SetCity("A-Town");
    VERIFY(test1.GetCity(), string("A-Town"));
    
    test1.SetState("NC"); 
    VERIFY(test1.GetState(), string("NC"));
    
    test1.SetZip("27777");
    VERIFY(test1.GetZip(), string("27777"));
    
    test1.SetPhone("919-999-8888");
    VERIFY(test1.GetPhone(), string("919-999-8888"));
    
    test1.SetSalesRep("Bob");
    VERIFY(test1.GetSalesRep(), string("Bob"));

    test1.SetSpecialty("Pics");
    VERIFY(test1.GetSpecialty(), string("Pics"));
    
    test1.SetEmail("acme@hotmail.com");
    VERIFY(test1.GetEmail(), string("acme@hotmail.com"));
    
    test1.SetHomePage("http://yardsale.sf.net");
    VERIFY(test1.GetHomePage(), string("http://yardsale.sf.net"));    
    
    return failure;
}

#endif
