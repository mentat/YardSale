#ifndef YS_UTIL_H
#define YS_UTIL_H

#include <sstream>
#include <string>

using namespace std;

inline string strIToA(long int i) {
    stringstream strm;
    strm << i;
    return strm.str();
}

inline string strFToA(float f) {
    stringstream strm;
    strm << f;
    return strm.str();
}

inline string toMoney(float f) {
    stringstream strm;
    strm.precision(2);
    
    strm << showpoint << f;
    return strm.str();
}

#endif
