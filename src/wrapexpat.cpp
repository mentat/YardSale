#include <iostream>
#include <sstream>

#include "wrapexpat.h"
#include "expat.h"

#ifndef LOG_DEBUG
#ifdef DEBUG
 #ifdef WIN32
  #include <fstream>
  static ofstream debugOut("wrapexpat_debug.txt");
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

// trim_right() family.
string Expat::trim_right ( const string & source, const string & t)
{
    string str = source;
    return str.erase ( str.find_last_not_of ( t ) + 1 ) ;
}

// trim_left() family.
string Expat::trim_left ( const string & source, const string & t)
{
    string str = source;
    return str.erase ( 0 , source.find_first_not_of ( t ) ) ;
}

// trim() family.
string Expat::trim ( const string & source, const string & t)
{
    string str = source;
    return trim_left ( trim_right ( str , t ) , t ) ;
}
 
Expat::Expat()
{
    parser = 0;
    init();
}

Expat::~Expat()
{
    cleanup();
}

void Expat::init()
{
    if (parser != 0)
        cleanup();

    parser = XML_ParserCreate( NULL );
    XML_SetElementHandler(parser, startElement, endElement);
    XML_SetCharacterDataHandler(parser, charData);
    XML_SetUserData(parser, (void *)this);

    rootRecieved = false;
}

void Expat::cleanup()
{
    if (parser == 0)
        return;

    XML_ParserFree( parser );
    parser = 0;

    newNodes.clear();
    while (!fillingNodes.empty())
        fillingNodes.pop();
}

void Expat::reset()
{
    cleanup();
    init();
}

void Expat::parse(string data)
{
    if (!parser)
    {
        parserError("Expat::parse: Internal error",0);
        return;
    }

    if (!XML_Parse( parser, (const char *)data.c_str(), (long int)data.length(), false ))
    {
        parserError( XML_ErrorString(XML_GetErrorCode(parser)), XML_GetCurrentLineNumber(parser));
        return;
    }

    // Send out any new tags
    for (unsigned int i=0;i<newNodes.size();i++)
        recievedTag(newNodes[i]);

    newNodes.clear();
}

void Expat::recievedTag( XMLNode &n)
{
    LOG_DEBUG(string(n).c_str());
}

void Expat::rootTagRecieved(XMLNode &n)
{
    string s("Recieved root tag:");
    s += string(n);
    LOG_DEBUG(s.c_str());
}

void Expat::rootTagEnded()
{
	LOG_DEBUG("Root tag ended.");
}

void Expat::parserError(string errorMsg, int line )
{
    stringstream err;
    err << "Expat parser error: " << errorMsg << " at "<< line;
    
    // try to keep object in sane state after throw
    reset();
    throw ParseFailure(err.str().c_str());
}

void Expat::startElement(void *userData, const XML_Char *name, const XML_Char **atts)
{
    /* get the userdata into a usable form */
    Expat *me = (Expat *)userData;

    /* New tag? Well...create one */
    XMLNode t;

    t.setName(name);
    /* now put on it's parameters */
    int i=0;

    if (atts != NULL)
    {
        while (atts[i] != NULL)
        {
            t.setProperty(atts[i],atts[i+1]);
            i+=2;
        }
    }


    if( !me->rootRecieved )
    {
        // This is the first tag...therefore the root tag.
        me->rootTagRecieved(t);
        me->rootRecieved = true;
        return;
    }

    /* Register it as a sub tag of the previous tag */
    if (!me->fillingNodes.empty())
        me->fillingNodes.top().addChild(t);

	/* push this node onto the stack */
    me->fillingNodes.push( t );
}

void Expat::endElement(void *userData, const XML_Char *)
{
    /* get the userdata into a usable form */
    Expat *me = (Expat *)userData;

    if (me->fillingNodes.empty())
    {
        // If this is 0 then this is the end of the root tag...
        me->rootTagEnded();
        return;
    }

    if (me->fillingNodes.size() == 1)
    {
        // We used to send them right out from here...but I found out something very nasty can
        // happen...suppose that the parser is deleted because of this node (login error...)
        me->newNodes.push_back(me->fillingNodes.top());

        // We do not delete the node becuse that job belongs to
        // whoever overrid the revieced tag
    }

    me->fillingNodes.top().setData(trim(me->fillingNodes.top().data(),"\n\r\t "));

    me->fillingNodes.pop();
}

void Expat::charData(void *userData, const char *s, int length)
{
    /* get the userdata into a usable form */
    Expat *me = (Expat *)userData;

    char *data;
    data = new char[length + 1];
    memcpy(data, s, length);
    data[length] = '\0';

    if (me->fillingNodes.empty())
    {
        delete [] data;
        return;
    }
    string newData = me->fillingNodes.top().data()+data;

    me->fillingNodes.top().setData(newData);

    delete[] data;
}
