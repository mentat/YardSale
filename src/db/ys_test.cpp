#include <iostream>
#include <sstream>
using namespace std;

#define OTL_ODBC_UNIX
#include <otlv4.h>

int main(){
    int unf;
    otl_long_string test;
    otl_connect db; // connect object
    otl_connect::otl_initialize(); // init ODBC
    db.rlogon("UID=pwizard;PWD=temp;DSN=YardSale"); // connect to ODBC
    otl_stream dbStream(50, "SELECT INV_SKU_Number, INV_Item_Description "
                        "FROM Inventory_Table WHERE INV_SKU_Number = '10000'",
			db);
    while (!dbStream.eof()){
	dbStream >> unf >> test;
	cout << test.v << " " << unf << endl;
    }
    db.logoff();
    return 0;
}
