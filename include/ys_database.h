/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef YS_DATABASE_H
#define YS_DATABASE_H

#include "ys_exception.h"
#include <vector>
#include <map>
#include <string>

using namespace std;

// Forward declarations for speed -jll
#include "ys_group.h"
#include "ys_inv_type.h"
#include "ys_trans_type.h"
#include "ys_employee_type.h"
#include "ys_cust_type.h"
#include "ys_vend_type.h"
#include "ys_trans_type.h"
#include "ys_package_type.h"
#include "ys_shipping_type.h"
#include "ys_carrier_type.h"
#include "ys_tax_type.h"
    
class otl_connect;
class otl_stream;

/**
 * @defgroup database Database Related Documentation
 */

/**
 * @ingroup datebase
 *
 * This is the main database backend which does all translation from
 * OO calls to SQL/ODBC.
 * @sa YardInvType 
 * @author Jesse Lovelace
 * @version \$ Revision: $$
 */
class YardDatabase {
    public:
    
    /** 
     * Constructor
     * @param dsn Name of data source
     * @param name Name of the user for DB
     * @param pass Password for DB
     */
    YardDatabase(const string& name, const string& pass, const string& dsn);
    //YardDatabase(const YardDBConfig& config);  
    
    /**
     * Default constructor.
     */
    YardDatabase();

    /** 
     * Initialize or re-initialize db
     * @param dsn Name of data source
     * @param name Name of the user for DB
     * @param pass Password for DB
     */    
    bool Init(const string& name, const string& pass, const string& dsn);
    
    /** Destructor **/
    ~YardDatabase();
    
    /** 
     * This connects to the database with the options specified
     * above.  Dumbass.
     * @return True if connection was successful, @sa GetStatus
     * @throws YardDBException
     */
    bool connect();
    
    /**
     * Disconnects from the DB
     * @return False if not connected to DB in the first place
     * @throws YardDBException
     */
    bool disconnect();
     
    /**
     * Get Database Status reported by ODBC 
     * @return An integer corresponding with the error code
     */     
    int GetStatus() const;
     

    bool IsConnected() const;

    /*------------Inventory-------------*/
    
    /**
     * Find all inventory matches of SKU search
     * @note This could be dangerous, need to limit all returns to some set
     *  value (or configured value).
     * @param keyword A text string to search for.
     * @return A std::vector of YardInvType objects
     * @throws YardException if databae not initialized
     */
    vector<YardInvType> InventorySearchSKU(const string& sku);
    
    /**
     * Get a batch of inventory items.
     * @return A std::vector of YardInvType objects
     * @throws YardException if database not initialized
     */
    vector<YardInvType> InventoryGetAll() const;
    vector<YardInvType> InventoryGetInGroup(long groupid) const;
    YardInvType InventoryGet(long key) const;
    void InventoryUpdate(const YardInvType& inv);
    
    /**
     * Add an item to the inventory.
     */
    long InventoryAdd(const YardInvType& item);
    
    /*-----------Customers----------------*/

    long CustomerAdd(const YardCustType& newCust);
    vector<YardCustType> CustomerGetAll();
    vector<YardCustType> CustomerSearch(const YardCustType& criteria);
    void CustomerDisable(long key);
    YardCustType CustomerGet(long key);
    
    /// Check for key in cust so will not try to edit non-existant customer
    void CustomerUpdate(const YardCustType& cust);

    /*----------Employee-------------------*/
    
    long EmployeeAdd(const YardEmployeeType& employ);
    void EmployeeDisable(long key);
    YardEmployeeType EmployeeGet(long key) const;
    void EmployeeUpdate(const YardEmployeeType& employ);
    
    vector<YardEmployeeType> EmployeeGetAll() const;
    
    /*----------Vendors--------------------*/
    
    vector<YardVendType> VendorGetAll() const;
    YardVendType VendorGet(long key) const;
    
    long VendorAdd(const YardVendType& vendor);
    
    /*--------Carrier-------------------*/
    
    vector<YardCarrierType> CarrierGetAll() const;
    YardCarrierType CarrierGet(long key) const;
    long CarrierAdd(const YardCarrierType& carrier);
    vector<YardShipType> CarrierGetShippingTypes(long carrierId) const;
    void CarrierAddShippingType(long carrierId, const YardShipType& shiptype);    
    void CarrierDisableShippingType(long carrierId, int shipId);
    
    /*---------Transaction----------------*/
    
    /// throws something if not work
    void TransactionAdd(const vector<YardTransType>& transaction);
    vector<YardTransType> TransactionGet(long transactionId) const;
    
    // return transaction id(s)
    vector<long> TransactionSearch(int employeeId, int custId, int inventoryItem) const;
    
    /*--------Tax Types-----------------*/
    
    vector<YardTaxType> TaxTypeGetAll() const;
    long TaxTypeAdd(const YardTaxType& taxtype);
    void TaxTypeUpdate(const YardTaxType& taxtype);
    YardTaxType TaxTypeGet(long key) const;
    
    
    /*-------Group Type----------------*/
    
    vector<YardGroup> GroupGetAll() const;
    YardGroup GroupGet(long key) const;
    long GroupAdd(const YardGroup& group);
        
        
    /*---------ACLs--------------------*/
    map<string,string> ACLGetAll() const;
    void ACLAdd(const string& name, const string& desc);
    string ACLGet(const string& name); 


    /*-----------Reports--------------*/
    string ReportXML(const string& sql, long& count) const;
    
    
    /*----------GENERIC---------------*/
    
    void GenericUpdate(const string& table, const string& values);
    void GenericInsert(const string& table, const string& value);
        
    /* helpers */
    static string tab(int level);
    static string escape(const string& esc);
    /// @param stream The otl_stream being passed in
    /// @param record The name of the individual record (most likely the table name
    string ToXML(otl_stream * stream, const string& record) const;
    
 private:

    template<typename T>
    vector<T> XMLFromStream(otl_stream * stream, const string& table) const {
        vector<T> list;
        
        while (!stream->eof()){
            T temp(ToXML(stream, table));            
            list.push_back(temp);
        }
        
        return list;
    }     

    template<typename T>
    T XMLFromStreamSingle(otl_stream * stream, const string& table) const {
        T temp(ToXML(stream, table));
        return temp;
    }      
 
    otl_connect * m_db;
    string m_dsn;
    string m_name;
    string m_pass;
    //otl_stream * m_invGetStream;
     
};

#endif
