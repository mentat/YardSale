#include <iostream>
#include "receipt.h"
using namespace std;

/// Constructor, specify com port for printer.
Receipt::Receipt(const string& port): outport(port)
{
	tm = new ofstream(outport.c_str(), ios::out );
	//*tm << EP_cutpaper;
	EP_initialize();
	//this->EP_jcenter();
	header = "AS Logic Systems\n Thank you for your business!";
	//*tm << header << endl;
	//this->EP_jleft();
	printheader();
	//*tm << EP_initialize << header << EP_jleft;
}

/// Annnnd, the empty constructor.
Receipt::Receipt()
{
    tm = 0;
}

/// Resets all those critical values, lets you redef the port.
void Receipt::Init(const string& port)
{
    if (tm) 
        return; // if already initialized, dont do it again
    if (port == "")
        return;
    
    tm = new ofstream(port.c_str(), ios::out);
    EP_initialize();
	//this->EP_jcenter();
	header = "AS Logic Systems\n Thank you for your business!";
	//*tm << header << endl;
	//this->EP_jleft();
	printheader();  
}

/*
 * It's that "I just turned on my computer and started
 * YardSale" feeling, any time of the day you want it.
 */

/// Starts the printing process all over again, clears any data from
/// prev. transaction.
void Receipt::reset(){
    if (!tm) return;
	colist.clear();
	EP_initialize();
	printheader();
}

/*
 * This calls additem on an array of my fictional RTransType
 * objects.  WHOOPEE!
 */

/// This takes an array of transaction items and creates a receipt.
void Receipt::addTlist(vector <RTransType> tlist){
    for (int ii = 0; ii < tlist.size(); ii++)
		additem(tlist[ii].item, tlist[ii].price);
}

/*
 * Receipt::additem creates a vector of formatted strings
 * containing the item name and price, chopped up to fit in
 * 40 columns (42 actually).  There is probably a better way
 * to do this.
 */

/// Generate receipt one item at a time.
void Receipt::additem(const string& item, const string& price){
	string nitem = item.substr(0, 31);
	if (item.length() < 33) {
		for (int ii = 0; ii < 32 - item.length(); ii++) {
			nitem += " ";
		}
	}
	nitem += "$" + price;
	colist.push_back(nitem);
}

/*
 * U R St00pid if you don't know what this does.
 */

/// sets up the taxes/subtotal/total data.
void Receipt::totdata(const string& total, const string& ttx, const string& taxtotal){
	tot = total;
	tax = ttx;
	tottax = taxtotal;
}

/// Jesse added this.
void Receipt::change(const string& type, const string& tender, const string& change)
{
    m_type = type;
    m_tender = tender;
    m_change = change;
    
}

/*
 * This iterates through the checkout list and prints the data
 * in it, along with the subtotal, tax, and total for the current
 * transaction.  It then prints a header and a few newlines and
 * chops the receipt off right above the new header (I'm saving
 * paper!)
 */

/// This just prints the data gathered in a nice format, and chops
/// the paper (on some printarz.)
void Receipt::print(){
    if (!tm) return;
	for(int ii = 0; ii < colist.size(); ii++)
		*tm << colist[ii] << endl;
	*tm << "SUBTOTAL:          $" << tot << endl;
	*tm << "TAX:               $" << tax << endl;
	*tm << "TOTAL:             $" << tottax << endl << endl;
    if (m_type != "")
    {
        *tm << m_type << "               $" << m_tender << endl;
        *tm << "CHANGE:             $" << m_change << endl;
    }
    
//	this->EP_initialize();
//	*tm << "\n\n";
	printheader();
	EP_cutpaper();
	*tm << endl;
	//this->EP_pboth();
}

/*
 * centers the printing, prints the header string, and 
 * returns the printing to left justification.
 */

/// Formatting directives.
void Receipt::printheader(){
    if (!tm) return;
	EP_jcenter();
	*tm << endl << endl << header << endl;
	EP_jleft();
}

/*
 * ???
 */

/// Jesse added this.
void Receipt::test() {
    if (!tm) return;
	char test[] = { 0x00, 0x00, 0x61 };
	*tm << test << "\n\n\n\n\n";
}

/*
 * This batch of code-herpes is necessary because it's the
 * easiest way I know of right now to predefine strings that
 * contain the NULL byte.  Hah.
 */

/// reset printer
void Receipt::EP_initialize(){
    if (!tm) return;
	*tm << '\x1b' << '\x40';
}

/// cut paper
void Receipt::EP_cutpaper(){
    if (!tm) return;
	*tm << '\x1d' << '\x56' << '\x01' << endl;
}

/// print to pole only
void Receipt::EP_ppole(){
    if (!tm) return;
	*tm << '\x1b' << '\x3d' << '\x02';
}

/// print to printer only
void Receipt::EP_pprinter(){
    if (!tm) return;
	*tm << '\x1b' << '\x3d' << '\x01';
}

/// print to printer and pole.
void Receipt::EP_pboth(){
    if (!tm) return;
	*tm << '\x1b' << '\x3d' << '\x03';
}

/// justify my left.
void Receipt::EP_jleft(){
    if (!tm) return;
	*tm << '\x1b' << '\x61' << '\x00';
}

/// justify center
void Receipt::EP_jcenter(){
    if (!tm) return;
	*tm << '\x1b' << '\x61' << '\x01';
}

/// justify right
void Receipt::EP_jright(){
    if (!tm) return;
	*tm << '\x1b' << '\x61' << '\x02';
}

/// kick out cash drawer
void Receipt::EP_dkd(){ //kicks out cash drizzawer
	if (!tm) return;
    *tm << '\x1b' << 'p' << '\x00' << '\x64' << '\x64';
}
