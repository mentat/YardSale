#ifndef YS_TEST_H
#define YS_TEST_H

#include <iostream>
#include "ys_exception.h"

using namespace std;

int failure;
int success;

#define VERIFY(a,b) { \
    if ((a)==(b)) \
        { cout << "Passed.." << endl; success++; } \
    else \
        { cout << "Failed at " << __FILE__ << ":" << __LINE__ << endl; failure++; } \
}


#define VERIFY_THROW(a) { bool didThrow = false; \
    try { a; } \
    catch(YardException &e) \
        { \
            didThrow = true; \
            cout << e.what() << endl; \
        } \
        if (didThrow)   \
        { cout << "Passed.." << endl; success++; } \
    else \
        { cout << "Failed at " << __FILE__ << ":" << __LINE__ << endl; failure++; } \
}

#define VERIFY_NO_THROW(a) { bool didThrow = false; \
    try { a; } \
    catch(YardException &e) \
        { \
            didThrow = true; \
            cout << e.what() << endl; \
        } \
        if (!didThrow)   \
        { cout << "Passed.." << endl; success++; } \
    else \
        { cout << "Failed at " << __FILE__ << ":" << __LINE__ << endl; failure++; } \
}



#endif
