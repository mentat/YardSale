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
