DROP TABLE IF EXISTS Employee_Table;

CREATE TABLE Employee_Table(
	EMP_ID_Number				INT NOT NULL AUTO_INCREMENT,
	EMP_Social_Security_Number		INT NOT NULL,
	#varchar(13) NOT NULL,
	EMP_First_Name				varchar(25),
	EMP_Middle_Name				varchar(25),
	EMP_Last_Name				varchar(50),
	EMP_Address				TEXT,
	EMP_Phone_Number			varchar(20),
	EMP_City				varchar(50),
	EMP_Zip					varchar(12),
	EMP_Picture				TEXT,
	EMP_Signature				TEXT,
	EMP_REF_ACL_Type			varchar(30),
	EMP_Enabled				INT,
	Primary Key (EMP_ID_Number),
	UNIQUE INDEX(EMP_Social_Security_Number),
	INDEX acl_type (EMP_REF_ACL_Type),
	#INDEX acct_number (EMP_REF_CUST_Account_Number),
	FOREIGN KEY (EMP_REF_ACL_Type) REFERENCES ACL_Table(ACL_Type),
	#FOREIGN KEY (EMP_REF_CUST_Account_Number) REFERENCES Customer_Table(CUST_Account_Number)
) type=InnoDB
