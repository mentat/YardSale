#include "ys_database.h"
#include <wx/db.h>
#include <wx/dbtable.h>

YardDatabase::YardDatabase(const wxString& dsn, const wxString& name, const wxString& pass) {
    m_db = new wxDb;
    m_table = new wxDbTable;
    m_connectInfo = new wxDbConnectInf(NULL, dsn, name, pass);
    m_inv = new YardInvType;
    
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
    SetColDefs(0, "INV_SKU_Number", DB_DATA_TYPE_INTEGER, m_inv->m_skuNumber, 
	       SQL_C_ULONG, sizeof(m_inv->m_skuNumber), TRUE, TRUE);
    SetColDefs(1, "INV_Bar_Code_Number", DB_DATA_TYPE_VARCHAR, m_inv->m_barCode,
	       SQL_C_CHAR, sizeof(m_inv->m_barCode), TRUE, TRUE);
    SetColDefs(2, "INV_Item_Type", DB_DATA_TYPE_VARCHAR, m_inv->m_itemType,
	       SQL_C_CHAR, sizeof(m_inv->m_itemType), TRUE, TRUE);
    /* ... *JOHN*
       skipping stuff here for a bit.
    */
    SetColDefs(3, "INV_Retail_Price", DB_DATA_TYPE_FLOAT, m_inv->m_retailPrice,
	       SQL_C_FLOAT, sizeof(m_inv->m_retailPrice), TRUE, TRUE);
    SetColDefs(4, "INV_Item_Description", DB_DATA_TYPE_VARCHAR, m_inv->m_itemDescription,
	       SQL_C_CHAR, sizeof(m_inv->m_itemDescription), TRUE, TRUE);
    SetColDefs(5, "INV_Wholesale_Price", DB_DATA_TYPE_FLOAT, m_inv->m_wholesalePrice,
	       SQL_C_FLOAT, sizeof(m_inv->m_wholesalePrice), TRUE, TRUE);

}
  
YardDatabase::YardDatabase() {
}

bool YardDatabase::connect(){
    if(!m_connectInfo || !m_connectInfo->GetHenv()){
	cerr << "You messed up, G." << endl;
	return false;
    }
    m_db = wxDbGetConnection(m_connectInfo);
}