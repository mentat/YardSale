#include <string>
#include <sstream>
#include <memory>

#include "ys_log.h"
#include "ys_exception.h"
#include "ys_database.h"

#include "ys_inv_type.h"
#include "ys_trans_type.h"
#include "ys_employee_type.h"
#include "ys_cust_type.h"
#include "ys_vend_type.h"
#include "ys_trans_type.h"
#include "ys_package_type.h"

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif

#include <otlv4.h>

using namespace std;
//using namespace odbc;

YardDatabase::YardDatabase(const string& name, const string& pass, const string& dsn) {
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

bool YardDatabase::IsConnected() const 
{
    if (!m_db)
        return false;
    
    if (m_db->connected != 0)
        return true;
    return false;
    
}

bool YardDatabase::Init(const string& name, const string& pass, const string& dsn)
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
    
    //wxLogDB(loginString.str().c_str());
    
    try {
        
        m_db->rlogon(loginString.str().c_str()); // connect to ODBC
    
    } catch(otl_exception &e) {
        
        try{ m_db->logoff(); } catch(otl_connect&){}
        throw YardDBException((char *)e.msg);
        return false;
    }        

    return true;
}

bool YardDatabase::disconnect()
{
    if (!m_db)
    {   
        wxLogError(wxT("DB not allocated in disconnect()"));
        return false;
    }
    
    try {
        m_db->logoff();
    }
    catch( otl_exception &e) {
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
        return false;
    }
    return true;
}
#if 0
vector<YardInvType> YardDatabase::FillFromStream(otl_stream * stream){
    
    vector<YardInvType> invVec;
    
    while (!stream->eof()){
        
        char oversized, freight;
        otl_datetime lastRec;
    
        YardInvType temp;
        
        try {
            *stream 
                >> temp.m_skuNumber 
                >> temp.m_barCode 
                >> temp.m_itemDescription
                >> temp.m_itemDepartment 
                >> temp.m_quantityOnHand
                >> temp.m_quantityOnOrder
                >> temp.m_reorderLevel
                >> temp.m_reorderQuantity
                >> temp.m_itemType >> temp.m_taxType
                >> temp.m_vendorId
                >> temp.m_retailPrice
                >> temp.m_wholesalePrice
                >> temp.m_bulkPrice
                >> lastRec
                >> temp.m_itemWeight
                >> oversized
                >> freight
                >> temp.m_comment;
            
            if (oversized == 'F')
                temp.m_oversized = false;
            else 
                temp.m_oversized = true;
            
            if (freight == 'F')
                temp.m_mustShipFreight = false;
            else
                temp.m_mustShipFreight = true;
            
        } catch (otl_exception &e) {
            throw YardDBException((char *)e.msg, (char*)e.stm_text, (char*)e.var_info);
        }
        
        invVec.push_back(temp);
    }
    
    return invVec;
}
#endif

vector<YardInvType> YardDatabase::InvSearchSKU(unsigned long sku) {
   
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Table WHERE INV_SKU_Number = '" << sku << "'";
    
    auto_ptr<otl_stream> dbStream;
    
    try {
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) {
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return FillFromStream<YardInvType>(dbStream.get());
}

vector<YardInvType> YardDatabase::InvGet() throw (YardDBException){
    
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Table";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return FillFromStream<YardInvType>(dbStream.get());
}

int YardDatabase::AddInventoryItem(const YardInvType& item)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO Inventory_Table values(" << item.ToString() << ");";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    return 0;
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
        
        cout << "Name: " << argv[1] << " Pass: " << argv[2] << " DSN: "
            << argv[3] << endl;
        
        testDB.Init(argv[1], argv[2], argv[3]);
        
        try {
            testDB.connect();
        } 
        catch (YardDBException &e) 
        {
            cout << e.GetWhat() << endl;
            return 1;
        }
        
        vector<YardInvType> invObj;

        /* Search for an SKU that probably doesn't exist,
	   test to see if the shit bombs when we try to print */
        
        try {
            invObj = testDB.InvSearchSKU(99999);
        }
        catch (YardDBException &e)
        {
            cout << e.GetWhat() << endl;
            return 1;
        }
                      
        for (unsigned int ii = 0; ii < invObj.size(); ii++){
            cout << "----------" << invObj[ii].ToString() << "----------" << endl;
        }

        
        /* Search for an SKU that we know exists, and see if that prints. */
        try {
            invObj = testDB.InvSearchSKU(10000);
        }
        catch (YardDBException &e) {
            cout << e.GetWhat() << endl << e.GetSQL() 
                << endl << e.GetVarInfo() << endl;
            return 1;
        }
          
        for (unsigned int ii = 0; ii < invObj.size(); ii++){
            cout << "-------" << invObj[ii].ToString() << "-------" << endl;
        }
        
        try {
            invObj = testDB.InvGet();
        }
        catch (YardDBException &e) {
            cout << e.GetWhat() << endl << e.GetSQL() 
                << endl << e.GetVarInfo() << endl;
            return 1;
        }
          
        for (unsigned int ii = 0; ii < invObj.size(); ii++){
            cout << "-------" << invObj[ii].ToString() << "-------" << endl;
        }
    }
}
    
#endif
