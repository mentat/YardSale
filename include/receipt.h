#ifndef RECEIPT_H
#define RECEIPT_H

#include <vector>
#include <fstream>
#include <string>
using namespace std;

class RTransType{
	public:
		string item;
		string price;
};

/**
 This class is the abstraction layer for the
 receipt printers.

 @author John Lamb
*/
class Receipt
{
	private:
		string m_type, outport, tot, tax, tottax, header, m_change, m_tender;
		vector <string> colist;
		ofstream *tm;
	public:
	/// Constructor, specify com port for printer.
	Receipt(const string& port);
	/// Annnnd, the empty constructor.
        Receipt();
	/// Resets all those critical values, lets you redef the port.
        void Init(const string& port);
        void Clear() { colist.clear(); }
        ~Receipt() { delete tm; }
        
		/// Starts the printing process all over again, clears any data from
		/// prev. transaction.
		void reset();
		/// This takes an array of transaction items and creates a receipt.
		void addTlist(vector <RTransType> tlist);
		/// Generate receipt one item at a time.
		void additem(const string& item, const string& price);
		/// sets up the taxes/subtotal/total data.
		void totdata(const string& total, const string& ttx, const string& taxtotal);
		/// Jesse added this.
		void change(const string& type, const string& tender, const string& change);
		/// This just prints the data gathered in a nice format, and chops
		/// the paper (on some printarz.)
		void print();
		/// Print header
		void printheader();
		/// Jesse added this.
		void test();
		/// reset printer
		void EP_initialize();
		/// cut paper
		void EP_cutpaper();
		/// print to pole only
		void EP_ppole();
		/// print to printer only
		void EP_pprinter();
		/// print to printer and pole.
		void EP_pboth();
		/// justify my left.
		void EP_jleft();
		/// justify center
		void EP_jcenter();
		/// justify right
		void EP_jright();
		/// kick out cash drawer
		void EP_dkd();
};
#endif
