#include <wx/string.h>
#include <wx/db.h>
#include <wx/dbtable.h>

#include "ys_database.h"

YardDatabase::YardDatabase(const wxString& dsn, const wxString& name, const wxString& pass) {

    m_db = 0;
    m_table = 0;
    m_connectInfo = 0;
    Init(dsn, name, pass);
}
  
YardDatabase::YardDatabase() {
    m_db = 0;
    m_table = 0;
    m_connectInfo = 0;
}

YardDatabase::~YardDatabase() 
{
    delete m_connectInfo;
    delete m_db;
    delete m_table;
}

bool YardDatabase::Init(const wxString& dsn, const wxString& name, const wxString& pass)
{
    
    if (m_connectInfo)
        delete m_connectInfo;
    
    m_connectInfo = new wxDbConnectInf(NULL, dsn, name, pass);

    return true;
}
   

int YardDatabase::GetStatus() const {
    
    if (m_db)
        return m_db->DB_STATUS;
    return -1;
}


bool YardDatabase::connect(){
    
    if(!m_connectInfo || !m_connectInfo->GetHenv()){
//	cerr << "You messed up, G." << endl;
        return false;
    }
    m_db = wxDbGetConnection(m_connectInfo);

    m_table = new wxDbTable(m_db, "Inventory_Table", 6, "", !wxDB_QUERY_ONLY, "");

    
    /* DB_DATA_TYPEs include:
         DB_DATA_TYPE_INTEGER
	 DB_DATA_TYPE_VARCHAR
	 DB_DATA_TYPE_FLOAT
	 DB_DATA_TYPE_DATE
       SQL_C_TYPEs include:
         SQL_C_CHAR	    SQL_C_LONG
	 SQL_C_ULONG        SQL_C_SHORT
	 SQL_C_USHORT       SQL_C_FLOAT
	 SQL_C_DOUBLE       SQL_C_NUMERIC
	 SQL_C_TIMESTAMP    SQL_C_BOOLEAN
	 SQL_C_ENUM
    */  
    m_table->SetColDefs(0, "INV_SKU_Number", DB_DATA_TYPE_INTEGER, &(m_inv.m_skuNumber), 
	       SQL_C_ULONG, sizeof(m_inv.m_skuNumber), TRUE, TRUE);
    m_table->SetColDefs(1, "INV_Bar_Code_Number", DB_DATA_TYPE_VARCHAR, &(m_inv.m_barCode),
	       SQL_C_CHAR, sizeof(m_inv.m_barCode), TRUE, TRUE);
    m_table->SetColDefs(2, "INV_Item_Type", DB_DATA_TYPE_VARCHAR, &(m_inv.m_itemType),
	       SQL_C_CHAR, sizeof(m_inv.m_itemType), TRUE, TRUE);
    /* ... *JOHN*/
    /**
       @todo We need to set up columns for every actual column
       in the table if we plan on using them columns.
    */
    /*   skipping stuff here for a bit.
    */
    m_table->SetColDefs(3, "INV_Retail_Price", DB_DATA_TYPE_FLOAT, &(m_inv.m_retailPrice),
	       SQL_C_FLOAT, sizeof(m_inv.m_retailPrice), TRUE, TRUE);
    m_table->SetColDefs(4, "INV_Item_Description", DB_DATA_TYPE_VARCHAR, &(m_inv.m_itemDescription),
	       SQL_C_CHAR, sizeof(m_inv.m_itemDescription), TRUE, TRUE);
    m_table->SetColDefs(5, "INV_Wholesale_Price", DB_DATA_TYPE_FLOAT, &(m_inv.m_wholesalePrice),
	       SQL_C_FLOAT, sizeof(m_inv.m_wholesalePrice), TRUE, TRUE);
    m_table->Open();
    return true;
}


/** JOHN!@#$ */
/* FIXME! */
vector<YardInvType> YardDatabase::InvSearchKeyword(const unsigned long &sku) {
    wxString sqlQuery;
    vector<YardInvType> m_invVec; // john - had to put this in to compile
    sqlQuery.Printf("SELECT * FROM `Inventory_Table` WHERE INV_SKU_NUMBER = '%d'", sku);
    
    if (!m_table->QueryBySqlStmt(sqlQuery)) 
        return m_invVec;
    
    while (m_table->GetNext()) {
        m_invVec.push_back(m_inv);
    }
    return m_invVec;
}

vector<YardInvType> YardDatabase::InvGet(unsigned int num, unsigned int offset){
    
    unsigned long numRows = 0;
    vector<YardInvType> m_invVec; // john - had to put this in to compile
    m_invVec.clear();
    wxString sqlQuery;
    sqlQuery.Printf("SELECT * FROM `Inventory_Table`");
    
    if(!m_table->QueryBySqlStmt(sqlQuery)) 
        return m_invVec;
    /* There is no GetNumRows, only GetRowNum, so I have to
       GetLast();, then GetRowNum().  BRILLIANT!
    */
    m_table->GetLast();
    numRows = m_table->GetRowNum();
    
    if(numRows < num || numRows < num+offset) 
        return m_invVec;
    
    m_table->GetFirst();
    if(offset > 0) {
        for(int ii = 1; ii <= offset; ii++){
            m_table->GetNext();
        }
    }
    
    for(int ii = 1; ii < num; ii++){
        m_invVec.push_back(m_inv);
        m_table->GetNext();
    }
    
    m_invVec.push_back(m_inv);
    return m_invVec;
}
