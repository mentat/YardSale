#include <iostream>
#include "receipt.h"
using namespace std;

Receipt::Receipt()
{
	outport = "/dev/ttyS2";
	tm = new ofstream(outport.c_str(), ios::out );
	//*tm << EP_cutpaper;
	this->EP_initialize();
	//this->EP_jcenter();
	header = "AS Logic\n Selling you free shit\n since right about now.";
	//*tm << header << endl;
	//this->EP_jleft();
	this->printheader();
	//*tm << EP_initialize << header << EP_jleft;
}

/*
 * It's that "I just turned on my computer and started
 * YardSale" feeling, any time of the day you want it.
 */
void Receipt::reset(){
	colist.clear();
	this->EP_initialize();
	this->printheader();
}

/*
 * This calls additem on an array of my fictional RTransType
 * objects.  WHOOPEE!
 */
void Receipt::addTlist(vector <RTransType> tlist){
	for (int ii = 0; ii < tlist.size(); ii++)
		this->additem(tlist[ii].item, tlist[ii].price);
}

/*
 * Receipt::additem creates a vector of formatted strings
 * containing the item name and price, chopped up to fit in
 * 40 columns (42 actually).  There is probably a better way
 * to do this.
 */
void Receipt::additem(string item, string price){
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
void Receipt::totdata(string total, string ttx, string taxtotal){
	tot = total;
	tax = ttx;
	tottax = taxtotal;
}

/*
 * This iterates through the checkout list and prints the data
 * in it, along with the subtotal, tax, and total for the current
 * transaction.  It then prints a header and a few newlines and
 * chops the receipt off right above the new header (I'm saving
 * paper!)
 */
void Receipt::print(){
	for(int ii = 0; ii < colist.size(); ii++)
		*tm << colist[ii] << endl;
	*tm << "SUBTOTAL:        $" << tot << endl;
	*tm << "TAX:             $" << tax << endl;
	*tm << "TOTAL:           $" << tottax << endl;
//	this->EP_initialize();
//	*tm << "\n\n";
	this->printheader();
	this->EP_cutpaper();
	*tm << endl;
	//this->EP_pboth();
}

/*
 * centers the printing, prints the header string, and 
 * returns the printing to left justification.
 */
void Receipt::printheader(){
	this->EP_jcenter();
	*tm << endl << endl << header << endl;
	this->EP_jleft();
}

/*
 * ???
 */
void Receipt::test() {
	char test[] = { 0x00, 0x00, 0x61 };
	*tm << test << "\n\n\n\n\n";
}

/*
 * This batch of code-herpes is necessary because it's the
 * easiest way I know of right now to predefine strings that
 * contain the NULL byte.  Hah.
 */

void Receipt::EP_initialize(){
	*tm << '\x1b' << '\x40';
}
void Receipt::EP_cutpaper(){
	*tm << '\x1d' << '\x56' << '\x01' << endl;
}
void Receipt::EP_ppole(){
	*tm << '\x1b' << '\x3d' << '\x02';
}
void Receipt::EP_pprinter(){
	*tm << '\x1b' << '\x3d' << '\x01';
}
void Receipt::EP_pboth(){
	*tm << '\x1b' << '\x3d' << '\x03';
}
void Receipt::EP_jleft(){
	*tm << '\x1b' << '\x61' << '\x00';
}
void Receipt::EP_jcenter(){
	*tm << '\x1b' << '\x61' << '\x01';
}
void Receipt::EP_jright(){
	*tm << '\x1b' << '\x61' << '\x02';
}


//int main(){
//	Receipt rr;
//	rr.additem("poop", "0.50");
//	rr.totdata("0.50", "0.4", "0.54");
//	rr.print();
////	rr.test();
//	return 0;
//}
//
