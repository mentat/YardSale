#include <string>
#include <sstream>
#include <memory>

#include "ys_log.h"
#include "ys_exception.h"
#include "ys_database.h"

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef _WIN32
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

vector<YardInvType> YardDatabase::FillFromStream(otl_stream * stream){
    
    vector<YardInvType> invVec;
    
    while (!stream->eof()){
       // otl_long_string longDesc;
       // otl_long_string bulkPrice;
       // otl_long_string comment;
        //char itemType[20+1];	
        //itemType[0]='\0';
            
        //char barCode[30+1];
        //barCode[0]='\0';
        
       // char department[30+1];
        char oversized, freight;
        otl_datetime lastRec;
    
        YardInvType temp;
        
        /*        
        	INV_SKU_Number			INT	NOT NULL,
	INV_Bar_Code_Number		varchar(30),
	INV_Item_Description		TEXT,
	INV_Item_Department		varchar(30),
	INV_Quantity_On_Hand		INT,
	INV_Quantity_On_Order		INT,
	INV_Reorder_Level		INT,
	INV_Reorder_Quantity		INT,
	INV_Item_Type			varchar(20),
	INV_REF_TAX_Tax_Type            INT NOT NULL,
	INV_REF_VND_Vendor_ID           INT NOT NULL,	
	INV_Retail_Price		DECIMAL(7,2),
	INV_Wholesale_Price		DECIMAL(7,2),
	INV_Bulk_Price			TEXT,
	INV_Date_Last_Received		DATETIME,
	INV_Weight_Pounds		FLOAT,
	INV_Oversized_Flag		enum('T','F'),
	INV_Ship_By_Freight		enum('T','F'),
	INV_Comment			TEXT,

        */
        
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
        
        //temp.m_itemDescription = (char*)longDesc.v;
        //temp.m_barCode = barCode;
        //temp.m_itemType = itemType;
        invVec.push_back(temp);
    }
    
    return invVec;
}

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
        
    return FillFromStream(dbStream.get());
}

vector<YardInvType> YardDatabase::InvGet() throw (YardDBException){
    
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    //THIS FUNCTION IS NOT DONE
    //throw YardDBException("This function is not implementated");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Table";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return FillFromStream(dbStream.get());
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
