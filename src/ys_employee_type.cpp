#include <string>
#include <sstream>

#include "ys_employee_type.h"

using namespace std;

// Copy constructor - always deep copy
YardEmployeeType::YardEmployeeType(const YardEmployeeType& copy)
{
    *this = copy;
    
}
    
// Assignment operator overload
YardEmployeeType& YardEmployeeType::operator=(const YardEmployeeType & copy)
{
    m_id = copy.m_id; // employee id number
     
    m_taxId = copy.m_taxId; // social in many cases
    m_firstName = copy.m_firstName; //first name
    m_middleName = copy.m_middleName; //middle name
    m_lastName = copy.m_lastName; //last name
    m_address = copy.m_address; 
    m_city = copy.m_city;
    m_zip = copy.m_zip;
    m_state = copy.m_state;
    m_phone = copy.m_phone;
    m_picture = copy.m_picture;
    m_signature = copy.m_signature;
    m_title = copy.m_title;
    return *this;
}

string YardEmployeeType::ToString(const string& delim) const {
    stringstream strm;
    strm 
        << m_id << delim 
        << m_taxId << delim
        << m_firstName << delim
        << m_middleName << delim
        << m_lastName << delim
        << m_address << delim
        << m_city << delim
        << m_zip << delim
        << m_state << delim
        << m_phone << delim
        << m_picture << delim
        << m_signature << delim
        << m_title;
    
    return strm.str();
}


void YardEmployeeType::SetTaxId(const string& id) {
    m_taxId = id;
}

void YardEmployeeType::SetFirstName(const string& name) {
    m_firstName = name;
}

void YardEmployeeType::SetMiddleName(const string& name) {
    m_middleName = name;
}

void YardEmployeeType::SetLastName(const string& name) {
    m_lastName = name;
}

void YardEmployeeType::SetAddress(const string& add) {
    m_address = add;
}

void YardEmployeeType::SetCity(const string& city) {
    m_city = city;
}

void YardEmployeeType::SetState(const string& state) {
    m_state = state;
}

void YardEmployeeType::SetZip(const string& zip) {
    m_zip = zip;
}
    
void YardEmployeeType::SetPhone(const string& phone) {
    m_phone = phone;
}

void YardEmployeeType::SetPicture(const string& loc) {
    m_picture = loc;
}

void YardEmployeeType::SetSig(const string& loc) {
    m_signature = loc;
}
    
void YardEmployeeType::SetTitle(const string& title) {
    m_title = title;
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
