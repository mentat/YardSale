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
		Receipt(const string& port);
        Receipt();
        void Init(const string& port);
        void Clear() { colist.clear(); }
        ~Receipt() { delete tm; }
        
		void reset();
		void addTlist(vector <RTransType> tlist);
		void additem(const string& item, const string& price);
		void totdata(const string& total, const string& ttx, const string& taxtotal);
		void change(const string& type, const string& tender, const string& change);
        void print();
        /// Printer header
		void printheader();
		void test();
		void EP_initialize();
		void EP_cutpaper();
		void EP_ppole();
		void EP_pprinter();
		void EP_pboth();
		void EP_jleft();
		void EP_jcenter();
		void EP_jright();
		void EP_dkd();
};
#endif
