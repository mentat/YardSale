DROP DATABASE IF EXISTS PERSON;
CREATE DATABASE PERSON;
USE PERSON;

#MAKE SURE ITS GONE BEFORE YOU TRY TO MAKE A NEW ONE
DROP TABLE IF EXISTS Personal_Info;

#TABLE CREATION SAMPLE
CREATE TABLE Personal_Info (
	PI_Social_Security_Number	varchar(11),
	PI_First_Name	varchar(30),
	PI_Middle_Name	varchar(30),
	PI_Last_Name	varchar(30),
	PI_Phone_Number	varchar(20),
	PI_House_Number	INT,
	PI_Street_Name	varchar(50),
	PI_City		varchar(30),
	PI_State	varchar(2),
	PI_Zip_Code	INT,
	Primary Key (PI_Social_Security_Number)
) ;

#SAMPLE INSERT DATA STATEMENT
INSERT INTO Personal_Info VALUES('255-45-6549','William','Adam','Parrish','919.334.5675',7598,'Some Street BLVD','Raleigh','NC',27606);

#VERY BASIC SELECT STATEMENT
SELECT * FROM Personal_Info;
