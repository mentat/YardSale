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
#include <vector>
#include <string>

using namespace std;

// Forward declarations for speed -jll
class YardDBConfig;
class otl_connect;
    
/**
 * @defgroup database Database Related Documentation
 */

/**
 * @ingroup datebase
 *
 * This is the main database backend which does all translation from
 * OO calls to SQL/ODBC.
 * @sa YardInvType 
 */
class YardDatabase {
    public:
    
    /** 
     * Constructor
     * @param dsn Name of data source
     * @param name Name of the user for DB
     * @param pass Password for DB
     */
    YardDatabase(const string& dsn, const string& name, const string& pass);
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
    bool Init(const string& dsn, const string& name, const string& pass);
    
    /** Destructor **/
    ~YardDatabase();
    
    /** 
     * This connects to the database with the options specified
     * above.  Dumbass.
     * @return True if connection was successful, @sa GetStatus    
     */
    bool connect();
    
    bool disconnect();
     
    /**
     * Get Database Status reported by ODBC 
     * @return An integer corresponding with the error code
     */     
    int GetStatus() const;
     

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
     * @param num The number of items to get.
     * @param offset The item index to start at.
     * @return A std::vector of YardInvType objects
     * @throws YardException if database not initialized
     */
    vector<YardInvType> InvGet(unsigned int num, unsigned int offset);
    
 private:
    otl_connect * m_db;
    string m_dsn;
    string m_name;
    string m_pass;
    otl_stream m_invGetStream;
     
};

#endif
