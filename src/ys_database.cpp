#include "wx/string.h"
#include "ys_database.h"

YardDatabase::YardDatabase(const wxString& dsn, const wxString& name, const wxString& pass) {

}
  
YardDatabase::YardDatabase() {
  
}

YardDatabase::~YardDatabase() 
{
  
}

bool YardDatabase::Init(const wxString& dsn, const wxString& name, const wxString& pass)
{
    
    return true;
}
   

int YardDatabase::GetStatus() const {
    
   
    return -1;
}


bool YardDatabase::connect(){

    return true;
}


vector<YardInvType> YardDatabase::InvSearchKeyword(const unsigned long &sku) {
   
    vector<YardInvType> m_invVec; 
    return m_invVec;
}

vector<YardInvType> YardDatabase::InvGet(unsigned int num, unsigned int offset){
    

    vector<YardInvType> m_invVec; 
   
    return m_invVec;
}
