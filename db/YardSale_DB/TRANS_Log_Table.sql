DROP TABLE IF EXISTS Transaction_Log_Table;

CREATE TABLE Transaction_Log_Table(
	TRANS_REF_EMP_ID_Number			INT,
	TRANS_REF_INV_Item_ID			INT,
	TRANS_REF_CUST_Account_Number		INT,
	TRANS_Sale_Price			DECIMAL(10,2),
	TRANS_ID				INT NOT NULL,
	TRANS_Quantity				INT,
	TRANS_Comment				TEXT,
	TRANS_Time				DATETIME,
	Primary Key(TRANS_REF_EMP_ID_Number, TRANS_REF_INV_Item_ID, TRANS_REF_CUST_Account_Number, TRANS_Sale_Price, TRANS_ID, TRANS_Quantity),
	INDEX trans_id (TRANS_ID),
	INDEX emp_id (TRANS_REF_EMP_ID_Number),
	INDEX sku_num (TRANS_REF_INV_Item_ID),
	INDEX cust_acct (TRANS_REF_CUST_Account_Number),
	FOREIGN KEY (TRANS_REF_EMP_ID_Number) REFERENCES Employee_Table(EMP_ID_Number),
	FOREIGN KEY (TRANS_REF_INV_Item_ID) REFERENCES Inventory_Table(INV_Item_ID),
	FOREIGN KEY (TRANS_REF_CUST_Account_Number) REFERENCES Customer_Table(CUST_Account_Number)
)type=InnoDB
