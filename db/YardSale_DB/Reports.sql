# Connection: local
# Host: localhost
# Saved: 2004-04-10 05:21:30
# 
# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-04-09 12:49:12
# 
use YardSale;

SELECT * 
FROM Transaction_Log_Table
WHERE 
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND NOW();

SELECT COUNT(DISTINCT TRANS_ID) AS Number_Of_Transactions
FROM Transaction_Log_Table
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND NOW();

#Get a List of all the transactions and their Inventory Information, and Employee and Customer Information for a date range
SELECT TRANS_ID, TRANS_REF_EMP_ID_Number AS Employee_ID, 
             TRANS_REF_INV_Item_ID, TRANS_REF_CUST_Account_Number, 
             TRANS_Sale_Price, TRANS_ID, TRANS_Quantity, TRANS_Comment,
             TRANS_Time,
             EMP_ID_Number, EMP_First_Name, EMP_Middle_Name, EMP_Last_Name
             INV_Item_Description, (TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price)) AS PROFIT_2 # 
FROM   Transaction_Log_Table JOIN Employee_Table 
            ON Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number  JOIN Customer_Table
            ON Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.Cust_Account_Number JOIN Inventory_Table
            ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND NOW();

#Get a sum of the profits for each transaction
#try unioning this with the query that gets a list of all items
#in a transaction
SELECT TRANS_ID, TRANS_REF_EMP_ID_Number AS Employee_ID, 
             TRANS_REF_INV_Item_ID, TRANS_REF_CUST_Account_Number, 
             TRANS_Sale_Price, TRANS_ID, TRANS_Quantity, TRANS_Comment,
             TRANS_Time,
             EMP_ID_Number, EMP_First_Name, EMP_Middle_Name, EMP_Last_Name
             INV_Item_Description, SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT_2 # 
FROM   Transaction_Log_Table JOIN Employee_Table 
            ON Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number  JOIN Customer_Table
            ON Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.Cust_Account_Number JOIN Inventory_Table
            ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND NOW()
GROUP BY TRANS_ID
UNION
#Get an hourly profit with this query
SELECT TRANS_ID, TRANS_REF_EMP_ID_Number AS Employee_ID, 
             TRANS_REF_INV_Item_ID, TRANS_REF_CUST_Account_Number, 
             TRANS_Sale_Price, TRANS_ID, TRANS_Quantity, TRANS_Comment,
             TRANS_Time,
             EMP_ID_Number, EMP_First_Name, EMP_Middle_Name, EMP_Last_Name
             INV_Item_Description, SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT # 
FROM   Transaction_Log_Table JOIN Employee_Table 
            ON Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number  JOIN Customer_Table
            ON Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.Cust_Account_Number JOIN Inventory_Table
            ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND '2004-04-10 23:00:00'
GROUP BY TRANS_Time; #Fix so that time does not have to be exactly the same - should be within the same hour

             