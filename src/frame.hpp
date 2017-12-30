#ifndef FRAME_H
#define FRAME_H

#include <ctime>
#include <vector>
#include "digit.hpp"

/**
 * @author Joshua Fronsee <jbfronsee@gmail.com>
 *
 * Represents the frame of a clock that displays
 * the current time using ncurses and ASCII art.
 */
class Clock
{
    private:
        static const size_t NUMDIG = 10;
        std::vector<Digit> digits;
        
        std::vector<char> separator;
        std::tm* currTime;

        size_t height;
        size_t width;
        
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
        Clock();

        /* These three aren't necessary for now. */
        Clock(const Clock& clock);

        ~Clock();

        Clock& operator=(const Clock& clock);

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
