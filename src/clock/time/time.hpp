#pragma once

#include <ctime>

namespace Time
{
    std::tm GetLocalTime();

    int ToStandardHour(int hour);
}
