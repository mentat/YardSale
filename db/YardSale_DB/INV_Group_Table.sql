DROP TABLE IF EXISTS Inventory_Group_Table;

CREATE TABLE Inventory_Group_Table(
	INVGRP_Group_ID		INT AUTO_INCREMENT,
	INVGRP_Group_Name	varchar(20),
	Primary Key(INVGRP_Group_ID),
	Unique(INVGRP_Group_Name)
)type=InnoDB
