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
values(2004,'Mike','R','Swigon',
'Behind Domino\'s Pizza','919.233.2877',
'Raleigh','27604','0123-4567-8910-1454', '04/04',
'Mike R Swigon','','' );

INSERT INTO Customer_Table 
values(2004,'Jay','','Johnston',
'With Jesse!!!','919.233.2877',
'Raleigh','27604','0123-4267-8910-1454', '04/04',
'Jay Johnston','','' );

INSERT INTO Customer_Table 
values(2004,'John','','Lamb',
'Above Jesse and Jay','919.233.2877',
'Raleigh','27604','1123-4567-8910-1454', '04/04',
'John Lamb','','' );

#END CUSTOMER TABLE STUFF

#BEGIN INVENTORY STUFF

INSERT INTO Inventory_Table
values(10000,'1011011010101','Canned Smushed Tomatoes',
'Food',50,200,35,200,'Can food','1','1',0.80,0.20,
'<bulk><amount>10</amount><discount>10</discount></bulk>',
now(),0.004,'F','F');

INSERT INTO Inventory_Table
values(10100,'10101101011010101','Hamburger Meat',
'Food',117,100,50,100,'Meat','1','3',1.99,0.99,
'<bulk><amount>5</amount><discount>10</discount></bulk>',
now(),1.000,'F','F');

INSERT INTO Inventory_Table
values(10110,'1001101011010101','50 Gallon Trash Can',
'Houseware',13,0,2,20,'Home','2','2',8.99,3.50,
'',now(),1.000,'F','F');

SELECT *  FROM Inventory_Table;