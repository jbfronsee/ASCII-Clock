#include <chrono>

#include "time.hpp"

tm Time::GetLocalTime()
{
    std::chrono::time_point now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    return *std::localtime(&t);
}

int Time::ToStandardHour(int hour)
{
    if(hour > 12)
    {
        hour = hour - 12;
    }
    else if(hour == 0)
    {
        hour = 12;
    }

    return hour;
}
