#include <string>
#include <sstream>

#include "ys_employee_type.h"

using namespace std;

string YardEmployeeType::ToString(const string& delim, bool quotes) const {
    stringstream strm;
    char q = '\'';
    
    strm 
        << child("EMP_ID_Number").data() << delim 
        << child("EMP_Social_Security_Number").data() << delim
        << q << child("EMP_First_Name").data() << q << delim
        << q << child("EMP_Middle_Name").data() << q << delim
        << q << child("EMP_Last_Name").data() << q << delim
        << q << child("EMP_Address").data() << q << delim
        << q << child("EMP_Phone_Number").data() << q << delim
        << q << child("EMP_City").data() << q << delim
        << q << child("EMP_Zip").data() << q << delim
        << q << child("EMP_Picture").data() << q << delim
        << q << child("EMP_Signature").data() << q;
    
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
