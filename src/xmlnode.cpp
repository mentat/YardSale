// --*-c++-*--
/*
    $Id: xmlnode.cpp,v 1.2 2004/04/18 22:03:54 thementat Exp $
 
    GNU Messenger - The secure instant messenger
    Copyright (C) 2001-2002  Henrik Abelsson <henrik@abelsson.com>
 
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/

#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib> // for atol
#include <cerrno> // for atol as well

#include "xmlnode.h"
#include "xml.h"

#ifndef LOG_DEBUG
#ifdef DEBUG
 #ifdef WIN32
  #include <fstream>
  static ofstream debugOut("xmlnode_debug.txt");
  #define LOG_DEBUG(str) debugOut << str << endl;
 #else
  #include <iostream>
  #define LOG_DEBUG(str) cout << str << endl;
 #endif
#else
 #define LOG_DEBUG(str) {}
#endif
#endif // LOG_DEBUG
     
#if 0
#ifdef _UNICODE
#undef string
#define string basic_string<wchar_t>
#endif
#endif

using namespace std;

XMLNode::XMLNode()
{
    m_xmlData=new XMLNodeData();
    m_xmlData->data_is_cdata=false;
    m_xmlData->oneline=false;
}

XMLNode::XMLNode(const XMLNode &other)
{
    other.m_xmlData->ref();
    m_xmlData=other.m_xmlData;
}

XMLNode::XMLNode(const string& name, const string& data)
{
    m_xmlData=new XMLNodeData();
    m_xmlData->data_is_cdata=false;
    m_xmlData->oneline=false;
    m_xmlData->m_name = name;
    m_xmlData->m_data = data;
}
    
XMLNode::XMLNode(const string& id, Resource res)
{
    try 
    {
        if (res == File)
        {
            XMLParser p(id,XMLParser::File);
            p.get_root().m_xmlData->ref();
            m_xmlData = p.get_root().m_xmlData;
        }
        else if (res == Str)
        {
            XMLParser p(id, XMLParser::String);
            p.get_root().m_xmlData->ref();
            m_xmlData = p.get_root().m_xmlData;
        }
       
    }
    catch(XMLParser::ParseFailure &e)
    {
        throw ParseFailure(e.what());
    }	
}

XMLNode::~XMLNode()
{
    if ((m_xmlData) && m_xmlData->deref())
    {
        delete m_xmlData;
        m_xmlData=0;
    }
}

bool XMLNode::hasChild(const string &name, int n) const
{
    // multimap: logarithmic
    // hash_mmap: Average is constant time. Worst is linear in the size of the container.
    if (m_xmlData->m_children.find(name) == m_xmlData->m_children.end())
        return false;
    return true;
}

unsigned int XMLNode::numChildren(const string &name) const
{
    // multimap:  O(log(size()) + count(k))
    // hash_mmap: Average is O(count(k)). Worst is linear in the size of the container.
    return m_xmlData->m_children.count(name);
}

const string XMLNode::property(const string &name) const
{
    // average is constant time, worst is linear in size of container
    AttributeMap::const_iterator it=m_xmlData->m_properties.find(name);
    
    if (it == m_xmlData->m_properties.end())
        return "";
    else
        return it->second;
}

long XMLNode::ToLong(const string& str) 
{
    long convert;
    errno = 0;
    convert = atol(str.c_str());
    
    if (errno == ERANGE)
        throw RangeOverflow("The string cannot be represented in the intended result type.");
    
    return convert;
}

int XMLNode::ToInt(const string& str)
{
    int convert;
    errno = 0;
    convert = atoi(str.c_str());
    
    if (errno == ERANGE)
        throw RangeOverflow("The string cannot be represented in the intended result type.");
    
    return convert;
}

double XMLNode::ToDouble(const string& str)
{    
    double convert;
    errno = 0;
    convert = atof(str.c_str());
    
    if (errno == ERANGE)
        throw RangeOverflow("The string cannot be represented in the intended result type.");
    
    return convert;
}

string XMLNode::ToStr(long numeric)
{
    stringstream ret;
    ret << numeric;
    LOG_DEBUG("ToStr: " << ret.str());
    return ret.str();
}

string XMLNode::ToStr(double floating, unsigned int precision)
{
    stringstream ret;
    ret.setf(ios_base::fixed, ios_base::floatfield);
    ret.precision(precision);
    // precision is total number of digits in iomanip! :(
    ret << floating;
    LOG_DEBUG("ToStrD: " << ret.str());
    return ret.str();
}

long XMLNode::intProperty(const string &name) const
{
    // average is constant time, worst is linear in size of container
    AttributeMap::const_iterator it=m_xmlData->m_properties.find(name);
    
    if (it==m_xmlData->m_properties.end())
        return 0;
    else
        return ToLong(it->second.c_str());
}

vector<XMLNode> XMLNode::children(const string& name)
{
    vector<XMLNode> ret;
    pair<NodeMap::iterator, NodeMap::iterator> p(m_xmlData->m_children.equal_range(name));

    while (p.first != m_xmlData->m_children.end())
        ret.push_back((p.first++)->second);
    
    return ret;   
}

/// Return all children
vector<XMLNode> XMLNode::children() 
{ 
    vector<XMLNode> ret;
    for (NodeMap::iterator it = m_xmlData->m_children.begin();
            it != m_xmlData->m_children.end(); it++)
       ret.push_back(it->second);
    
    return ret;
}

/// Return all children (read only)
/// @todo This makes no sence with the reference counted XMLNode!!!!!!!!!111
vector<XMLNode> XMLNode::const_children() const 
{    
   vector<XMLNode> ret;
    for (NodeMap::const_iterator it = m_xmlData->m_children.begin();
            it != m_xmlData->m_children.end(); it++)
       ret.push_back(it->second);
    
    return ret;
}


XMLNode& XMLNode::child(const string &name, unsigned int n)
{
    NodeMap::iterator it = m_xmlData->m_children.find(name);
    
    if (it == m_xmlData->m_children.end())
        return addChild(name, "");
 
    if (n == 0)
    {
        LOG_DEBUG("Found at n=0");
        return it->second;
    }
     
    // Logarithmic calls (lower_bound and upper_bound)
    // if using multimap, or constant if hash_multimap
    
    pair<NodeMap::iterator, NodeMap::iterator> p(m_xmlData->m_children.equal_range(name));
    
    while( (n > 0) && (++p.first != m_xmlData->m_children.end()) ) {
        if (--n == 0)
            return (p.first)->second;
    }
    LOG_DEBUG("No child of that key at index");
    return addChild(name, "");
}

XMLNode XMLNode::child(const string& name, unsigned int n) const
{
    LOG_DEBUG("Const child.");
    // hash_mmap: Average is O(count(k)). 
    //            Worst case is linear in the size of the container.
    // multimap:  at most logarithmic
    pair<NodeMap::const_iterator, NodeMap::const_iterator> p(m_xmlData->m_children.equal_range(name));
    
    // item not found
    if (p.first == m_xmlData->m_children.end())
#if (XMLNODE_THROW_NOTFOUND)
        throw InvalidChild("Invalid child");
#else
        return XMLNode();
#endif
    
    if (n == 0)
        return (p.first)->second;
    
    // both: at most O(count(n))
    while( (n > 0) && (p.first != p.second) ) {
        p.first++;
        if (--n == 0)
            return (p.first)->second;
    }
#if (XMLNODE_THROW_NOTFOUND)
        throw InvalidChild("Invalid child");
#else
        return XMLNode();
#endif
}

XMLNode& XMLNode::setProperty(const string &name, const string &value)
{
    m_xmlData->m_properties[name] = value;
    return *this;
}

XMLNode& XMLNode::setProperty(const string &name, int value)
{
    stringstream foo;
    foo << value;
    return setProperty(name, foo.str());
}

XMLNode& XMLNode::addChild(const string &name, const string &data)
{
    XMLNode tmp(name, data);
    
    // multimap: Average complexity for insert element is at most logarithmic.
    // hash_mmap: 
    return ((m_xmlData->m_children.insert(NodeMap::value_type(name, tmp)))->second);
}

 /// Add a child node to the tree.
XMLNode &XMLNode::addChild(XMLNode& node) 
{ 
    // ARG This is wrong according to the SGI docs, DAMNIT
    // it should return a pair<X::iterator, bool> FUCK
    return ((m_xmlData->m_children.insert(NodeMap::value_type(node.name(), node)))->second);
}

XMLNode& XMLNode::delChild(const string &name, unsigned int n)
{
    pair<NodeMap::iterator, NodeMap::iterator> p(m_xmlData->m_children.equal_range(name));
    
    // item not found
    if (p.first == m_xmlData->m_children.end())
#if (XMLNODE_THROW_NOTFOUND)
        throw InvalidChild("Invalid child");
#else
        return *this;
#endif
    
    if (n == 0)
    {
        m_xmlData->m_children.erase(p.first);
        return *this;
    }
    
    // both: at most O(count(n))
    while( (n > 0) && (p.first != p.second) ) {
        p.first++;
        if (--n == 0)
        {
            m_xmlData->m_children.erase(p.first);
            return *this;
        }
    }
    
#if (XMLNODE_THROW_NOTFOUND)
        throw InvalidChild("Invalid child");
#else
        return *this;
#endif  
}

#if 0
XMLNode& XMLNode::moveChild(unsigned int index, unsigned int newIndex)
{

    if ( (index >= m_xmlData->m_children.size()) || (newIndex > m_xmlData->m_children.size()) )
        throw XMLException("Array out of bounds");

    // account for idiots moving to same place
    if (index == newIndex)
        return m_xmlData->m_children[index];

    vector<XMLNode>::iterator it = m_xmlData->m_children.begin();

    // account for index before newIndex
    if (index < newIndex)
        newIndex--;

    while(index-- != 0)
        it++;

    XMLNode tmp(*it);

    m_xmlData->m_children.erase(it);

    it = m_xmlData->m_children.begin();
    
    while (newIndex-- != 0)
        it++;

    return *(m_xmlData->m_children.insert(it, tmp));
    
}
#endif

XMLNode::operator string() const
{
    string str;
    XMLParser::printTag(*this,str);
    return str;
}

AttributeMap& XMLNode::properties() 
{ 
    return m_xmlData->m_properties; 
}

    /*
    * Return all properties (read only)
    */
const AttributeMap& XMLNode::const_properties() const 
{ 
    return m_xmlData->m_properties; 
}

string& XMLNode::operator[](const string &name)
{
    return m_xmlData->m_properties[name];
}

string XMLNode::operator[](const string &name) const
{

    AttributeMap::const_iterator it=m_xmlData->m_properties.find(name);

    if (it==m_xmlData->m_properties.end())
        throw InvalidChild("The specified child does not exist.");
    else
        return it->second;
}

ostream &operator<<(ostream &o, XMLNode &n)
{
    string str;

    XMLParser::printTag(n,str);
    o << str;

    return o;
}

XMLNode &XMLNode::operator<<(const string &str) throw (ParseFailure)
{
	
    try 
    {
        XMLParser p(str);
        *this = p.get_root();
    }
    catch(XMLParser::ParseFailure &e)
    {
        throw ParseFailure(e.what());
    }
    catch(...)
    {
    	LOG_DEBUG("Unexpected exception from parse failure.");
        throw XMLException("Unexpected exception from parse failure.");
    }	
    
    return *this;
}

XMLNode &XMLNode::operator=(const XMLNode &other)
{
    if (!other.m_xmlData)
        return *this;

    if (other.m_xmlData == m_xmlData)
        return *this;
    
    /// checks to see if both the current and other object
    /// are valid. 
    if (other.m_xmlData)
    	other.m_xmlData->ref();
    	       
    if (m_xmlData && m_xmlData->deref())
    {
        delete m_xmlData;
        m_xmlData=0;
    }
    
    m_xmlData=other.m_xmlData;
    return *this;
}
