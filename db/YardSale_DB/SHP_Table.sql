DROP TABLE IF EXISTS Shipping_Table;

CREATE TABLE Shipping_Table(
	SHP_Type		varchar(30),
	SHP_REF_CRR_ID		INT REFERENCES Carrier_Table.CRR_ID,
	SHP_Cost		MONEY,
	Primary_Key(SHP_Type, SHP_REF_CRR_ID, SHP_Cost)
);
