DROP TABLE IF EXISTS ACL_Table;

CREATE TABLE ACL_Table(
	ACL_Type		varchar(30),
	ACL_Description		TEXT,
	Primary Key (ACL_Type)
) type=InnoDB
