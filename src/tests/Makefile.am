INCLUDES = -I../../include
CXXFLAGS = -g $(WX_CXXFLAGS) -ansi 

EXTRA_PROGRAMS = test_emp test_db test_inv test_cust test_trans test_carr test_grp

TESTS = test_db test_inv test_emp test_cust test_trans test_carr test_grp

test_db_SOURCES = ../ys_database.cpp ../ys_inv_type.cpp ../ys_log.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp \
	../ys_date.cpp ../ys_employee_type.cpp
test_db_LDADD =  -lodbc $(WX_LIBS)
test_db_CXXFLAGS =  $(WX_CXXFLAGS) -g -ansi -Wall -DYS_TEST_DB

test_inv_SOURCES = ../ys_inv_type.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp ../ys_date.cpp 
test_inv_LDADD = -lodbc -lexpat $(WX_LIBS)
test_inv_CXXFLAGS =  -DYS_TEST_INV_TYPE

test_emp_SOURCES = ../ys_employee_type.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp ../ys_date.cpp
test_emp_LDADD = -lodbc -lexpat $(WX_LIBS)
test_emp_CXXFLAGS =  -DYS_TEST_EMPLOYEE_TYPE

test_cust_SOURCES = ../ys_cust_type.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp ../ys_date.cpp
test_cust_LDADD = -lodbc -lexpat $(WX_LIBS)
test_cust_CXXFLAGS = -DYS_TEST_CUST_TYPE

test_trans_SOURCES = ../ys_trans_type.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp ../ys_date.cpp
test_trans_LDADD = -lodbc -lexpat $(WX_LIBS) 
test_trans_CXXFLAGS = -DYS_TEST_TRANS_TYPE

test_carr_SOURCES = ../ys_carrier_type.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp ../ys_date.cpp
test_carr_LDADD = -lodbc -lexpat $(WX_LIBS)
test_carr_CXXFLAGS = -DYS_TEST_CARR_TYPE

test_grp_SOURCES = ../ys_group.cpp ../xmlnode.cpp ../xml.cpp ../wrapexpat.cpp ../ys_date.cpp
test_grp_LDADD = -lodbc -lexpat $(WX_LIBS)
test_grp_CXXFLAGS = -DYS_TEST_GROUP_TYPE

