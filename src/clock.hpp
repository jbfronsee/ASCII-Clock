#ifndef CLOCK_H
#define CLOCK_H

#include <ncurses.h>
#include <string>
#include "frame.hpp"

/**
 * Outer frame of clock.
 */
class Clock
{
    private:
        size_t height, width,
               starty, startx;
        char** outer;
        Frame inner;

        /**
         * Helper function to call default constructor.
         */
        void constructDefault();
    
    public:
        static const size_t DEFAULT_H = 5;
        static const size_t DEFAULT_W = 19;
        static const char DEFAULT[DEFAULT_H][DEFAULT_W + 1];
        static const size_t DEFAULT_YSTART = 1;
        static const size_t DEFAULT_XSTART = 3;

        /**
         * Constructor uses default frame.
         */
        Clock();

        /**
         * Read the clock contents from a file.
         * 
         * @param filename - The name of the file to read from.
         */
        Clock(std::string& filename);

        /**
         * Copy constructor.
         */
        Clock(const Clock& clock);

        /**
         * Destructor.
         */
        ~Clock();

        /**
         * Copy assignment.
         */
        Clock& operator=(const Clock& clock);

        /**
         * Displays the clock on screen with
         * ncurses.
         */
        void displayClock();
};

#endif /* CLOCK_H */
