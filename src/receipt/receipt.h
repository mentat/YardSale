#include <vector>
#include <fstream>
#include <string>
using namespace std;

class RTransType{
	public:
		string item;
		string price;
};

class Receipt
{
	private:
		string outport, tot, tax, tottax, header;
		vector <string> colist;
		ofstream *tm;
	public:
		Receipt();
		void reset();
		void addTlist(vector <RTransType> tlist);
		void additem(string item, string price);
		void totdata(string total, string ttx, string taxtotal);
		void print();
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
};

