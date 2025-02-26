#include "analogDisplay.hpp"

#include <algorithm>
#include <ranges>

#include "../time/time.hpp"

const std::vector<std::vector<std::string>> AnalogDisplay::HOUR_HANDS = {
    {
        "  7",
        " /",
        "/"
    },
    {
        "   7",
        ".;'"
    },
    {
        "---->"
    },
    {
        "._",
        "  `'>"
    },
    {
        "\\",
        " \\",
        "  v"
    },
    {
        "|",
        "|",
        "v"
    },
    {
        "  /",
        " /",
        "v"
    },
    {
        "  ,-`",
        "<`"
    },
    {
        "<----"
    },
    {
        "_",
        "`'':."
    },
    {
        "_",
        "`",
        " \\",
        "  \\"
    },
    {
        "^",
        "|",
        "|"
    }
};

const std::vector<std::vector<std::string>> AnalogDisplay::MINUTE_HANDS = {
    {
        "   7",
        "  /"
        " /",
        "/"
    },
    {
        "     7"
        "   ,'",
        ".;'"
    },
    {
        "------>"
    },
    {
        "._",
        "  `'."
        "     '>"
    },
    {
        "\\",
        " \\",
        "  \\",
        "   v"
    },
    {
        "|",
        "|",
        "|",
        "v"
    },
    {
        "   /",
        "  /",
        " /",
        "v"
    },
    {
        "   ,-`",
        " .'`",
        "<"
    },
    {
        "<------"
    },
    {
        "_",
        "`'':.",
        "     `*"
    },
    {
        "_",
        "`",
        " \\",
        "  \\",
        "   \\"
    },
    {
        "^",
        "|",
        "|",
        "|"
    }
};

std::pair<int, int> AnalogDisplay::GetHandAdjust(const std::vector<std::string>& hand, const int value, const bool hour)
{
    int left = 9, right = 3, down = 6;
    if (hour == false)
    {
        left = 45;
        right = 15;
        down = 30;
    }

    int xAdjust = 0;
    int yAdjust = 0;

    if (value > down)
    {
        xAdjust = -std::ranges::max(std::views::transform(hand, &std::string::size));
    }

    if (value > left || value < right)
    {
        yAdjust = -hand.size();
    }

    return std::pair<int, int>(xAdjust, yAdjust);
}

AnalogDisplay::AnalogDisplay(std::string filename, Tui::ColorPairs color)
    : mColor(color)
{

}

void AnalogDisplay::printTime()
{
    // TODO check for off by one type adjustments
    mCurrTime = Time::GetLocalTime();

    const int hour = Time::ToStandardHour(mCurrTime.tm_hour);

    const std::vector<std::string>& hour_hand = HOUR_HANDS[hour - 1];

    const auto [x, y] = Tui::GetXY();
    const auto [xAdjustHour, yAdjustHour] = GetHandAdjust(hour_hand, hour);

    Tui::Move(x + xAdjustHour, y + yAdjustHour);
    Tui::DisplayMessages(hour_hand, x - xAdjustHour, y - yAdjustHour, mColor);

    // TODO make a function to handle all 3 kinds of hands

    const std::vector<std::string>& minute_hand = MINUTE_HANDS[(mCurrTime.tm_min / 5) - 1];

    const auto [xAdjustMin, yAdjustMin] = GetHandAdjust(minute_hand, mCurrTime.tm_min, false);

    Tui::Move(x + xAdjustMin, y + yAdjustMin + 1);
    Tui::DisplayMessages(minute_hand, x - xAdjustMin, y - yAdjustMin, mColor);
}
