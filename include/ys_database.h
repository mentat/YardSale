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

using namespace std;

// Forward declarations for speed -jll
class YardDBConfig;
class wxDb;
class wxDbTable;
class wxDbConnectInf;


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
    YardDatabase(const wxString& dsn, const wxString& name, const wxString& pass);
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
    bool Init(const wxString& dsn, const wxString& name, const wxString& pass);
    
    /** Destructor **/
    ~YardDatabase();
    
    /** 
     * This connects to the database with the options specified
     * above.  Dumbass.
     * @return True if connection was successful, @sa GetStatus    
     */
    bool connect();
     
    /**
     * Get Database Status reported by ODBC 
     * @return An integer corresponding with the error code
     */     
    int GetStatus() const;
     

    /*------------Inventory-------------*/
    
    /**
     * Find all inventory matches of keyword search
     * @note This could be dangerous, need to limit all returns to some set
     *  value (or configured value).
     * @param keyword A text string to search for.
     * @return A std::vector of YardInvType objects
     */
    vector<YardInvType> InvSearchKeyword(const unsigned long &sku);
    
    /**
     * Get a batch of inventory items.
     * @param num The number of items to get.
     * @param offset The item index to start at.
     * @return A std::vector of YardInvType objects
     */
    vector<YardInvType> InvGet(unsigned int num, unsigned int offset);
    
 private:
    wxDb * m_db;
    wxDbTable * m_table;
    wxDbConnectInf * m_connectInfo;
    YardInvType * m_inv;
};

#endif
