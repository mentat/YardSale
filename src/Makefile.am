## the hell with autocon
INCLUDES =  -I../include
SUBDIRS = extra res tests

CXXFLAGS = $(WX_CXXFLAGS)  -g

all:
	perl build.pl

rez: yardsale
	$(REZFLAGS) yardsale

bin_PROGRAMS = yardsale

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
	ys_tax_type.cpp\
	ys_build.cpp\
	ys_vend_type.cpp\
	wrapexpat.cpp\
	xml.cpp\
	xmlnode.cpp\
	ys_date.cpp\
	ys_group.cpp

yardsale_LDFLAGS = -Lextra/xrc

yardsale_LDADD =  \
	$(WX_LIBS) -lodbc -lxrc
