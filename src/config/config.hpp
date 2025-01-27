#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <set>

#include "../tui/tui.hpp"

namespace Config
{
    struct Opts
    {
        Opts()
        : readClock(false),
          readDigit(false),
          clockColor(Tui::ColorPairs::DEFAULT),
          digitsColor(Tui::ColorPairs::DEFAULT) {}

        bool readClock;
        std::string clockFile;

        bool readDigit;
        std::string digitFile;

        Tui::ColorPairs clockColor;
        Tui::ColorPairs digitsColor;
    };

    Opts& SetOpts(const std::map<std::string, std::string> settings, Opts& opts);

    Opts& ParseFromFile(Opts& opts, const std::set<std::string>& whichOpts = std::set<std::string>());

    Opts GetOpts(const std::vector<std::string>& args);
}

#endif /* CONFIG_H */
