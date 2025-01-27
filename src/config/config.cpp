#include <any>
#include <fstream>
#include <sstream>
#include <typeindex>
#include <utility>

#include "config.hpp"

Config::Opts& Config::SetOpts(const std::map<std::string, std::string> settings, Config::Opts& opts)
{
    // typeid returns ref to std::type_info but we need something that can
    // be constructed for std::pair so we can use std::type_index
    std::map<std::string, std::pair<std::any, std::type_index>> setting_map = {
        {"auto_hide", {&opts.autoHide, std::type_index(typeid(opts.autoHide))}},
        {"read_clock", {&opts.readClock, std::type_index(typeid(opts.readClock))}},
        {"read_clock_file", {&opts.clockFile, std::type_index(typeid(opts.clockFile))}},
        {"read_digit", {&opts.readDigit, std::type_index(typeid(opts.readDigit))}},
        {"read_digit_file", {&opts.digitFile, std::type_index(typeid(opts.digitFile))}},
        {"clock_color", {&opts.clockColor, std::type_index(typeid(opts.clockColor))}},
        {"digits_color", {&opts.digitsColor, std::type_index(typeid(opts.digitsColor))}}
    };

    for (const auto& [setting, value] : settings)
    {
        if (setting_map.contains(setting))
        {
            auto& [field, type] = setting_map.at(setting);

            if (type == std::type_index(typeid(bool)))
            {
                bool* bField = std::any_cast<bool*>(field);
                *bField = value == "1";
            }
            else if (type == std::type_index(typeid(std::string)))
            {
                std::string* sField = std::any_cast<std::string*>(field);
                *sField = value;
            }
            else if (type == std::type_index(typeid(Tui::ColorPairs)))
            {
                Tui::ColorPairs* cField = std::any_cast<Tui::ColorPairs*>(field);
                *cField = Tui::AsColor(value);
            }
        }
    }

    return opts;
}

Config::Opts& Config::ParseFromFile(Config::Opts& opts, const std::set<std::string>& whichOpts)
{
    std::map<std::string, std::string> settings;

    std::ifstream inFile("clock.conf");
    if(inFile.is_open())
    {
        std::string line;
        while(std::getline(inFile, line))
        {
            std::stringstream lineStream(line);
            std::string setting;
            lineStream >> setting;
            std::string value;
            lineStream >> value;

            if (whichOpts.empty() || whichOpts.contains(setting))
            {
                settings[setting] = value;
            }
        }
    }

    return SetOpts(settings, opts);
}

Config::Opts Config::GetOpts(const std::vector<std::string>& args)
{
    Opts result;
    result = ParseFromFile(result);
    return result;
}
