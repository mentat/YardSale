## the hell with autocon
INCLUDES =  -I../include
#SUBDIRS = wxrc

CXXFLAGS = $(WX_CXXFLAGS)  -g

rez: yardsale
	$(REZFLAGS) yardsale

bin_PROGRAMS = yardsale
EXTRA_PROGRAMS = test_emp test_db test_inv test_bitmap test_cust test_trans   

TESTS = test_db test_inv test_emp test_bitmap test_cust test_trans

yardsale_SOURCES = \
	yardsale.cpp\
	yardsale_wdr.cpp\
	ys_splash.cpp\
	ys_main.cpp\
	ys_inventory.cpp\
	ys_login.cpp\
	ys_sale.cpp\
	ys_calc.cpp\
	ys_keybrd.cpp\
	ys_employee.cpp\
	ys_log.cpp\
	ys_inv_type.cpp\
	ys_database.cpp\
	ys_bitmaps.cpp\
	ys_debug.cpp\
	ys_config.cpp\
	ys_footer.cpp\
	ys_calc_dlg.cpp\
	ys_employee_type.cpp\
    	ys_cust_type.cpp\
	ys_keybrd_dlg.cpp\
	ys_trans_type.cpp\
	ys_tax_type.cpp

yardsale_LDFLAGS = 

yardsale_LDADD =  \
	$(WX_LIBS) -lodbc

test_db_SOURCES = ys_database.cpp ys_inv_type.cpp ys_log.cpp
test_db_LDADD =  -lodbc $(WX_LIBS)
test_db_CXXFLAGS =  $(WX_CXXFLAGS) -g -ansi -Wall -DYS_TEST_DB

test_inv_SOURCES = ys_inv_type.cpp 
test_inv_LDADD = -lodbc
test_inv_CXXFLAGS =  -g -ansi -Wall -DYS_TEST_INV_TYPE

test_bitmap_SOURCES = ys_bitmaps.cpp ys_log.cpp
test_bitmap_LDADD = $(WX_LIBS)
test_bitmap_CXXFLAGS = $(WX_CXXFLAGS) -g -ansi -Wall -DYS_TEST_BITMAPS

test_emp_SOURCES = ys_employee_type.cpp
test_emp_LDADD = -lodbc
test_emp_CXXFLAGS = -g -ansi -Wall -DYS_TEST_EMPLOYEE_TYPE

test_cust_SOURCES = ys_cust_type.cpp
test_cust_LDADD = -lodbc
test_cust_CXXFLAGS = -g -ansi -Wall -DYS_TEST_CUST_TYPE

test_trans_SOURCES = ys_trans_type.cpp
test_trans_LDADD = -lodbc
test_trans_CXXFLAGS = -g -ansi -Wall -DYS_TEST_TRANS_TYPE

