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

vector<YardInvType> YardDatabase::InventorySearchSKU(unsigned long sku) {
   
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
        
    return XMLFromStream<YardInvType>(dbStream.get(), "Inventory_Table");
}

vector<YardEmployeeType> YardDatabase::EmployeeGetAll() const{
    
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Employee_Table";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    } catch (otl_exception &e) { // so just get otl exceptions
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    return XMLFromStream<YardEmployeeType>(dbStream.get(), "Employee_Table");
}

vector<YardInvType> YardDatabase::InventoryGetAll(){
    
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
        
    return XMLFromStream<YardInvType>(dbStream.get(), "Inventory_Table");
}

YardInvType YardDatabase::InventoryGet(long key)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Table where INV_Item_ID = "
        << key << ";";
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStreamSingle<YardInvType>(dbStream.get(), "Inventory_Table");
}

long YardDatabase::CarrierAdd(const YardCarrierType& carrier)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO Carrier_Table values(" << item.ToString() << ");";
    
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions    
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    // This function also does a select to return the key
    
    stringstream select;
    select << "SELECT CRR_ID from Carrier_Table where CRR_Name = '"
        << carrier.GetName() << "';";
    
    auto_ptr<otl_stream> db;
    
    try { // since its a new call might throw bad_alloc, but that is unlikely
        db.reset( new otl_stream(1, select.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    long int key = 0;
    
    try {
        *db >> key;
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    return key;
    
}

long YardDatabase::InventoryAdd(const YardInvType& item)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO Inventory_Table values(" << item.ToString() << ");";
    
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    // This function also does a select to return the key
    
    stringstream select;
    select << "SELECT INV_Item_ID from Inventory_Table where INV_Bar_Code_Number = '"
        << item.GetBarCode() << "';";
    
    auto_ptr<otl_stream> db;
    
    try { // since its a new call might throw bad_alloc, but that is unlikely
        db.reset( new otl_stream(1, select.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    long int key = 0;
    
    try {
        *db >> key;
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    return key;
}

int YardDatabase::CustomerAdd(const YardCustType& newCust)
{
	if (!m_db)
		throw YardDBException("DB not Initialized.");

	stringstream sql;
	sql << "INSERT INTO Customer_Table values(" << newCust.ToString() << ");";
    wxLogDebug(sql.str().c_str());
	auto_ptr<otl_stream> dbStream;

	try {
		dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
	} catch (otl_exception &e) {

		throw YardDBException((char *)e.msg, (char *)e.stm_text);
	}
    return 0;
}

long TaxTypeAdd(const YardTaxType& taxtype);

string YardDatabase::tab(int level)
{
    string ret;
    for (int i = 0; i < level; i++)
        ret += "    ";
    return ret;
}

string YardDatabase::escape(const string& esc){
    string ret;
    // This is to try and cut down on internal buffer resizing
    ret.reserve(esc.length());
    for (unsigned int i = 0; i < esc.length(); i++)
    {
        switch (esc[i]) {
            case ('<'): ret += "&lt;"; break;
            case ('>'): ret += "&gt;"; break;
            case ('&'): ret += "&amp;"; break;
            case ('\''): ret += "&apos;"; break;
            case ('"'): ret += "&quot;"; break;
            default: ret += esc[i]; break;
        }

    }
    return ret;
}

string YardDatabase::ToXML(otl_stream * stream, const string& record) const
{
    
    if (!stream)
        return "";
    stringstream xml;    
    int length = 0;
    otl_column_desc* desc = stream->describe_select(length);

    xml << tab(0) << "<" << record << ">" << endl;
    /// @todo This is most likely faster with a string that I don't recreate in the loop
    for(int i = 0; i < length; i++)
    {
        xml << tab(1) << "<" << desc[i].name << ">";
        
        switch(desc[i].otl_var_dbtype) {
            case(otl_var_varchar_long): {
                string i;
                *stream >> i;
                xml << escape(i);}
                break;
            case(otl_var_int):{
                int i;
                *stream >> i;
                xml << i;}
                break;
             case(otl_var_char):{
                string i;
                *stream >> i;
                xml << escape(i);}
                break;
            case(otl_var_db2date): 
            case(otl_var_db2time): 
            case(otl_var_ltz_timestamp): 
            case(otl_var_timestamp): 
            case(otl_var_tz_timestamp): {
                otl_datetime i;
                *stream >> i;
                xml << i;
                }
                break;
            case(otl_var_float):{
                float i;
                *stream >> i;
                xml << i;}
                break;
            case(otl_var_double): {
                double i;
                *stream >> i;
                xml << i;}
                break;
            case(otl_var_long_int): {
                long int i;
                *stream >> i;
                xml << i;}
                break;
            case(otl_var_short):{
                short i;
                *stream >> i;
                xml << i;}
                break;
            case(otl_var_unsigned_int): {
                unsigned int i;
                *stream >> i;
                xml << i;}
                break;
            #ifdef OTL_BIGINT
            case(otl_var_bigint): {
                long long i;
                *stream >> i;
                xml << i; }
                break;
            #endif
            
            case(otl_var_clob): {
                string i;
                *stream >> i;
                xml << escape(i); }
                break;
            #if 0
            case(otl_var_blob): {
                otl_lob_stream i;
                *stream >> i;
                xml << i;}
                break;
            #endif
            default: cerr << "Throw a fucking exception" << endl;
                break;
        }
        xml << "</" << desc[i].name << ">" << endl;

    }
    
    xml << tab(0) << "</" << record << ">" << endl;
    return xml.str();
}
    

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_DB))

#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

#define TEST_DB "localhost"
#define TEST_DSN "YardSaleTest"
#define TEST_USER "test"
#define TEST_PASS "test"

/*
Tests needed:
    Add, remove, modify each type.

*/

int InventoryTest(YardDatabase * db)
{
    // Setup inventory
    YardInvType test1;
    
    test1.SetSKU("BFG-5000");
    test1.SetBarCode("QWERTY");
    test1.SetDescription("A very nice object");
    test1.SetDepartment("Sales");
    test1.SetQuantOnHand(69);
    test1.SetQuantOnOrder(96);
    test1.SetReorderLevel(30);
    test1.SetReorderQuant(1000);
    test1.SetType("Widget");
    test1.SetWeightLbs(1000.45);
    test1.SetTaxType(0);
    test1.SetVendorId(0);
    test1.SetGroupId(0);
    test1.SetRetailPrice(34.23);
    test1.SetWholesalePrice(1000.12);
    test1.AddBulkPrice(100, 0.12);
    test1.AddBulkPrice(200, 0.23);
    test1.RemoveBulkPrice(100);
    test1.SetOverSized(true);
    test1.SetShipFreight(false);
    
    // try insert
    long key = 0;
    VERIFY_NO_THROW( key = db->InventoryAdd(test1) );
    if (key == 0) return 1;
        
    // try retrieve
    YardInvType test2;
    VERIFY_NO_THROW( test2 = db->InventoryGet(key) );
    
    return  0;
    
#if 0    
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
#endif
}

/// argv[1]: username, argv[2]: pass, argv[3]: dsn
int main(int argc, char** argv)
{
    YardDatabase testDB;
   
    if (argc == 4) {
        testDB.Init(argv[1], argv[2], argv[3]);
    }
    else
    {
        testDB.Init(TEST_USER, TEST_PASS, TEST_DSN);
    }
        
    try {
        testDB.connect();
    } 
    catch (YardDBException &e) 
    {
        if (argc == 4) // command line usage
        {
            cout << "Error: " << e.GetWhat() << endl
                 << "Command line usage: test_db username pass dsn" << endl;
            return 1;
        }
        cout << "!!!Could not connect to the database, \n"
            << "the database connection based \n"
            << "tests will not be run (" << e.GetWhat() << "). \n"
            << "I you have not setup the testing main for your \n"
            << "testing database, please do so!!!" << endl;
        return 1;
    }

    InventoryTest(&testDB);
    
    return failure;
}

    
#endif
