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
     * @param dsn ?
     * @param name Name of the database
     * @param pass Password for DB
     */
    YardDatabase(const wxString& dsn, const wxString& name, const wxString& pass);
    //YardDatabase(const YardDBConfig& config);  
    
    /**
     * Default constructor.
     */
    YardDatabase();
    
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
