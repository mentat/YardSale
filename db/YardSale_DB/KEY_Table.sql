DROP TABLE IF EXISTS Key_Table;

CREATE TABLE Key_Table(
	KEY_REF_EMP_ID_Number		INT REFERENCES Employee_Table.EMP_ID_Number,
	KEY_Keys			TEXT,
	Primary Key ( KEY_REF_EMP_ID_Number )
);
