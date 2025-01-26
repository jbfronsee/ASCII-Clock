#ifndef FRAME_H
#define FRAME_H

#include <ctime>
#include <vector>
#include <string>
#include "digit.hpp"

/**
 * @author Joshua Fronsee <jbfronsee@gmail.com>
 *
 * Represents the frame of a clock that displays
 * the current time using ncurses and ASCII art.
 */
class Frame
{
    private:
        static const size_t NUMDIG = 10;
        std::vector<Digit> mDigits;

        std::vector<std::string> mSeparator;
        std::tm* mCurrTime;

        size_t mHeight;
        size_t mWidth;

        /**
         * Constructs default frame.
         */
        void constructDefault();
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
         * Default constructor creates a
         * frame with 10 ASCII digits from
         * 0 - 9.
         */
        Frame();

        /**
         * Construct frame with file.
         *
         * @param filename of file to read from
         */
        Frame(std::string filename);

        /**
         * Prints the current time of clock frame.
         */
        void printTime();

        /**
         * Prints digits in order for debugging.
         */
        void printDigits();
};

#endif /* FRAME_H */
