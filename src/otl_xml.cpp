#include "otl_xml.h"
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#define OTL_ODBC_MYSQL
#define OTL_STL

#ifndef WIN32
#define OTL_ODBC_UNIX
#else
#define OTL_ODBC
#endif

#include <otlv4.h>

using namespace std;

// plan C
static string tab(int level)
{
    string ret;
    for (int i = 0; i < level; i++)
        ret += "    ";
    return ret;
}

string ToXML(otl_stream * stream)
{
    
    if (!stream)
        return "";
    
    int length = 0;
    otl_column_desc* desc = stream->describe_select(length);
    stringstream xml;
    xml << "<?xml version=\"1.0\" encoding=\"UTF-8\">" << endl;
    xml << "<result>" << endl;
    
    while (!stream->eof())
    {
        xml << tab(1) << "<record>" << endl;

        for(int i = 0; i < length; i++)
        {
            xml << tab(2) << "<" << desc[i].name << ">" << endl;
            
            switch(desc->dbtype) {
                case(otl_var_varchar_long): {
                    string i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_int):{
                    int i;
                    *stream >> i;
                    xml << i;}
                    break;
                 case(otl_var_char):{
                    char i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_db2date): 
                case(otl_var_db2time): 
                case(otl_var_ltz_timestamp): 
                case(otl_var_timestamp): 
                case(otl_var_tz_timestamp): {
                    otl_datetime i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_float):{
                    float i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_double): {
                    double i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_long_int): {
                    long int i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_short):{
                    short i;
                    *stream >> i;
                    xml << i;}
                    break;
                case(otl_var_unsigned_int): {
                    unsigned int i;
                    *stream >> i;
                    xml << i;}
                    break;
                #ifdef OTL_BIGINT
                case(otl_var_bigint): {
                    long long i;
                    *stream >> i;
                    xml << i; }
                    break;
                #endif
                #if 0
                case(otl_var_clob): 
                case(otl_var_blob): {
                    otl_lob_stream i;
                    *stream >> i;
                    xml << i;}
                    break;
                #endif
                default: cerr << "Throw a fucking exception" << endl;
                    break;
            }
            xml << "</" << desc[i].name << ">" << endl;

        }
        xml << tab(1) << "</record>" << endl;
    }
    xml << "</result>" << endl;
        
}
















#if 0
template <class T> 
string ToString(otl_stream * stream,T& v) 
{
    stringstream st;
    *stream >> v;
    st << v;
}

class Shit {
public:
    
    Shit(int id): m_id(id) {
      /*  
        switch(id) {
            #ifdef OTL_BIGINT
            case(otl_var_bigint): 
                m_type = new long long(0); break;
            #endif
            case(otl_var_blob): 
                m_type = new otl_lob_stream(); break;
            case(otl_var_char): 
                m_type = new char(0); break;
            case(otl_var_clob): 
                m_type = new otl_lob_stream(); break;
            case(otl_var_db2date): 
                m_type = new otl_datetime(); break;
            case(otl_var_db2time): 
                m_type = new otl_datetime(); break;
            case(otl_var_double): 
                m_type = new double(0.0); break;
            case(otl_var_float): 
                m_type = new float(0.0); break;
            case(otl_var_int): 
                m_type = new int(0); break;
            case(otl_var_long_int): 
                m_type = new long int(0); break;
            case(otl_var_ltz_timestamp): 
                m_type = new otl_datetime(); break;
            case(otl_var_raw_long): 
                m_type = new otl_lob_stream(); break;
            case(otl_var_short): 
                m_type = new short int(0); break;
            case(otl_var_timestamp): 
                m_type = new otl_datetime(); break;
            case(otl_var_tz_timestamp): 
                m_type = new otl_datetime(); break;
            case(otl_var_unsigned_int): 
                m_type = new unsigned int(0); break;
            case(otl_var_varchar_long): 
                m_type = new string(); break;
            default: cerr << "Throw a fucking exception" << endl;
                break;
        }*/
    }

    int GetType() const { return m_id; }

    //long long& GetLLInt();// { long long(*m_type); }
   // otl_lob_stream& GetLob();
    char& GetChar();
    otl_datetime& GetDate();
    double& GetDouble();
    float& GetFloat();
    int& GetInt();
    long int& GetLInt();
    short int& GetSInt();
    unsigned int& GetUInt();
    string& GetString();

private:
    int m_id;
    void * m_type; // terrible, nastly, shit
};

class OTLPoly {
 public:
    OTLPoly() {}
        
    OTLPoly & operator>>(otl_stream * stream)
    {
        if (!stream)
            return *this;
        
        int length = 0;
        otl_column_desc* desc = stream->describe_select(length);
        
        PolyRow master_row;
        
        for(int i = 0; i < length; i++)
        {
            
            switch(desc->dbtype) {
                #ifdef OTL_BIGINT
                case(otl_var_bigint): 
                    master_row.Data().push_back(new variant_t(long long(0))); break;
                #endif
                case(otl_var_blob): 
                    master_row.Data().push_back(new variant_t(otl_lob_stream())); break;
                case(otl_var_char): 
                    master_row.Data().push_back(new variant_t(char(0))); break;
                case(otl_var_clob): 
                    master_row.Data().push_back(new variant_t(otl_lob_stream())); break;
                case(otl_var_db2date): 
                    master_row.Data().push_back(new variant_t(otl_datetime())); break;
                case(otl_var_db2time): 
                    master_row.Data().push_back(new variant_t(otl_datetime())); break;
                case(otl_var_double): 
                    master_row.Data().push_back(new variant_t(double(0.0))); break;
                case(otl_var_float): 
                    master_row.Data().push_back(new variant_t(float(0.0))); break;
                case(otl_var_int): 
                    master_row.Data().push_back(new variant_t(int(0))); break;
                case(otl_var_long_int): 
                    master_row.Data().push_back(new variant_t(long int(0))); break;
                case(otl_var_ltz_timestamp): 
                    master_row.Data().push_back(new variant_t(otl_datetime())); break;
                case(otl_var_raw_long): 
                    master_row.Data().push_back(new variant_t(otl_lob_stream())); break;
                case(otl_var_short): 
                    master_row.Data().push_back(new variant_t(short int(0))); break;
                case(otl_var_timestamp): 
                    master_row.Data().push_back(new variant_t(otl_datetime())); break;
                case(otl_var_tz_timestamp): 
                    master_row.Data().push_back(new variant_t(otl_datetime())); break;
                case(otl_var_unsigned_int): 
                    master_row.Data().push_back(new variant_t(unsigned int(0))); break;
                case(otl_var_varchar_long): 
                    master_row.Data().push_back(new variant_t(string())); break;
                default: cerr << "Throw a fucking exception" << endl;
                    break;
            }

        }

        while(!stream->eof()) {
            
            PolyRow temp(master_row); // hoping this will copy the templates over
            
            for (int i = 0; i < temp.Data().size(); i++)
            {
                *stream >> temp.Data()[i];
            }
        }
        
        return *this;
    }
    
 private:
    
    vector<string> m_rowNames;
    vector<PolyRow> m_rows;
    
};


#endif
#if 0
static string otl_xml::process(otl_stream * stream)
{
    stringstream xml;
    xml << "<?xml version=\"1.0\" encoding=\"UTF-8\">" << endl;
    /// Build dynamic array for stream operation

    int length; // maybe instead use describe_select, see OTL example 33
    otl_column_desc* desc = stream->describe_select(length);
    
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
#endif
