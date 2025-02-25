#ifndef CONFIG_H
#define CONFIG_H

#include <algorithm>
#include <map>
#include <optional>
#include <set>

#include "../clock/clock.hpp"
#include "../tui/tui.hpp"

namespace Config
{
    struct Opts
    {
        Opts()
        : autoHide(false),
          clockColor(Tui::ColorPairs::DEFAULT),
          digitsColor(Tui::ColorPairs::DEFAULT),
          mode(ClockMode::DIGITAL),
          readClock(false),
          readDigit(false) {}

        bool autoHide;

        Tui::ColorPairs clockColor;

        std::string clockFile;

        Tui::ColorPairs digitsColor;

        std::string digitFile;

        ClockMode mode;

        bool readClock;
        bool readDigit;
    };

    Opts& SetOpts(const std::map<std::string, std::string> settings, Opts& opts);

    Opts& ParseFromFile(Opts& opts, const std::set<std::string>& whichOpts = std::set<std::string>());

    Opts GetOpts(const std::vector<std::string>& args);

    template<typename T>
    std::optional<T> AsEnum(const std::string& value, const std::map<std::string, T>& mapping)
    {
      std::string asUpper;
      std::transform(value.cbegin(), value.cend(), back_inserter(asUpper),
          [] (const char c) { return std::toupper(c); }
      );

      if (mapping.contains(asUpper))
          return std::optional(mapping.at(asUpper));
      else
          return std::optional<T>();
    }
}

#endif /* CONFIG_H */
