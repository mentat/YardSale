/*
    YardSale - The Open Point of Sale
    Copyright (C) 2004 - Jesse Lovelace <jllovela@ncsu.edu>
 
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
#ifndef YS_TEST_H
#define YS_TEST_H

#include <iostream>
#include "ys_exception.h"
#include <cmath>

using namespace std;

int failure = 0;
int success = 0;

// close with tolerance TOLERANCE
#define TOLERANCE 0.0000001
#define VERIFY_FLOAT(a, b) { \
     if ( (abs(a - b) <= TOLERANCE ) ) \
     { cout << "Passed..." << endl; success++; } \
     else \
     { cout << "Failed at " << __FILE__ << ":" << __LINE__ << endl; failure++; } \
}
     
#define VERIFY(a,b) { \
    if ((a)==(b)) \
        { cout << "Passed..." << endl; success++; } \
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
