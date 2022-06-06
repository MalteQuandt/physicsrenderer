#ifndef PHYSICS_RENDERER_UTILITIES_H
#define PHYSICS_RENDERER_UTILITIES_H

#include <iostream>
#include <string>
#include <time.h>

namespace Util
{
    const std::string CurrentDateTime()
    {
        time_t         now = time(NULL);
        struct tm      tstruct;
        char           buf[80];
        localtime_s(&tstruct, &now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
        return buf;
    }
}
#endif //PHYSICS_RENDERER_UTILITIES_H
