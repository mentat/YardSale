#ifndef YS_EMPLOY_TYPE_H
#define YS_EMPLOY_TYPE_H

#include <string>
#include "ys_dbtype.h"

class YardDatabase;
    
using namespace std;

/**
 * This is a datatype to represent an Employee record.
 * See Database Tables.
 * @author Jesse Lovelace
 */
class YardEmployType: public YardDBType {
 public:
    friend class YardDatabase;
     
    YardEmployType(){}
        
    /// Copy constructor - always deep copy
    YardEmployType(const YardEmployType& copy);
    
    /// Assignment operator overload
    YardEmployType& operator=(const YardEmployType & copy);
        
    // Getors
    
    unsigned long GetId() const { return m_id; }
    string GetTaxId() const { return m_taxId; }
    string GetFirst() const { return m_firstName; }
    string GetMiddle() const { return m_middleName; }
    string GetLast() const { return m_lastName; }
    string GetAddress() const { return m_address; }
    string GetCity() const { return m_city; }
    string GetState() const { return m_state; }
    string GetZip() const { return m_zip; }
    string GetPhone() const { return m_phone; }
    
    /// Returns location of employee picture on datacenter
    /// @todo Define what a datacenter is
    string GetPicLocal() const { return m_picture; }
    
    /// Returns the location of the employee signature file
    string GetSigLocal() const { return m_signature; }
    
    // Settors
    /// @note You cannot set the employee ID, it is set by the DB
    /// @todo Maybe have all these return boolean which says if the set
    ///  violates size limitations.
    void SetTaxId(const string& id);
    void SetFirstName(const string& name);
    void SetMiddleName(const string& name);
    void SetLastName(const string& name);
    void SetAddress(const string& add);
    void SetCity(const string& city);
    void SetState(const string& state);
    void SetZip(const string& zip);
    
    void SetPhone(const string& phone);
    void SetPicture(const string& loc);
    void SetSig(const string& loc);
    
    void SetTitle(const string& title);

 private:
    
    unsigned long m_id; // employee id number
     
    string m_taxId; // social in many cases
    string m_firstName; //first name
    string m_middleName; //middle name
    string m_lastNmae; //last name
    string m_address; 
    string m_city;
    string m_zip;
    string m_state;
    string m_phone;
 
    string m_picture;
    string m_signature;

    string m_title; // for grouping
    
};

#endif
