#include <string>
#include <sstream>
#include <memory>

#include "ys_log.h"
#include "ys_exception.h"
#include "ys_database.h"

#include "ys_group.h"
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

vector<YardInvType> YardDatabase::InventorySearchSKU(const string& sku) {
   
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


map<string,string> YardDatabase::ACLGetAll() const
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM ACL_Table";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(5, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    map<string, string> acls;
    
    try {
        string name, desc;
        while(!dbStream->eof())
        {    
            *dbStream >> name >> desc;
            acls[name] = desc;
        }
    }catch (otl_exception& e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return acls;
    
}
void YardDatabase::ACLAdd(const string& name, const string& desc)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO ACL_Table values('" << name << "','" 
        << desc << "');";
    
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
}

string YardDatabase::ACLGet(const string& name)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT ACL_Description FROM ACL_Table where ACL_Type = '"
        << name << "';";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(5, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    string desc;
    try {
        *dbStream >> desc;
        
    }catch (otl_exception& e) {
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    return desc;
}

vector<YardInvType> YardDatabase::InventoryGetAll() const{
    
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

vector<YardInvType> YardDatabase::InventoryGetInGroup(long groupid) const
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Table where INV_REF_INVGRP_Group_ID = "
        << groupid << ";";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStream<YardInvType>(dbStream.get(), "Inventory_Table");
}

YardEmployeeType YardDatabase::EmployeeGet(long key) const
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Employee_Table where EMP_ID_Number = "
        << key << ";";
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStreamSingle<YardEmployeeType>(dbStream.get(), "Employee_Table");   
}

YardVendType YardDatabase::VendorGet(long key) const
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Vendor_Table where VND_ID = "
        << key << ";";
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStreamSingle<YardVendType>(dbStream.get(), "Vendor_Table");   
}

string YardDatabase::ReportXML(const string& sql, long& count) const
{    
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    wxLogDebug(sql.c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(40, sql.c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    string result(ToXML(dbStream.get(), "record")); 
    count = dbStream->get_rpc();
    
    return result;    
}

YardInvType YardDatabase::InventoryGet(long key) const
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
    sql << "INSERT INTO Carrier_Table values(" << carrier.ToString() << ");";
    
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

long YardDatabase::EmployeeAdd(const YardEmployeeType& emp)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO Employee_Table values(" << emp.ToString() << ");";
    
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    // This function also does a select to return the key
    
    stringstream select;
    select << "SELECT EMP_ID_Number from Employee_Table where EMP_Social_Security_Number = "
        << emp.GetTaxId() << ";";
    
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

long YardDatabase::VendorAdd(const YardVendType& vendor)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO Vendor_Table values(" << vendor.ToString() << ");";
    
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    // This function also does a select to return the key
    
    stringstream select;
    select << "SELECT VND_ID from Vendor_Table where VND_Name = '"
        << vendor.GetName() << "';";
    
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

vector<YardGroup> YardDatabase::GroupGetAll() const
{        
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Group_Table";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    } catch (otl_exception &e) { // so just get otl exceptions
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    return XMLFromStream<YardGroup>(dbStream.get(), "Inventory_Group_Table");   
}

YardGroup YardDatabase::GroupGet(long key) const
{
   if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Inventory_Group_Table where INVGRP_Group_ID = "
        << key << ";";
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStreamSingle<YardGroup>(dbStream.get(), "Inventory_Group_Table");
}

long YardDatabase::GroupAdd(const YardGroup& group)
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "INSERT INTO Inventory_Group_Table values(" << group.ToString() << ");";
    
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    
    // This function also does a select to return the key
    
    stringstream select;
    select << "SELECT INVGRP_Group_ID from Inventory_Group_Table where INVGRP_Group_Name = '"
        << group.GetName() << "';";
    
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

long YardDatabase::CustomerAdd(const YardCustType& newCust)
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

vector<YardCustType> YardDatabase::CustomerGetAll()
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Customer_Table";
    
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc
        dbStream.reset( new otl_stream(50, sql.str().c_str(), *m_db) );
    } catch (otl_exception &e) { // so just get otl exceptions
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
    return XMLFromStream<YardCustType>(dbStream.get(), "Customer_Table");   
    
}

YardCustType YardDatabase::CustomerGet(long key)
{
   if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Customer_Table where CUST_Account_Number = "
        << key << ";";
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStreamSingle<YardCustType>(dbStream.get(), "Customer_Table");  
}

long YardDatabase::TaxTypeAdd(const YardTaxType& taxtype)
{
    if (!m_db)
		throw YardDBException("DB not Initialized.");

	stringstream sql;
	sql << "INSERT INTO Tax_Table values(" << taxtype.ToString() << ");";
    wxLogDebug(sql.str().c_str());
	auto_ptr<otl_stream> dbStream;

	try {
		dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
	} catch (otl_exception &e) {

		throw YardDBException((char *)e.msg, (char *)e.stm_text);
	}
    
    // This function also does a select to return the key
    
    stringstream select;
    select << "SELECT TAX_ID from Tax_Table where TAX_Name = '"
        << taxtype.GetName() << "';";
    
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

YardTaxType YardDatabase::TaxTypeGet(long key) const
{
    if (!m_db)
        throw YardDBException("DB not initialized.");
    
    stringstream sql;
    sql << "SELECT * FROM Tax_Table where TAX_ID = "
        << key << ";";
    wxLogDebug(sql.str().c_str());
    auto_ptr<otl_stream> dbStream;

    try { // since its a new call might throw bad_alloc, but that is unlikely
        dbStream.reset( new otl_stream(1, sql.str().c_str(), *m_db) );
    
    } catch (otl_exception &e) { // so just get otl exceptions
        
        throw YardDBException((char *)e.msg, (char*)e.stm_text);
    }
        
    return XMLFromStreamSingle<YardTaxType>(dbStream.get(), "Tax_Table");
  
}

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

int TaxTest(YardDatabase * db)
{
    YardTaxType test1;
    test1.SetName("Leetness Tax");
    test1.SetPercent(0.11);
    
    long key = 0;
    VERIFY_NO_THROW(key = db->TaxTypeAdd(test1));
    
    YardTaxType test2;
    VERIFY_NO_THROW(test2 = db->TaxTypeGet(key));
    
    VERIFY(test1.GetName(), test2.GetName());
    
    return 0;
}

int VendorTest(YardDatabase * db)
{
    YardVendType test1;
    
    test1.SetName("ACME");
    test1.SetAddress("29 Lynwood");
    test1.SetCity("A-Town");
    test1.SetState("NC"); 
    test1.SetZip("27777");
    test1.SetPhone("919-999-8888");
    test1.SetSalesRep("Bob");
    test1.SetSpecialty("Pics");
    test1.SetEmail("acme@hotmail.com");
    test1.SetHomePage("http://yardsale.sf.net");
    
    long key = 0;
    VERIFY_NO_THROW(key = db->VendorAdd(test1));
    
    YardVendType test2;
    VERIFY_NO_THROW(test2 = db->VendorGet(key));
    
    VERIFY(test1.GetName(), test2.GetName());
    
    return 0;
}

int GroupTest(YardDatabase * db)
{
    YardGroup test1;
    test1.SetName("Spockets");
    
    long key = 0;
    VERIFY_NO_THROW(key = db->GroupAdd(test1));
    
    YardGroup test2;
    VERIFY_NO_THROW(test2 = db->GroupGet(key));
    
    VERIFY(test1.GetName(), test2.GetName());
    
    return 0;
}

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
    test1.SetTaxType(1);
    test1.SetVendorId(1);
    test1.SetGroupId(1);
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
    //if (key == 0) return 1;
        
    // try retrieve
    YardInvType test2;
    VERIFY_NO_THROW( test2 = db->InventoryGet(key) );
       
    vector<YardInvType> invObj;

    /* Search for an SKU that probably doesn't exist,
   test to see if the shit bombs when we try to print */
    
    VERIFY_NO_THROW(invObj = db->InventorySearchSKU("BFG-5000"));
    VERIFY(invObj.size(), 1);
    
    return 0;    

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

    TaxTest(&testDB);
    VendorTest(&testDB);
    GroupTest(&testDB);
    InventoryTest(&testDB);
    
    return failure;
}

    
#endif
