/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifndef YS_PACKAGE_TYPE_H
#define YS_PACKAGE_TYPE_H

#include "xmlnode.h"
#include <vector>
#include <string>

using namespace std;

class YardDatabase;
class otl_stream;

/**
 * The YardSale Package Type is a OO representation of the datebase
 * package table.
 *
 * @include PKG_Table.sql
 * @ingroup database 
 * @see YardPackageType
 * @author Michael Swigon	
 * @version \$Revision: 1.2 $$
 * @see XMLNode
 */

class YardPackageType: public XMLNode
{
 public:
   
    friend class YardDatabase;

	  
    YardPackageType() {}
    
    /**
     * Copy constructor
     */
    YardPackageType(const YardPackageType& obj);
    
    YardPackageType& operator=(const YardPackageType& obj);

	/* gettors */

	/// Get package id
    int GetPackID() const { return m_packageID; }
    /// Get transaction id, external reference
    int GetTransID() const { return m_transID; }
    /// Get customer account number, external reference
	int GetCustAcctNum() const { return m_custAcctNum; }
	/// Get carrier id number, external reference
	int GetCarrierID() const { return m_carrierID; }
	/// Get package tracking number
	string GetTrackNum() const { return m_trackNum; }
	/// Get shipping type, external reference
	string GetShippingType() const{ return m_shippingType; }

	/* settors */

	/// Set the transaction id 
	void SetTransID(const int num) { m_transID = num; }
	/// Set the customer account number
	void SetCustAcctNum(const int num) { m_custAcctNum = num; }
	/// Set the carrier id number
	void SetCarrierID(const int num) { m_carrierID = num; }
	/// Set the package tracking number
	void SetTrackNum(const string& str) { m_trackNum = str; }
	/// Set the shipping type
	void SetShippingType(const string& str) { m_shippingType = str; }


	/**
     * Returns string representation of the datatype.
     * @param delim The string to delimit items in database
     * @return A string representation of the object
     */
    virtual string ToString(const string& delim = ",") const;
    
    virtual void FillFromStream(otl_stream * stream);
   
 private:
    
    /* These variables directly correspond with the database */
    int m_packageID;
    int m_transID;
	int m_custAcctNum;
	int m_carrierID;
	string m_trackNum;
	string m_shippingType;

};


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

#endif
