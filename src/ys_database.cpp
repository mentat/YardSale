#include <string>
#include <sstream>

#include "ys_exception.h"
#include "ys_database.h"

#define OTL_ODBC_MYSQL
#ifndef _WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif

#include <otlv4.h>

using namespace std;

YardDatabase::YardDatabase(const string& dsn, const string& name, const string& pass) {
    m_db = 0;
    Init(dsn, name, pass);
}
  
YardDatabase::YardDatabase() {
    m_db = 0;
}

YardDatabase::~YardDatabase() 
{
    delete m_db;
  
}

bool YardDatabase::Init(const string& dsn, const string& name, const string& pass)
{
    if (m_db)
        delete m_db;
    
    m_db = new otl_connect();
    otl_connect::otl_initialize();
    
    m_dsn = dsn;
    m_name = name;
    m_pass = pass;
    /*
      int unf;
    otl_long_string test;
    otl_connect db; // connect object
    otl_connect::otl_initialize(); // init ODBC
    db.rlogon("UID=REPLACE;PWD=REPLACE;DSN=REPLACE"); // connect to ODBC
    otl_stream dbStream(50, "SELECT INV_SKU_Number, INV_Item_Description "
                        "FROM Inventory_Table WHERE INV_SKU_Number = '10000'",
			db);
    while (!dbStream.eof()){
	dbStream >> unf >> test;
	cout << test.v << " " << unf << endl;
    }
    db.logoff();*/
    
    return true;
}
   

int YardDatabase::GetStatus() const {
       
    return -1;
}

bool YardDatabase::connect(){
    
    if (!m_db)
        return false;

    stringstream loginString;
    loginString << "UID=" << m_name << ";PWD=" << m_pass 
        << ";DSN=" << m_dsn;
    
    try {
        
        m_db->rlogon(loginString.str().c_str()); // connect to ODBC
    
    } catch(otl_exception &e) {
        
        return false;
    }
    return true;
}

bool YardDatabase::disconnect()
{
    if (!m_db)
        return false;
    
    try {
        m_db->logoff();
    }
    catch( otl_exception &e) {
        return false;
    }
    return true;
}

vector<YardInvType> YardDatabase::InvSearchSKU(unsigned long sku) {
   
    if (!m_db)
        throw YardException("DB not initialized.");
    
    vector<YardInvType> invVec;
        
    stringstream sql;
    sql << "SELECT INV_SKU_Number, INV_Item_Description "
        "FROM Inventory_Table WHERE INV_SKU_Number = '" << sku << "'";
    
    otl_stream dbStream(50, sql.str().c_str(), *m_db);
    
    while (!dbStream.eof()){
        otl_long_string longStr;
        YardInvType temp;
        dbStream >> temp.m_skuNumber >> longStr;
        temp.m_itemDescription = (char*)longStr.v;
        invVec.push_back(temp);
    }
        
    return invVec;
}

vector<YardInvType> YardDatabase::InvGet(unsigned int num, unsigned int offset){
    
    if (!m_db)
        throw YardException("DB not initialized.");
    

    vector<YardInvType> m_invVec; 
   
    return m_invVec;
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_DB))

#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main(int argc, char ** argv)
{
    // argv[1] = name, [2] = pass, [3] = dsn

    YardDatabase testDB;
    
    if (argc == 4) {
        testDB.Init(argv[3], argv[1], argv[2]);
        VERIFY(testDB.connect(), true);
        
        vector<YardInvType> invObj;
        
        invObj = testDB.InvSearchSKU(1000);
    }
    
}
    
#endif
