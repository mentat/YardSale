using namespace::std;

#include "ys_database.h"
#include <iostream>

int main() {
    wxString dsn = "YardSaleRemote";
    wxString user = "pwizard";
    wxString password = "temp";
    YardDatabase db = YardDatabase(dsn, user, password);
    vector<YardInvType> invVec;
    if(db.connect()){
	invVec = db.InvSearchKeyword(10000);
	cout << invVec[0].GetRetailPrice() << endl;
    }
    return 0;
}
