# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-02-21 20:39:37
# 
# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-02-19 15:12:56
# 
# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-02-19 14:36:10
# 
# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-02-16 01:22:15
# 
SELECT * FROM Customer_Table;

INSERT INTO Customer_Table 
values(2001,'William','Adam','Parrish',
'4701 Blue Bird Court Apt A','919.233.7921',
'Raleigh','27606','0123-4567-8910-1112', '04/04',
'William Adam Parrish','','' );

INSERT INTO Customer_Table 
values(2003,'Jesse','L','Lovelace',
'Somewhere near cameron village','919.233.9840',
'Raleigh','27604','0123-4567-8910-1114', '04/04',
'Jesse  L Lovelace','','' );

INSERT INTO Customer_Table 
values(2005,'Mike','R','Swigon',
'Behind Domino\'s Pizza','919.233.2877',
'Raleigh','27604','0123-4567-8910-1454', '04/04',
'Mike R Swigon','','' );

INSERT INTO Customer_Table 
values(2004,'Jay','','Johnston',
'With Jesse!!!','919.233.2877',
'Raleigh','27604','0123-4267-8910-1454', '04/04',
'Jay Johnston','','' );

INSERT INTO Customer_Table 
values(2006,'John','','Lamb',
'Above Jesse and Jay','919.233.2877',
'Raleigh','27604','1123-4567-8910-1454', '04/04',
'John Lamb','','' );

#END CUSTOMER TABLE STUFF

#BEGIN TAX STUFF
INSERT INTO Tax_Table
values(1,'Food Tax', 0.02);

INSERT INTO Tax_Table
values(2,'Sales Tax',0.06);

#Show all the different tax types
SELECT * FROM Tax_Table;

#Show all inventory items associated with their Tax Types
#This is probably the most useful query
SELECT * FROM Inventory_Table JOIN Tax_Table
ON Inventory_Table.INV_REF_TAX_TAX_Type=Tax_Table.TAX_ID;

#END TAX RELATED STUFF

#BEGIN VENDOR  STUFF

INSERT INTO Vendor_Table
VALUES('','Canned Food Distributing Warehouse',
'Warehouse St.','Raleigh','NC','27667','919.233.7865',
'Joe Blow','Canned Food','joe_blow@cfdw.com','www.cfdw.com');

INSERT INTO Vendor_Table
VALUES('','Plastic Storage Container Biz',
'Waterfront Port BLVD','Wimington','NC','27666','919.765.3456',
'Jackie Nackie','Plastic Storage Containers','j_nackie@psc.biz','');

INSERT INTO Vendor_Table
VALUES('','Fayetteville St. Butcher Market',
'203 Fayetteville St','Raleigh','NC','27603','919.233.4455',
'Butch','Meat','','');

SELECT * FROM Vendor_Table;

#BEGIN INVENTORY STUFF

INSERT INTO Inventory_Table
values('10000','1011011010101','Canned Smushed Tomatoes',
'Food',50,200,35,200,'Can food',1,1,0.80,0.20,
'<bulk><amount>10</amount><discount>10</discount></bulk>',
now(),0.004,'F','F','');

INSERT INTO Inventory_Table
values('','10100','10101101011010101','Hamburger Meat',
'Food',117,100,50,100,'Meat',1,3,1.99,0.99,
'<bulk><amount>5</amount><discount>10</discount></bulk>',
now(),1.000,'F','F','');

INSERT INTO Inventory_Table
values('10110','1001101011010101','50 Gallon Trash Can',
'Houseware',13,0,2,20,'Home',2,2,8.99,3.50,
'',now(),1.000,'F','F','');

# Show all things in the inventory table, without their actual tax
# information
SELECT *  FROM Inventory_Table;

#END INVENTORY STUFF

#
# This query returns a set of all tax and vendor data 
# associated with any particular Inventory Item.
#
# This is also a more useful query than the  plain
# ole select query
#
SELECT * FROM 
Inventory_Table JOIN Tax_Table 
ON 
Inventory_Table.INV_REF_TAX_TAX_Type=Tax_Table.TAX_ID, Vendor_Table
WHERE 
Inventory_Table.INV_REF_VND_Vendor_ID=Vendor_Table.VND_ID;


#BEGIN ACL TABLE STUFF

INSERT INTO ACL_Table VALUES('Administrator', 'Tha Master User');
INSERT INTO ACL_Table VALUES('Manager','Eh, he is pretty powerful');
INSERT INTO ACL_Table VALUES('Clerk','Peon');
INSERT INTO ACL_Table VALUES('Warehouse','Powerful Peon');

#END ACL TABLE STUFF

#BEGIN EMPLOYEE TABLE STUFF

INSERT INTO Employee_Table VALUES('222334545',1234,'Bilbo','','Baggins',
	'<ADDRESS><1>Somewhere in the Shire</1><2>Green Round Door</2></ADDRESS>',
	'No Phone','The Shire','23456','','','Manager');

INSERT INTO Employee_Table VALUES('245334545',1235,'Frodo','','Baggins',
        '<ADDRESS><1>Somewhere in the Shire</1><2>Green Round Door</2></ADDRESS>',
	'No Phone','The Shire','23456','','','Clerk');

INSERT INTO Employee_Table VALUES('221334545',1236,'Smeagle','','',
        '<ADDRESS><1>Lake Placid</1><2></2></ADDRESS>',
	'No Phone','The Shire','23456','','','Warehouse');

INSERT INTO Employee_Table VALUES('999999999',0,'G','O','D',
        '<ADDRESS><1></1><2></2></ADDRESS>',
	'','','','','','Administrator');
		
SELECT * FROM Employee_Table JOIN ACL_Table ON Employee_Table.EMP_REF_ACL_Type = ACL_Table.ACL_Type;

#END EMPLOYEE STUFF

#BEGIN TRANSACTION STUFF

INSERT INTO Transaction_Log_Table VALUES(1234,'10000',2001, 0.20, 10000, 5, '' );
INSERT INTO Transaction_Log_Table VALUES(1234,'10100',2001, 0.99, 10000, 10, '' );
INSERT INTO Transaction_Log_Table VALUES(1234,'10110',2001, 3.50, 10000, 1, '' );


#THIS QUERY RETURNS A LOT OF INFORMATION
# IT WILL SHOW THE EMPLOYEE WHO SOLD THE ITEMS
# THIS QUERY ANSWERS THE QUESTION: Show the employee, customer, and items that belong to transaction id 10000
SELECT * 
FROM 	Transaction_Log_Table JOIN Employee_Table 
ON	Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number,
	Inventory_Table, Customer_Table
WHERE 
	Transaction_Log_Table.TRANS_REF_INV_SKU_Number = Inventory_Table.INV_SKU_Number AND
	Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.CUST_Account_Number AND
	Transaction_Log_Table.TRANS_ID = 10000;


#END TRANSACTION STUFF
