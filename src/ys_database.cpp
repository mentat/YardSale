#include "ys_database.h"
#include <wx/db.h>
#include <wx/dbtable.h>

YardDatabase::YardDatabase(const wxString& dsn, const wxString& name, const wxString& pass) {
  m_db = new wxDb;
  m_table = new wxDbTable;
  m_connectInfo = new wxDbConnectInf(NULL, dsn, name, pass);
  m_inv = new YardInvType;
  SetColDefs(0, "INV_SKU_NUMBER", DB_DATA_TYPE_INTEGER, m_inv->m_skuNumber, SQL_C_ULONG, sizeof(m_inv->m_skuNumber), TRUE, TRUE);
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
