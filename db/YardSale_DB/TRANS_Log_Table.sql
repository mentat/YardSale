DROP TABLE IF EXISTS Transaction_Log_Table;

CREATE TABLE Transaction_Log_Table(
	TRANS_REF_EMP_ID_Number			INT REFERENCES	Employee_Table.EMP_ID_Number,
	TRANS_REF_INV_SKU_Number		INT REFERENCES	Inventory_Table.INV_SKU_Number,
	TRANS_REF_CUST_Account_Number		INT REFERENCES	Customer_Table.CUST_Account_Number,
	TRANS_Sale_Price			DECIMAL(10,2),
	TRANS_ID				INT NOT NULL,
	TRANS_Quantity				INT,
	TRANS_Comment				TEXT,
	Primary Key(TRANS_REF_EMP_ID_Number, TRANS_REF_INV_SKU_Number, TRANS_REF_CUST_Account_Number, TRANS_Sale_Price, TRANS_ID, TRANS_Quantity)
)type=InnoDB
