#include <sstream>
#include "ys_group.h"

using namespace std;
   
string YardGroup::ToString(const string& delim, bool quote) const {
    
    stringstream output;
    char q = '\'';
    output 
        << GetIdS() << delim
        << q << GetName() << q;
    
    return output.str();    
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_GROUP_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{   
    YardGroup test1;
    
    test1.SetId(1000);
    VERIFY(test1.GetId(), 1000);
    
    test1.SetName("Z mod n"); // ;)
    VERIFY(test1.GetName(), string("Z mod n"));
    
    return failure;
}

#endif
