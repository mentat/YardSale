#include "ys_build.h"
#include "ys_build_id.h"

#define YS_VER_MAJOR  0.0
#define YS_VER_MINOR  BUILD_ID
#define YS_VER        YS_VER_MAJOR + BUILD_ID


double GetVersion()
{
    return YS_VER;

}
