#ifndef OTL_XML_H
#define OTL_XML_H

/*
The idea behind this class is to take a generic OTL stream and
spit out some hot XML.

*/
#include <string>
using namespace std;
class otl_stream;

class otl_xml {
 public:
    otl_xml() {}
    ~otl_xml() {}

    static string process(otl_stream * stream);

};


#endif

