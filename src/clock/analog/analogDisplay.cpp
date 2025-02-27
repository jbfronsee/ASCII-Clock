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
        " ^",
        " |",
        " |",
        "/"
    },
    {
        " '`",
        " |",
        " |",
        "/"
    },
    {
        " ^",
        " |",
        " /",
        "/"
    },
    {
        "   ^",
        "  /",
        " /",
        "/"
    },
    // 1
    {
        "   7",
        "  /",
        " /",
        "/"
    },
    {
        "   .7",
        "  '",
        " /",
        "/"
    },
    {
        "   .*",
        "  '",
        " /",
        "/"
    },
    {
        "    _^",
        "   -",
        ".-`"
    },
    {
        "    _.*",
        "   -",
        ".-`"
    },
    // 2
    {
        "    _.7",
        "   -",
        ".-`"
    },
    {
        "    _.*",
        "   -",
        ".-`"
    },
    {
        "    _>",
        "   -",
        ".-`"
    },
    {
        "   ---*",
        ".-`"
    },
    {
        "      .",
        ".--```"
    },
    // 3
    {
        "------>"
    },
    {
        "---...",
        "      ``",
    },
    {
        "---...",
        "      `>",
    },
    {
        "._",
        "  `\\..",
        "       `"
    },
    {
        "._",
        "  `\\.",
        "      `"
    },
    // 4
    {
        "._",
        "  `\\",
        "    `'>"
    },
    {
        "._",
        "  `\\",
        "    `'."
    },
    {
        "._",
        "  `\\",
        "    `.."
    },
    {
        "\\",
        " \\",
        "  `'.>"
    },
    {
        "\\",
        " \\",
        "  `'.",
        "     v"
    },
    // 5
    {
        "\\",
        " \\",
        "  \\",
        "   v"
    },
    {
        "\\",
        " \\",
        "  \\",
        "  v"
    },
    {
        "\\",
        " \\",
        "  |",
        "  v"
    },
    {
        "\\",
        " |",
        " |",
        " `."
    },
    {
        "\\",
        " |",
        " |",
        " v"
    },
    // 6
    {
        "|",
        "|",
        "|",
        "v"
    },
    {
        " /",
        "|",
        "|",
        "v"
    },
    {
        "  /",
        " |",
        " |",
        ".'"
    },
    {
        "   /",
        "  /",
        " |",
        " v"
    },
    {
        "   /",
        "  /",
        " /",
        " v"
    },
    // 7
    {
        "   /",
        "  /",
        " /",
        "v"
    },
    {
        "    /",
        "   /",
        "  -",
        ".'"
    },
    {
        "     /",
        "    /",
        "  --",
        "<'"
    },
    {
        "   .-`",
        "  /",
        ".`"
    },
    {
        "   .-`",
        "  /",
        "*`"
    },
    // 8
    {
        "   .-`",
        "  /",
        "<`"
    },
    {
        "    .-`",
        "   /",
        "<``"
    },
    {
        "    .-`",
        "  --",
        "<`"
    },
    {
        "  ...---",
        "<`",
    },
    {
        "  ...---",
        "``",
    },
    // 9
    {
        "<------"
    },
    {
        ".",
        " ```--."
    },
    {
        "*---",
        "    `-."
    },
    {
        "<_",
        "  -",
        "   `-."
    },
    {
        "*._",
        "   -",
        "    `-."
    },
    // 10
    {
        "_",
        "`_",
        "  -",
        "   `-."
    },
    {
        "`._",
        "   -",
        "    `-."
    },
    {
        "^_",
        "  -",
        "   `-."
    },
    {
        "*.",
        "  `",
        "   \\",
        "    \\"
    },
    {
        "_",
        "`.",
        "  `",
        "   \\",
        "    \\"
    },
    // 11
    {
        "_",
        "`",
        " \\",
        "  \\",
        "   \\"
    },
    {
        "^",
        " \\",
        "  \\",
        "   \\"
    },
    {
        "^",
        "|",
        " \\",
        "  \\"
    },
    {
        "`'",
        " |",
        " |",
        "  \\"
    },
    {
        "^",
        "|",
        "|",
        " \\"
    },
    // 12
    {
        "^",
        "|",
        "|",
        "|"
    }
};
/*
const std::vector<std::pair<int, int>> AnalogDisplay::MINUTE_HAND_ADJUSTMENTS = {
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {0, 0},
    {-1, 0},
    {-1, 0},
    {-1, 0}
};*/

std::pair<int, int> AnalogDisplay::GetHandAdjust(const std::vector<std::string>& hand, int value, const bool hour)
{
    int left = 9, right = 3, down = 6, up = 12;
    if (hour == false)
    {
        left = 45;
        right = 15;
        down = 30;
        up = 60;
        if (value == 0)
            value = up;
        // //TODO temp solution
        // if (value > 45 && value < 50)
        // {
        //     value = 45;
        // }
        // if (value > 15 && value < 20)
        // {
        //     value = 15;
        // }
        // if (value > 30 && value < 35)
        // {
        //     value = 30;
        // }
        // if (value > 0 && value < 5)
        // {
        //     value = up;
        // }
    }

    int xAdjust = 0;
    int yAdjust = 0;

    if (value > down && value < up)
    {
        xAdjust = -std::ranges::max(std::views::transform(hand, &std::string::size)) - 1;
    }
    else if (value < down)
    {
        xAdjust += 1;
    }

    if (value > left || value < right)
    {
        yAdjust = -hand.size();
    }
    else if (value != left && value != right)
    {
        yAdjust += 1;
    }

    return std::pair<int, int>(xAdjust, yAdjust);
}

AnalogDisplay::AnalogDisplay(std::string filename, Tui::ColorPairs color, Tui::ColorPairs secondColor)
    : mColor(color), mSecondColor(secondColor)
{

}

void AnalogDisplay::printHand(const Hand hand)
{
    int value = 0;
    const std::vector<std::string>* hand_vec = nullptr;
    bool is_hour = false;
    Tui::ColorPairs color = mSecondColor;
    if (hand == Hand::HOUR)
    {
        value = Time::ToStandardHour(mCurrTime.tm_hour);
        hand_vec = &HOUR_HANDS[value - 1];
        is_hour = true;
        color = mColor;
    }
    else
    {
        value = mCurrTime.tm_sec;
        if (hand == Hand::MINUTE)
        {
            value = mCurrTime.tm_min;
            color = mColor;
        }

        int index = value - 1;
        if (index == -1)
            index = 59;

        hand_vec = &MINUTE_HANDS[index];
    }

    const auto [x, y] = Tui::GetXY();
    auto [xAdjustHour, yAdjustHour] = GetHandAdjust(*hand_vec, value, is_hour);

    Tui::Move(x + xAdjustHour, y + yAdjustHour);
    Tui::DisplayMessages(*hand_vec, x - xAdjustHour, y - yAdjustHour, color);
    Tui::Move(x, y);

}

void AnalogDisplay::printTime()
{
    // TODO check for off by one type adjustments
    mCurrTime = Time::GetLocalTime();

    printHand(Hand::HOUR);
    printHand(Hand::MINUTE);
    printHand(Hand::SECOND);
}
