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
