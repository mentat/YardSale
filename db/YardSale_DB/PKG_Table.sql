DROP TABLE IF EXISTS Package_Table;

CREATE TABLE Package_Table(
	PKG_ID_Number				INT AUTO_INCREMENT NOT NULL,
	PKG_REF_TRANS_ID			INT REFERENCES Transaction_Log_Table.TRANS_ID,
	PKG_REF_CUST_Account_Number		INT REFERENCES Customer_Table.CUST_Account_Number,
	PKG_REF_CRR_ID_Number			INT REFERENCES Carrier_Table.CRR_ID_Number,
	PKG_Tracking_Number			varchar(50),
	PKG_REF_SHP_Shipping_Type		INT REFERENCES Shipping_Type_Table.SHP_Type,
	Primary Key(PKG_ID_Number)
) type=InnoDB
