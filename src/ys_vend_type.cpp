#include <sstream>

#include "ys_vend_type.h"

using namespace std;

string YardVendType::ToString(const string& delim, bool quote) const {
    
    stringstream output;
    char q = '\'';
    
    output << GetIdS() << delim 
        << q << GetName() << q << delim 
        << q << GetAddress() << q << delim 
        << q << GetCity() << q << delim 
        << q << GetState() << q << delim 
        << q << GetZip() << q << delim 
        << q << GetPhone() << q << delim 
        << q << GetSalesRep() << q << delim 
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
    return failure;
}

#endif
