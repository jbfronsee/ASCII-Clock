#ifndef CLOCK_H
#define CLOCK_H

#include <ncurses.h>
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

    public:
        static const size_t FRAME1H = 5;
        static const size_t FRAME1W = 19;
        static const char FRAME1[FRAME1H][FRAME1W + 1];
        static const size_t FRAME1YSTART = 1;
        static const size_t FRAME1XSTART = 3;

        /**
         * Constructor uses default frame.
         */
        Clock();

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
