#ifndef YS_DATABASE_H
#define YS_DATABSE_H

#include "ys_inv_type.h"

class YardDBConfig{}

/**
 * This is the main database backend which does all translation from
 * OO calls to SQL/ODBC.
 * @sa YardInvType 
 */
class YardDatabase {
    public:
        
    YardDatabase(const string& name, const string& pass);
    //YardDatabase(const YardDBConfig& config);  
    YardDatabase();
    
    /*------------Inventory-------------*/
    
    /**
     * Find all inventory matches of keyword search
     * @note This could be dangerous, need to limit all returns to some set
     *  value (or configured value).
     * @param keyword A text string to search for.
     * @return A std::vector of YardInvType objects
     */
    vector<YardInvType> InvSearchKeyword(const string& keyword);
    
    /**
     * Get a batch of inventory items.
     * @param num The number of items to get.
     * @param offset The item index to start at.
     * @return A std::vector of YardInvType objects
     */
    vector<YardInvType> InvGet(unsigned int num, unsigned int offset);
    
    
};


#endif
