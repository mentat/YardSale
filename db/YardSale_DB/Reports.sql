# Connection: rau
# Host: rau.ece.ncsu.edu
# Saved: 2004-04-11 03:11:54
# 
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

#####################################################################
# SALES SUMMARY REPORT QUERY - SHOWS HOURLY PROFIT BREAKDOWN   #
#####################################################################
#This is a combined query. It Gives a total amount of profit made over each hour given a date range.
#This date range should normally be a open - close period although it could range from any 
#amount of time.
#
#The last column will always be the sum of all of the profit - the Hour field for this last column will
#always be totally bogus information but is required to allow the UNION operation to work.
#
# THIS QUERY EXPECTS A START DATE AND AN END DATE
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
#
#COLUMNS NAMES RETURNED
# ID_Number :: ID Number of Employee
# First_Name :: First Name of Employee
# Last_Name :: Last Name of Employee
# Time_Worked_Hours :: Amount of hours worked by the employee
# Time_Worked_Minutes :: Amount of minutes worked by the employee
# Worked_On_Date :: Day that the hours were logged
#
# THIS QUERY EXPECTS A START DATE AND AN END DATE

SELECT EMP_ID_Number AS ID_Number , EMP_First_Name AS First_Name, Emp_Last_Name AS Last_Name, 
             EXTRACT(HOUR FROM LOG_Time_Out - LOG_Time_In) AS Time_Worked_Hours,
             EXTRACT(HOUR_MINUTE FROM LOG_Time_Out - LOG_Time_In)%100 AS Time_Worked_Minutes,
             DATE_FORMAT(Log_Time_Out, '%W %M %D' ) AS Worked_On_Date
FROM Login_Table JOIN Employee_Table ON LOG_REF_EMP_ID = EMP_ID_Number
WHERE LOG_Count = 0 AND
LOG_Time_In BETWEEN '2004-04-01' AND '2004-04-07';

########################################
# EMPLOYEE SALES STUFF IS BELOW HERE #
########################################

#COLUMN NAMES RETURNED:
#Employee_ID :: The ID Number of the Employee Referenced on the current Row
#First_Name :: The Employee's first name
#Last_Name :: The Employee's last name
#PROFIT :: The Amount of profit the Employee Made in the time period
#RETAIL_TOTAL :: The amount of money the Employee actually brought in not considering the amount the items where bought for
#TOTAL_WHOLESALE_COST :: Total amount of money invensted in the items sold by the employee
#
# THIS QUERY EXPECTS A START DATE AND AN END DATE 

SELECT TRANS_REF_EMP_ID_Number AS Employee_ID, 
             EMP_First_Name AS First_Name, EMP_Last_Name AS Last_Name,
             SUM((TRANS_Quantity * (TRANS_Sale_Price - INV_Wholesale_Price))) AS PROFIT,
             SUM(TRANS_Sale_Price * TRANS_Quantity) AS RETAIL_TOTAL,
             SUM(INV_Wholesale_Price * TRANS_Quantity) AS TOTAL_WHOLESALE_COST
FROM   Transaction_Log_Table JOIN Employee_Table 
            ON Transaction_Log_Table.TRANS_REF_EMP_ID_Number = Employee_Table.EMP_ID_Number  JOIN Customer_Table
            ON Transaction_Log_Table.TRANS_REF_CUST_Account_Number = Customer_Table.Cust_Account_Number JOIN Inventory_Table
            ON Transaction_Log_Table.TRANS_REF_INV_Item_ID = Inventory_Table.INV_Item_ID
WHERE
TRANS_Time BETWEEN
'2004-04-01 00:00:00' AND Now()
GROUP BY TRANS_REF_EMP_ID_Number;

             