#include <vector>
#include <fstream>
#include <string>
using namespace std;

#define YSPGENERIC 0
#define YSPESCPOS 1
#define YSPSTAR 2

class RTransType{
	public:
		string item;
		string price;
};

class ysReceiptPrinterCodes{
	private:
		string header;
		int ptype;
		ofstream *printer;
	public:
		ysReceiptPrinterCodes();
		ysReceiptPrinterCodes(ofstream &printer, const int& ptype,
				const string& header);
		void justleft();
		void justcenter();
		void justright();
		void prnpole();
		void prnpaper();
		void prnboth();
		void cutpaper();
		void initialize();
		void printheader();
		void finishreceipt();
};

/*
 * For ESC/POS printers.
 */
class ysEPRPCodes : public ysReceiptPrinterCodes{
	private:
		// none
	public:
		// from parent
};

class ysSRPCodes : public ysReceiptPrinterCodes{
	private:
		// none
	public:
		// from parent
};

class ysGenRPCodes : public ysReceiptPrinterCodes{
	private:
		// none
	public:
		// from parent
};

class Receipt
{
	private:
		string outport, tot, tax, tottax, header;
		vector <string> colist;
		ofstream *tm;
		int ptype;
		ysReceiptPrinterCodes pcodes;
	public:
		Receipt(const string& port = "/dev/ttyS2");
        
		~Receipt() { delete tm; }
        
		void reset();
		void addTlist(vector <RTransType> tlist);
		void additem(const string& item, const string& price);
		void totdata(const string& total, const string& ttx,
				const string& taxtotal);
		void print();
		/*
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
		*/
};

