#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <string>
#include <stack>
#include <sstream>

#include "xml.h"

#ifndef LOG_DEBUG
#ifdef DEBUG
 #ifdef WIN32
  #include <fstream>
  static ofstream debugOut("xml_debug.txt");
  #define LOG_DEBUG(str) debugOut << str << endl;
 #else
  #include <iostream>
  #define LOG_DEBUG(str) cout << str << endl;
 #endif
#else
 #define LOG_DEBUG(str) {}
#endif
#endif // LOG_DEBUG


using namespace std;

string XMLParser::escape(string str)
{
    string a[] = {"&", "<", ">", "\"", "'"};
    string b[] = {"&amp;",  "&lt;",  "&gt;",  "&quot;",  "&apos;"};

    for (int i=0; i<5; i++) 
    {
        size_t pos=0;
        while ( ( pos = str.find(a[i], pos ) ) != std::string::npos ) 
        {
           str.replace( pos, a[i].length(), b[i] );
           pos += b[i].length(); // new starting point of search is just after 'b'
        }
    }
    return str;
}

void XMLParser::init(const string &line, Type type)
{
    switch (type)
    {
    case String:
        try {
            parse(line);
        }
        catch (Expat::ParseFailure &e)
        {
            throw ParseFailure(e.what());
        }
        break;
    case File:
    {
        string str;
        ifstream in(line.c_str());
        if (!in)
        {
            throw DiskError("XMLParser: Specified file cannot be opened.");
        }

        while (in.good())
        {
           getline(in,str);
           str+="\n";
           parse(str);
        }
        in.close();
    }
    break;
    };

}

XMLParser::XMLParser(const string &line, Type type)
: Expat()
{
    init(line, type);
}

XMLParser::XMLParser(XMLNode &_root)
: Expat()
{
    root = _root;  
}

XMLParser::~XMLParser()
{
    
}

int XMLParser::tree_to_xml(string &line)
{
    printTag(root,line);
    return 0;
}

int XMLParser::tree_to_file(const string &filename)
{
    string line;
    ofstream out(filename.c_str());

    if (!out)
    {
        throw DiskError("File Error!");
    }

    printTag(root,line);
    out << line;

    out.close();
    return 0;
}

vector<XMLNode> XMLParser::get_tags(const string &key)
{
    vector<XMLNode> ret;
    return ret;
}

int XMLParser::printTag(const XMLNode &node, string &ret, int indent)
{
	int s(0);
    
	// print indent
	for (s=0; s<indent; s++) 
        ret += "\t";

	// print tag name
    ret += "<" + XMLParser::escape(node.m_xmlData->m_name);
    
	// print properties
	for (AttributeMap::const_iterator i=node.m_xmlData->m_properties.begin();i!=node.m_xmlData->m_properties.end();i++)
    {
        if (i->second == "")
            ret+= " " + XMLParser::escape(i->first) + "=\"\"";
        else
            ret+= " " + XMLParser::escape(i->first) + "=\"" + XMLParser::escape(i->second) + "\"";
    }

	// if tag has no children, close and return
    if (( node.m_xmlData->m_data == "" || node.m_xmlData->m_data == "\n")  && node.m_xmlData->m_children.empty())
    {
        LOG_DEBUG(node.m_xmlData->m_name << " no children.");
		ret+="/>";
		return 0;
    }
    
	// if has data/children
	ret+=">";
    
	// print children
	bool childprinted = false;
	for (NodeMap::const_iterator it=node.m_xmlData->m_children.begin();it!=node.m_xmlData->m_children.end();it++)
    {
       ret+="\n";
       childprinted = true;
       string tmp;
       LOG_DEBUG("Printing children: " << it->second.m_xmlData->m_name); 
       printTag(it->second,tmp,indent+1);
       ret+=tmp;
    }
  
	// indent for data
	if (childprinted && (node.m_xmlData->m_data.length()>0))
        for (s=0; s<indent + 1; s++) 
           ret += "\t";

	if (node.m_xmlData->data_is_cdata)
        ret+="<![CDATA[";


    if (node.m_xmlData->m_data.length()>0)
    {
        if (node.m_xmlData->data_is_cdata)
           ret+=node.m_xmlData->m_data;
        else
           ret+=XMLParser::escape(node.m_xmlData->m_data);
    }

    if (node.m_xmlData->data_is_cdata)
        ret+="]]>";

    if (childprinted)
        ret+='\n';

    // print indent
    if (childprinted)
        for (s=0; s<indent; s++) ret += "\t";
    
    ret += "</" + XMLParser::escape(node.m_xmlData->m_name) + ">\n";
    
    return 0;
}


void XMLParser::recievedTag(XMLNode& n)
{
    root.addChild(n);
}

void XMLParser::rootTagRecieved(XMLNode& _root)
{
    root=_root;
}

void XMLParser::parserError(const string& errorMsg, int line)
{
    stringstream error;
    error << errorMsg << ": " << line;
    reset();

    throw ParseFailure(error.str().c_str());
}
