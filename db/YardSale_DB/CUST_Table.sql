DROP TABLE IF EXISTS Customer_Table;

CREATE TABLE Customer_Table(
	CUST_Account_Number		INT AUTO_INCREMENT NOT NULL,
	CUST_First_Name			varchar(25),
	CUST_Middle_Name		varchar(25),
	CUST_Last_Name			varchar(50),
	CUST_Address			TEXT,
	CUST_Phone			varchar(20),
	CUST_City			varchar(50),
	CUST_Zip			varchar(12),
	CUST_Credit_Card_Number		varchar(20),
	CUST_CC_Exp_Date		varchar(6),
	CUST_Name_On_CC			TEXT,
	CUST_Signature			TEXT,
	CUST_Photo			TEXT,
	Primary Key(CUST_Account_Number)
)type=InnoDB
