/*
    $Id: xmlnode.h,v 1.3 2004/04/26 01:20:53 thementat Exp $
 
    XMLNode - A XML DOM tree
    
    Original Copyright (C) 2001-2002  Henrik Abelsson <henrik@abelsson.com>
    Copyright(C) 2003-2004 Jesse Lovelace <jllovela@ncsu.edu>
 
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
#ifndef XMLNODE_H
#define XMLNODE_H

#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <locale>
#include <map>

using namespace std;

class XMLNode;
#ifdef XMLNODE_USE_HASHMAP
// Pulling in hash map
  #ifdef __GNUC__ // Fuck me this is the ugliest thing
    #include <ext/hash_map>
    namespace __gnu_cxx
    {
      using namespace std;
     
      template<>
        struct hash<string>
        {
          size_t operator()(const string& s) const
          {
            const collate<char>& c = use_facet<collate<char> >(locale::classic());
            return c.hash(s.c_str(), s.c_str() + s.size());
          }
        };
    }
    using namespace __gnu_cxx;
  #else      // ...  there are other compilers, right?
   #include <ext/hash_map> // MSOFT
 #endif
typedef hash_multimap<string, XMLNode> NodeMap;
typedef hash_map<string, string> AttributeMap;
#else // else use regular map
typedef multimap<string, XMLNode> NodeMap;
typedef map<string, string> AttributeMap;    
#endif
    
// Allow users to derive a new exception base,
//  this could be implemented as a template policy...
#ifndef XMLNODE_EXCEPTION_BASE
#include <exception>   
#define XMLNODE_EXCEPTION_BASE std::exception
#endif
    
#define XMLNODE_DOUBLE_PRECISION    3
#define XMLNODE_DOUBLE_MAX_MANTISSA numeric_limits<double>::digits10
#define XMLNODE_THROW_NOTFOUND      0

// Master exception class for all XML    
class XMLException: public XMLNODE_EXCEPTION_BASE {
 public:
        
    explicit XMLException(const string& err):m_what(err) {}
 
    virtual ~XMLException() throw() {}
    const char *what() const throw() {return (m_what.c_str());}    
    void SetWhat(const string &s) { m_what = s; } 
    const string& GetWhat() const { return m_what; }
    
 private:
    string m_what;
 };

/**
  * @defgroup xml XML
  * Classes using XML as the internal structure
  */
    
/** @ingroup xml
 * An XML Tag represented as a single class.
 *
 * This is a parsed xml tag. It stores all properties and all nested nodes and
 * the text between the start tag. It can be used as a combined tree, array and
 * associative map data structure without any artificial size limits.
 *
 * Terminology:
 * <ul>
 *   <li> tag - everything betweem <name> and </name> including the tag name and properties
 *   <li> node - same as tag
 *   <li> property - A value stored in the tag start <tag property="value">
 *   <li> child nodes - nested nodes <tag> <child> </child> </tag>
 *   <li> data - Text between start and end tag
 * </ul>
 * Example:
 * <pre>
 * <tag property1="value" property2="a value">
 * .. some text here ..
 * </tag>
 * </pre>
 *
 * @author Henrik Abelsson
 * @author Jesse Lovelace
 */
class XMLNode
{
public:

    /**
     *  An attempt to access an invalid child was made
     */
    class InvalidChild: public XMLException
    {
    public:
        InvalidChild(const string& error): XMLException(error) {}
    };

    /** 
     * The data could not be parsed as XML
     */
    class ParseFailure: public XMLException
    {
    public:
        ParseFailure(const string& error): XMLException(error) {}
    };
    
    // Cannot convert string to desired type
    class RangeOverflow: public XMLException
    {
    public:
        RangeOverflow(const string& error): XMLException(error) {}
    };

    /// Default constructor, allocates XMLNodeData
    XMLNode();
    
    enum Resource { File, Str };
    
    /**
    * This constructor allows the xmlnode to be read from a 
    *  file or string.
    */
    explicit XMLNode(const string& id, Resource res = Str);
    
    XMLNode(const string& name, const string& data);
    
    /**
     * Constructs the object as a counted reference of the given object
     * @param other The XMLNode to be referenced
     */
    XMLNode(const XMLNode &other);

    virtual ~XMLNode();

    /// a virtual function to return a 'name'
    virtual const string& name() const { return m_xmlData->m_name; }
    
    virtual const string type() const { return "xml"; }

    const string &data() const { return m_xmlData->m_data; }
   
    /* 
    * Return all properties
    */
    AttributeMap& properties();

    /*
    * Return all properties (read only)
    */
    const AttributeMap& const_properties() const;

    /* Return a single property */
    const string property(const string &name) const;

    /* 
    * Return property as an integer if possible, otherwise 0.
    */
    long intProperty(const string &name) const;

    /*
    * True if the node has a child with the specified name
    * @param name name of tag to look for
    * @param n how many tags are required (n=2 means there 
     *   has to be two children with the specified name) 
     */
    bool hasChild(const string &name, int n=1) const;

    /// Return how many children of a specified name there is in the node
    unsigned int numChildren(const string &name) const;

    /// Return all children
   // vector<XMLNode> children();
   template<typename T>
    vector<T> XMLNode::children() 
    { 
        vector<T> ret;
        for (NodeMap::iterator it = m_xmlData->m_children.begin();
                it != m_xmlData->m_children.end(); it++)
           ret.push_back(T(it->second));
        
        return ret;
    }

    /// Return all children (read only)
    vector<XMLNode> const_children() const;
    
    NodeMap& getMap() const { return m_xmlData->m_children; }
    
    /// Return a single child
    /// @param name name of tag to look for
    /// @param n which tag to return if there are more than one
    /// @note If this child does not exist it will be added to the tree
    XMLNode& child(const string &name, unsigned int index=0);
    
    // return all children of name
    //vector<XMLNode> children(const string& name);
    template <typename T>
    vector<T> XMLNode::children(const string& name)
    {
        vector<T> ret;
        pair<NodeMap::iterator, NodeMap::iterator> p(m_xmlData->m_children.equal_range(name));
    
        while (p.first != m_xmlData->m_children.end())
            ret.push_back(T((p.first++)->second));
        
        return ret;   
    }
    
    /**
     * Returns a child XMLNode
     * @param name The name of the XMLNode child
     * @param n The index of the child if more then one child share a name
     * @throw InvalidChild is thrown if the child does not exist
     */
    XMLNode child(const string& name, unsigned int index = 0) const;

    /// Set tag name
    inline XMLNode &setName(const string &name) { m_xmlData->m_name = name; return *this; }

    /// Set data
    inline XMLNode &setData(const string &data) { m_xmlData->m_data = data; return *this; }

    /// Set data as cdata sections
    XMLNode &setCData(const string &data) { m_xmlData->data_is_cdata=true; m_xmlData->m_data = data; return *this; }

    /// Set a property
    XMLNode &setProperty(const string &name, const string &value);
    /// Set a property integer type
    XMLNode &setProperty(const string &name, int value);

    /// Add a child node to the tree.
    XMLNode &addChild( XMLNode &node);

    /// Add a child node to the tree.
    XMLNode &addChild(const string &name, const string &data="");

    /**
     * Delete a child node, throws InvalidNode
     * @param name name of tag to look for
     * @param n which tag to delete if there are more than one
     */
    XMLNode &delChild(const string &name, unsigned int index=0);

    /// moves the child at position index to in front of position newIndex
    XMLNode& moveChild(unsigned int index, unsigned int newIndex);

    /** 
     * Outputs the XMLNode to an std output stream
     * @param o A reference to the output stream
     * @param n A reference to an XMLNode
     */
    friend ostream& operator<<(ostream &o, XMLNode &n);

    /**
     * Parse a string into a XMLNode directly. 
     * @param str The string to parse into an XMLNode
     * @throw ParseFailure if the text could not be parsed into an XMLNode
     */
    XMLNode &operator<<(const string &str) throw(ParseFailure);

    /**
     * Assignment operator
     * @param other The XMLNode object to assign to this object
     * @note This function will be valid regardless if the XMLNode has
     * 		been destroyed
     */
    XMLNode &operator=(const XMLNode &other);

    // Implicitly convert to string.
    operator string() const;

    /// Set and get tag properties using operator[]
    string& operator[](const string &name);

    /** 
     * Returns tag properties using overloaded operator []
     * @param name The name of the property to return
     * @throw InvalidNode if the property does not exist
     */
    string operator[](const string &name) const;

    friend class XMLParser;
        
    /// @throws RangeOverflow If type cannot contain representation
    static long ToLong(const string& str);
    /// @throws RangeOverflow If type cannot contain representation
    static int ToInt(const string& str);
    /// @throws RangeOverflow If type cannot contain representation
    static double ToDouble(const string& str);
        
    static string ToStr(long numeric);
    static string ToStr(double floating, unsigned int precision);
    
protected:

    ///
    /// Reference counted XML data
    /// @author Henrik Abelsson
    class XMLNodeData
    {
    public:
        XMLNodeData()
        { refCount=1; /*cout << (unsigned long)this << " created." << endl;*/ }

        ~XMLNodeData() { /*cout << (unsigned long)this << " deleting." << endl;*/ }
        
        /// Increases the reference count by one, called
        ///  when a new object references this data
        inline void ref() { refCount++; }

        /// Returns true if the data is no longer referenced
        ///  by any object
        inline bool deref() 
        { if (--refCount == 0) return true; return false; }
        
        NodeMap m_children;
        AttributeMap m_properties;
        
        string m_name;
        string m_data;

    private:
        int refCount;

    public:        
        bool data_is_cdata;
        bool oneline;
    };
    
    XMLNodeData *m_xmlData;
};
        
#endif // !GM_XMLNODE_H
