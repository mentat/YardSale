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
#ifndef SKUNK_BUILD_H
#define SKUNK_BUILD_H

#define YS_CODENAME                     "Zulu"
#define YS_DEFAULT_WEIGHT_PRECISION     5
#define YS_DEFAULT_MONEY_PRECISION      3
#define YS_DEFAULT_TIME_PRECISION       3
#define YS_BULK_DISCOUNT_PRECISION      4
#define YS_TAX_PRECISION                4

#ifndef YS_OS
 #ifdef WIN32
  #define YS_OS "Win32"
 #else
  #define YS_OS "Unknown OS"
 #endif
#endif

#ifndef YS_DEBUG_BUILD
 #ifdef __WXDEBUG__
  #define YS_BUILD_MODE "debug"
 #else
  #define YS_BUILD_MODE "release"
 #endif
#else
 #define YS_BUILD_MODE "debug"
#endif


#include <string>

double GetVersion();
std::string GetRevision();

#endif
