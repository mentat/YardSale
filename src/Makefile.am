## the hell with autoconf

INCLUDES =  -I../include

CXXFLAGS = $(WX_CXXFLAGS)  -g


#yardsale_CXXFLAGS =\
#	 $(WX_CXXFLAGS) \
#     -ansi \
#	 -Wall \
#	 -g

bin_PROGRAMS = yardsale
EXTRA_PROGRAMS = test_db test_inv test_bitmap

TESTS = test_db test_inv test_bitmap

yardsale_SOURCES = \
	yardsale.cpp\
	yardsale_wdr.cpp\
	ys_splash.cpp\
	ys_main.cpp\
	ys_inventory.cpp\
	ys_login.cpp\
	ys_sale.cpp\
	ys_calc.cpp\
	ys_employee.cpp\
	ys_log.cpp\
	ys_inv_type.cpp\
	ys_database.cpp\
	ys_bitmaps.cpp\
	ys_debug.cpp


yardsale_LDFLAGS = 

yardsale_LDADD =  \
	$(WX_LIBS) -lodbc

test_db_SOURCES = ys_database.cpp ys_inv_type.cpp ys_log.cpp
test_db_LDADD = $(WX_LIBS) -lodbc
test_db_CXXFLAGS = $(WX_CXXFLAGS) -g -ansi -Wall -DYS_TEST_DB

test_inv_SOURCES = ys_inv_type.cpp ys_log.cpp
test_inv_LDADD = $(WX_LIBS)
test_inv_CXXFLAGS = $(WX_CXXFLAGS) -g -ansi -Wall -DYS_TEST_INV_TYPE

test_bitmap_SOURCES = ys_bitmaps.cpp ys_log.cpp
test_bitmap_LDADD = $(WX_LIBS)
test_bitmap_CXXFLAGS = $(WX_CXXFLAGS) -g -ansi -Wall -DYS_TEST_BITMAPS

