#include <sstream>

#include "ys_package_type.h"

using namespace std;

string YardPackageType::ToString(const string& delim) const {
    
    stringstream output;
    char q = '\'';
    output << GetId() << delim 
        <<  << delim << m_custAcctNum 
        << delim << m_carrierID << delim << m_trackNum 
        << delim << m_shippingType;
    
    return output.str();
        
}

#if (defined(YS_TEST_MAIN) || defined(YS_TEST_PACKAGE_TYPE))
#include <iostream>
#include <vector>
#include "ys_test.h"

using namespace std;

int main()
{
    YardPackageType test1;
    test1.SetTransID(121212);
    test1.SetCustAcctNum(232323);
    test1.SetCarrierID(343434);
    test1.SetTrackNum("fff454545");
    test1.SetShippingType("overnight");

    YardPackageType test2(test1);
    
    VERIFY(test2.GetTransID(), test1.GetTransID());
    
    YardPackageType test3;
    
    test3 = test2;
    
    VERIFY(test3.GetCustAcctNum(), test2.GetCustAcctNum());
    VERIFY(test3.GetTrackNum(), test2.GetTrackNum());


    vector<YardPackageType> anArray;
    
    anArray.push_back(test1);
    anArray.push_back(test2);
    anArray.push_back(test3);
    
    VERIFY(anArray[1].GetTransID(), anArray[2].GetTransID());
    
    vector<YardPackageType> copyArray;
    copyArray = anArray;
    
    VERIFY(anArray[0].GetPackID(), copyArray[0].GetPackID());

    return failure;
}

#endif



/*
DROP TABLE IF EXISTS Package_Table;

CREATE TABLE Package_Table(
	PKG_ID_Number				INT AUTO_INCREMENT NOT NULL,
	PKG_REF_TRANS_ID			INT,
	PKG_REF_CUST_Account_Number		INT,
	PKG_REF_CRR_ID_Number			INT,
	PKG_Tracking_Number			varchar(50),
	PKG_REF_SHP_Shipping_Type		varchar(30),
	Primary Key(PKG_ID_Number),
	INDEX trans_id (PKG_REF_TRANS_ID),
	INDEX cust_acct (PKG_REF_CUST_Account_Number),
	INDEX crr_id (PKG_REF_CRR_ID_number),
	INDEX shp_type (PKG_REF_SHP_Shipping_Type),
	FOREIGN KEY (PKG_REF_TRANS_ID) REFERENCES Transaction_Log_Table( TRANS_ID ),
	FOREIGN KEY (PKG_REF_CUST_Account_Number) REFERENCES Customer_Table( CUST_Account_Number ),
	FOREIGN KEY (PKG_REF_CRR_ID_Number) REFERENCES Carrier_Table( CRR_ID ),
	FOREIGN KEY (PKG_REF_SHP_Shipping_Type) REFERENCES Shipping_Table( SHP_Type )
) type=InnoDB
*/
