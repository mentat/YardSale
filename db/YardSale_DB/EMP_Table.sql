DROP TABLE IF EXISTS Employee_Table;

CREATE TABLE Employee_Table(
	EMP_Social_Security_Number		varchar(13) NOT NULL,
	EMP_ID_Number				INT AUTO_INCREMENT,
	EMP_First_Name				varchar(25),
	EMP_Middle_Name				varchar(25),
	EMP_Last_Name				varchar(50),
	EMP_Address				TEXT,
	EMP_Phone_Number			varchar(20),
	EMP_City				varchar(50),
	EMP_Zip					varchar(12),
	EMP_Picture				TEXT,
	EMP_Signature				TEXT,
	EMP_REF_ACL_Type			varchar(30) REFERENCES ACL_Table.ACL_Type,
	EMP_REF_CUST_Account_Number		INT REFERENCES Customer_Table.CUST_Account_Number,
	Primary Key (EMP_Social_Security_Number),
	UNIQUE(EMP_ID_Number)
) type=InnoDB
