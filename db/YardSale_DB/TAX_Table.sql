DROP TABLE IF EXISTS Tax_Table;

CREATE TABLE Tax_Table(
	TAX_ID		INT AUTO_INCREMENT NOT NULL,
	TAX_Name	varchar(20),
	TAX_Percent	FLOAT,
	Primary Key (TAX_ID)
)type=InnoDB
