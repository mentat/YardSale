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

#include "ys_inv_type.h"
#include "ys_exception.h"
#include <vector>
#include <string>

using namespace std;

// Forward declarations for speed -jll
class YardDBConfig;
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
    vector<YardInvType> InvSearchSKU(unsigned long sku);
    
    /**
     * Get a batch of inventory items.
     * @return A std::vector of YardInvType objects
     * @throws YardException if database not initialized
     */
    vector<YardInvType> InvGet() throw (YardDBException);
    
    /**
     * Add an item to the inventory.
     */
    int AddInventoryItem(const YardInvType& item);
    
    /*-----------Customers----------------*/
#if 0
    int AddCustomer(const YardCustType& newCust);
    vector<YardCustType> CustomerGetList();
    vector<YardCustType> CustomerSearch(const YardCustType& criteria);
    void DisableCustomer(int key);
    YardCustType GetCustomer(int key);
    
    /// Check for key in cust so will not try to edit non-existant customer
    void EditCustomer(const YardCustType& cust);
#endif
    /*----------Employee-------------------*/
    
    
    
 private:
     
    template<class T>
    vector<T> FillFromStream(otl_stream * stream) {
        vector<T> list;
        
        while (!stream->eof()){
            T temp;
        
            temp.FillFromStream(stream); 
            
            list.push_back(temp);
        }
        
        return list;
    }
        
 
    otl_connect * m_db;
    string m_dsn;
    string m_name;
    string m_pass;
    otl_stream * m_invGetStream;
     
};

#endif
