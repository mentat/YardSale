# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-04-11 03:34:58
# 
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
GROUP BY TRANS_ID;

#Get an hourly profit with this query
SELECT TRANS_ID, TRANS_REF_EMP_ID_Number AS Employee_ID, 
             TRANS_REF_INV_Item_ID, TRANS_REF_CUST_Account_Number, 
             TRANS_Sale_Price, TRANS_ID, TRANS_Quantity, TRANS_Comment,
             EXTRACT(HOUR FROM TRANS_Time),
             EMP_ID_Number, EMP_First_Name, EMP_Middle_Name, EMP_Last_Name
             INV_Item_Description, SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT # 
FROM   Transaction_Log_Table JOIN Employee_Table 
            ON Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number  JOIN Customer_Table
            ON Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.Cust_Account_Number JOIN Inventory_Table
            ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND '2004-04-10 23:00:00'
GROUP BY EXTRACT(HOUR FROM TRANS_Time); 

#This is a combined query. It Gives a total amount of profit made over each hour given a date range.
#This date range should normally be a open - close period although it could range from any 
#amount of time.
#
#The last column will always be the sum of all of the profit - the Hour field for this last column will
#always be totally bogus information but is required to allow the UNION operation to work.
SELECT EXTRACT(HOUR FROM TRANS_Time) AS Hour,
             SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT # 
FROM   Transaction_Log_Table  JOIN Inventory_Table
            ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND '2004-04-10 23:00:00'
GROUP BY EXTRACT(HOUR FROM TRANS_Time)
UNION
SELECT TRANS_Time AS Hour, 
              SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT # 
FROM    Transaction_Log_Table  JOIN Inventory_Table
             ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND '2004-04-10 23:00:00'
GROUP BY TRANS_Always_Null;


################################################
# EMPLOYEE TIME TRACKING STUFF IS BELOW HERE #
################################################

#SHOW THE AMOUNT OF TIME AN EMPLOYEE HAS WORKED GIVEN A DATE RANGE
#THE Time_Worked Value is at least 2 digits. The two least significant digits are the minutes 0-60. The 3+ Significant digits are the
#hours worked. Minutes = Time_Worked / 100, Hours = Time_Worked % 100

SELECT EMP_First_Name, Emp_Last_Name, 
             EXTRACT(HOUR FROM LOG_Time_Out - LOG_Time_In) AS Time_Worked_Hours,
             EXTRACT(HOUR_MINUTE FROM LOG_Time_Out - LOG_Time_In)%100 AS Time_Worked_Minutes,
             DATE_FORMAT(Log_Time_Out, '%W %M %D' ) AS Worked_On_Date
FROM Login_Table JOIN Employee_Table ON LOG_REF_EMP_ID = EMP_ID_Number
WHERE LOG_Count = 0 AND
LOG_Time_In BETWEEN '2004-04-01' AND '2004-04-07';

             