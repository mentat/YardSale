#ifndef GM_XML_H
#define GM_XML_H

#include <string>
#include <map>
#include <vector>
#include <stack>

#include "wrapexpat.h"

using namespace std;

/**
 * An XML Parser
 *
 * This class a string and parsers it to build a XML tree.
 *
 * Usually you dont need to use this class directly, you can parse strings
 * and convert XMLNodes to string directly with the XMLNode class.
 *
 * @author Henrik Abelsson
 * @version 0.1
 */
class XMLParser: public Expat
{
    
public:

    /// The XML parser could not parse the string
    class ParseFailure: public XMLException
    {
    public:
        ParseFailure(const string& msg): XMLException(msg) {}
    };

    /// There was an error reading/writing from disk
    class DiskError: public XMLException
    {
    public:
        DiskError(const string& msg): XMLException(msg) {}
    };

    /// The type of input
    enum Type { File, String };

    /**
    * Construct a new parser, may throw ParseFailure or DiskError 
    *
    * @param data Data to read, either a ready string or a filename
    * @param type Specifies w XMLParser::String - read from an in memory string, or XMLParser::File, a file.
    */
    XMLParser(const string &data="",Type type=XMLParser::String);

    /**
    * Set a XMLNode as root
    */
    XMLParser(XMLNode &root);

    ~XMLParser();

    /**
    * Write the XML Tree to  to line.
    *
    * @param line Otherwise store the tree in this string.
    */
    int tree_to_xml(string &line);

    /// may throw DiskError
    int tree_to_file(const string &filename);
   
    /**
    * Get all tags in the tree whose name are key.
    *
    *
    * @param key What tags to return
    * @return all the tags that match key
    * @see tree_to_xml()
    */
    vector<XMLNode> get_tags(const string &key);

    /**
    Return the root tag.
    */
    XMLNode &get_root() { return root;}

    int lock(const string &fname);
    int release(const string &fname);
    int bad() { return status;}
    int good() { return status == 0;}

    static int printTag(const XMLNode &node, string &ret,int indent=0);
    int getParsed() const { return 0; }

    static string escape(string str);


protected:
    
    virtual void recievedTag(XMLNode &n);
    virtual void rootTagRecieved(XMLNode &n);
    virtual void parserError(const string& errorMsg, int line);

private:

    void init(const string &line, Type type);

    XMLNode root;
    int status;
};

#endif // !GM_XML_H
