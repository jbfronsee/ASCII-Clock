#pragma once

#include <ctime>
#include <vector>
#include <string>

#include "digit.hpp"
#include "../../tui/tui.hpp"

/**
 * @author Joshua Fronsee <jbfronsee@gmail.com>
 *
 * Represents an ASCII Digital Display.
 */
class DigitalDisplay
{
    private:
        static const size_t NUMDIG = 10;
        std::vector<Digit> mDigits;

        std::vector<std::string> mSeparator;
        std::tm* mCurrTime;

        size_t mHeight;
        size_t mWidth;

        Tui::ColorPairs mColor;

        /**
         * Constructs default frame.
         */
        void constructDefault(Tui::ColorPairs color = Tui::ColorPairs::DEFAULT);
        /**
         * Update currTime to hold current time.
         */
        void updateTime();

        /**
         * Prints the hours/min separator.
         */
        void printSeparator();

    public:
        /**
         * Construct frame with file.
         *
         * @param filename of file to read from
         */
        DigitalDisplay(std::string filename = "", Tui::ColorPairs color = Tui::ColorPairs::DEFAULT);

        /**
         * Prints the current time of clock frame.
         */
        void printTime();

        /**
         * Prints digits in order for debugging.
         */
        void printDigits();
};
