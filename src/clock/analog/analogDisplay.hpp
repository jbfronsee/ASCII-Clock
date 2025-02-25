#pragma once

#include <ctime>
#include <string>
#include "../../tui/tui.hpp"

/**
 * @author Joshua Fronsee <jbfronsee@gmail.com>
 *
 * Represents an ASCII Analog Display
 */
class AnalogDisplay
{
    private:
        Tui::ColorPairs mColor;
        std::tm mCurrTime;

    public:
        /**
         * Construct frame with file.
         *
         * @param filename of file to read from
         */
        AnalogDisplay(std::string filename = "", Tui::ColorPairs color = Tui::ColorPairs::DEFAULT);

        /**
         * Prints the current time of clock frame.
         */
        void printTime();
};
