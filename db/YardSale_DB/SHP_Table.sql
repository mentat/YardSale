DROP TABLE IF EXISTS Shipping_Table;

CREATE TABLE Shipping_Table(
	SHP_Type		varchar(30),
	SHP_REF_CRR_ID		INT,
	SHP_Cost		DECIMAL(7,2),
	SHP_Enabled		INT,
	Primary Key(SHP_Type, SHP_REF_CRR_ID, SHP_Cost),
	INDEX crr_id (SHP_REF_CRR_ID ),
	INDEX shp_type (SHP_Type),
	FOREIGN KEY (SHP_REF_CRR_ID) REFERENCES Carrier_Table( CRR_ID )
)type=InnoDB
