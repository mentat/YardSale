#include "otl_xml.h"
#include "otlv4.h"
#include <string>
#include <sstream>

using namespace std;

static string tab(int level)
{
    string ret;
    for (int i = 0; i < level; i++)
        ret += "    ";
    return ret;
}


// maybe redo this shit with a linked list or something
class an_otl_type
{
 public:
    static typ GetType(int type) {
        

    }

    static data GetData(int type) {
    }

    enum typ { var_bigint, var_blob, var_char, var_clob,
        var_db2_date, var_db2time, var_double, var_float,
        var_int, var_long_int, var_ltz_timestamp,
        var_raw_long, var_short, var_timestamp, var_tz_timestamp,
        var_unsigned_int, var_varchar_long };
    
    typ kind;
    union data { OTL_BIGINT, otl_lob_stream, char, otl_lob_stream, otl_datetime, otl_datetime, double
        float, int, long int, otl_datetime, /*raw_long,*/ short int,
        otl_datetime, otl_datetime, unsigned int, string };
}; 


static string otl_xml::process(otl_stream * stream)
{
    stringstream xml;
    xml << "<?xml version=\"1.0\" encoding=\"UTF-8\">" << endl;
    /// Build dynamic array for stream operation

    int length; // maybe instead use describe_select, see OTL example 33
    otl_var_desc * desc = stream->describe_out_vars(length);
    
    if (length == 0)
    {
        cerr << "Length is 0, aborting.\n";
        return "";
    }

    an_otl_type * array = new an_otl_array[length];

    for (int i = 0; i < length; i++) {
        array[i].kind = GetKind(desc[i].ftype);
        array[i].data = GetType(desc[i].ftype);
    }

    while (!stream->eof()) {
        
        /// get a copy of the an_otl_type here
        an_otl_type temp;

        try {
            for (int i = 0; i < length; i++)
                *stream >> temp.RefData(); 

        } catch (otl_exception &e) {
            cerr << "There was an exception..." << endl;
        }

        xml << tab(1) << "<row>" << endl;
        /// note need to encode all DB strings!
        xml << tab(2) << "<" << array[i].name << ">" 
            << temp.GetData() << "</" << array[i].name << ">" << endl;

    }	
}
