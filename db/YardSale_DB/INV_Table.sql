DROP TABLE IF EXISTS Inventory_Table;

CREATE TABLE Inventory_Table(
	INV_SKU_Number			INT	NOT NULL,
	INV_Bar_Code_Number		varchar(30),
	INV_Item_Description		TEXT,
	INV_Item_Department		varchar(30),
	INV_Quantity_On_Hand		INT,
	INV_Quantity_On_Order		INT,
	INV_Reorder_Level		INT,
	INV_Reorder_Quantity		INT,
	INV_Item_Type			varchar(20),
	INV_REF_TAX_Tax_Type            INT NOT NULL,
	INV_REF_VND_Vendor_ID           INT NOT NULL,	
	INV_Retail_Price		DECIMAL(7,2),
	INV_Wholesale_Price		DECIMAL(7,2),
	INV_Bulk_Price			TEXT,
	INV_Date_Last_Received		DATETIME,
	INV_Weight_Pounds		FLOAT,
	INV_Oversized_Flag		enum('T','F'),
	INV_Ship_By_Freight		enum('T','F'),
	INV_Comment			TEXT,
	Primary Key (INV_SKU_Number),
	UNIQUE INDEX (INV_Bar_Code_Number),
	INDEX tax_id (INV_REF_TAX_Tax_Type),
	INDEX vnd_id (INV_REF_VND_Vendor_ID),
	FOREIGN KEY (INV_REF_TAX_Tax_Type)
	  REFERENCES Tax_Table(TAX_ID),
	FOREIGN KEY (INV_REF_VND_Vendor_ID) 
	  REFERENCES Vendor_Table(VND_ID)
) type=InnoDB
