DROP TABLE IF EXISTS Carrier_Table;

CREATE TABLE Carrier_Table(
	CRR_ID				INT AUTO_INCREMENT NOT NULL,
	CRR_Name			varchar(50),
	CRR_Pickup_Location		TEXT,
	CRR_Phone_Number		varchar(20),
	Primary Key (CRR_ID)
)type=InnoDB
