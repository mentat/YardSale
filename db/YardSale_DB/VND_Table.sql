DROP TABLE IF EXISTS Vendor_Table;

CREATE TABLE Vendor_Table(
	VND_ID				INT AUTO_INCREMENT NOT NULL,
	VND_Name			varchar(255),
	VND_Address			TEXT,
	VND_City			varchar(50),
	VND_State			varchar(50),
	VND_Zip_Code			varchar(12),
	VND_Phone_Number		varchar(20),
	VND_Sales_Representative	TEXT,
	VND_Specialty			TEXT,
	VND_Email_Address		varchar(255),
	VND_Home_Page			TEXT,
	Primary Key (VND_ID)
)type=InnoDB
