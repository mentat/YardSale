#include <string>
#include <sstream>

#include "ys_employee_type.h"

using namespace std;

string YardEmployeeType::ToString(const string& delim, bool quotes) const {
    stringstream strm;
    char q = '\'';
    
    strm 
        << GetId() << delim 
        << q << GetUserName() << q << delim
        << GetTaxId() << delim
        << q << GetFirst() << q << delim
        << q << GetMiddle() << q << delim
        << q << GetLast() << q << delim
        << q << GetAddress() << q << delim
        << q << GetPhone() << q << delim
        << q << GetCity() << q << delim
        << q << GetZip() << q << delim
        << q << GetPicLocal() << q << delim
        << q << GetSigLocal() << q << delim
        << q << GetACL() << q << delim
        << "1" << delim
        << q << GetSince().ToString() << q;
    
    return strm.str();
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_EMPLOYEE_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardEmployeeType employee;
    
    employee.SetFirstName("jesse");
    employee.SetMiddleName("is");
    employee.SetLastName("cool");
    employee.SetTaxId("123456789");
    employee.SetAddress("29 Lynwood");
    employee.SetState("North Carolina");
    employee.SetZip("12345");
    employee.SetPhone("999-999-9999");
    employee.SetPicture("mypic.png");
    employee.SetSig("mysig.png");
    employee.SetTitle("Manager");
    
    YardEmployeeType emp1(employee);
    
    VERIFY(employee.GetFirst(), emp1.GetFirst());
    VERIFY(employee.GetLast(), emp1.GetLast());
    
    YardEmployeeType emp2;
    
    emp2 = emp1;
    
    VERIFY(emp2.GetZip(), emp1.GetZip());
    VERIFY(emp2.GetAddress(), employee.GetAddress());
    
    return failure;
    
}

#endif
