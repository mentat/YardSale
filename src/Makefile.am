## the hell with autocon
SUBDIRS = extra res tests

BUILDID = `cat build.id`

all:
	perl build.pl

clean:
	rm -f *.gz

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
	ys_carrier_type.cpp\
	wrapexpat.cpp\
	xml.cpp\
	xmlnode.cpp\
	ys_date.cpp\
	ys_group.cpp\
	ys_customer.cpp\
	ys_reports.cpp\
	ys_about_gl.cpp\
	ys_checkout.cpp\
	receipt.cpp


INCLUDES = -I../include
yardsale_LDFLAGS =

yardsale_LDADD =  \
	extra/xrc/libxrc.a $(GUI_LIBS)
    
binary: yardsale
	mkdir yardsale-$(BUILDID)
	mkdir yardsale-$(BUILDID)/res
	cp yardsale yardsale-$(BUILDID)
	cp res/*.xsl yardsale-$(BUILDID)/res
	cp res/*.png yardsale-$(BUILDID)/res
	cp res/*.xrc yardsale-$(BUILDID)/res
	cp res/flower.jpg yardsale-$(BUILDID)/res
	strip yardsale-$(BUILDID)/yardsale
	tar zcf yardsale-0.$(BUILDID).tar.gz yardsale-$(BUILDID)
	rm -rf yardsale-$(BUILDID)
