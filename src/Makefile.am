## the hell with autocon
INCLUDES =  -I../include
SUBDIRS = extra res tests

BUILDID = `cat build.id`

CXXFLAGS = $(WX_CXXFLAGS)  -g

all:
	perl build.pl

rez: yardsale
	$(REZFLAGS) yardsale

bin_PROGRAMS = yardsale

yardsale_SOURCES = \
	yardsale.cpp\
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
	ys_group.cpp\
	ys_customer.cpp\
	ys_reports.cpp

yardsale_LDFLAGS = -Lextra/xrc

yardsale_LDADD =  \
	$(WX_LIBS) -lodbc -lxrc -lsablot
    
binary: yardsale
	mkdir yardsale-$(BUILDID)
	mkdir yardsale-$(BUILDID)/res
	cp yardsale yardsale-$(BUILDID)
	cp res/*.xsl yardsale-$(BUILDID)/res
	cp res/*.png yardsale-$(BUILDID)/res
	cp res/*.xrc yardsale-$(BUILDID)/res
	strip yardsale-$(BUILDID)/yardsale
	tar zcf yardsale-0.$(BUILDID).tar.gz yardsale-$(BUILDID)
	rm -rf yardsale-$(BUILDID)
	scp yardsale-$(BUILDID).tar.gz thementat@yardsale.sf.net:/home/groups/y/ya/yardsale/htdocs/builds
