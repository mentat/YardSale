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
    return failure;
}

#endif
