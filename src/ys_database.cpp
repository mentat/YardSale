#include <string>
#include <sstream>
#include <memory>

#include "ys_exception.h"
#include "ys_database.h"
#include "ys_log.h"

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
        
        //throw YardDBException((char *)e.msg, (char*)e.stm_text);
        throw YardDBException("Cannot connect to DB, I dont know why.")
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
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
        return false;
    }
    return true;
}

vector<YardInvType> YardDatabase::InvSearchSKU(unsigned long sku) {
   
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    vector<YardInvType> invVec;
        
    stringstream sql;
    sql << "SELECT INV_SKU_Number, INV_Item_Type, "
        "INV_Item_Description, INV_Bar_Code_Number, "
        "INV_Retail_Price, INV_Wholesale_Price "
        "FROM Inventory_Table WHERE INV_SKU_Number = '" << sku << "'";
    
    auto_ptr<otl_stream> dbStream;

    try {
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) {
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    while (!dbStream->eof()){
        otl_long_string longDesc;
        
        char itemType[20+1];	
        itemType[0]='\0';
            
        char barCode[30+1];
        barCode[0]='\0';
            
        YardInvType temp;
        
        try {
            *dbStream >> temp.m_skuNumber >> itemType >> longDesc 
                 >> barCode >> temp.m_retailPrice 
                 >> temp.m_wholesalePrice;
        } catch (otl_exception &e) {
            throw YardDBException((char *)e.msg, (char*)e.stm_text);
        }
        
        temp.m_itemDescription = (char*)longDesc.v;
        temp.m_barCode = barCode;
        temp.m_itemType = itemType;
        invVec.push_back(temp);
    }
        
    return invVec;
}

vector<YardInvType> YardDatabase::InvGet(unsigned int num, unsigned int offset){
    
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
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
    int numItems = 0;

    if (argc == 4) {
        testDB.Init(argv[3], argv[1], argv[2]);
        VERIFY(testDB.connect(), true);
        
        vector<YardInvType> invObj;

        /* Search for an SKU that probably doesn't exist,
	   test to see if the shit bombs when we try to print */
        invObj = testDB.InvSearchSKU(99999);
	if (invObj.size()){
	    numItems = invObj.size();
	    for (int ii = 0; ii < numItems; ii++){
/* NO!  BAD John!  Baaad. */
// 		wxDbLog("%s, %s, %s, %f, %f.\n",invObj[ii].GetItemType(), 
// 			invObj[ii].GetDescription(), invObj[ii].GetBarCode(), 
// 			invObj[ii].GetRetailPrice(), invObj[ii].GetWholesalePrice());

		cout << " " << invObj[ii].GetItemType() \
		     << " " << invObj[ii].GetDescription() << " " \
		     << invObj[ii].GetBarCode() << " " << invObj[ii].GetRetailPrice() \
		     << " " << invObj[ii].GetWholesalePrice() << endl;
	    }
	}
        
        /* Search for an SKU that we know exists, and see if that prints. */
        invObj = testDB.InvSearchSKU(10000);
	if (invObj.size()){
	    numItems = invObj.size();
	    for (int ii = 0; ii < numItems; ii++){
		cout << " " << invObj[ii].GetItemType() \
		     << " " << invObj[ii].GetDescription() << " " \
		     << invObj[ii].GetBarCode() << " " << invObj[ii].GetRetailPrice() \
		     << " " << invObj[ii].GetWholesalePrice() << endl;
	    }
	}
    }
}
    
#endif
