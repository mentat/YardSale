#ifndef SKUNK_BUILD_H
#define SKUNK_BUILD_H

#define YS_CODENAME                     "Zulu"
#define YS_DEFAULT_WEIGHT_PRECISION     5
#define YS_DEFAULT_MONEY_PRECISION      3
#define YS_DEFAULT_TIME_PRECISION       3
#define YS_BULK_DISCOUNT_PRECISION      4
#define YS_TAX_PRECISION                4

#include <string>

double GetVersion();
std::string GetRevision();

#endif
