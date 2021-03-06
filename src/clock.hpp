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
        size_t height, width;
        int starty, startx;
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
        static const int DEFAULT_YSTART = 1;
        static const int DEFAULT_XSTART = 3;

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
         * Returns current Y coordinate of frame.
         */
        int getFrameY();

        /**
         * Returns current X coordinate of frame.
         */
        int getFrameX();
        /**
         * Moves the frames left hand corner.
         *
         * @param y - Y-coordinate
         * @param x - X-coordinate
         */
        void moveFrame(int y, int x);

        /**
         * Switches frame to frame specified by filename.
         *
         * @param filename to read frame data from
         */
        void switchFrame(std::string filename);
        /**
         * Writes the clock data to out.cf
         *
         * @return true if successful false otherwise
         */
        bool writeClock();
        
        /**
         * Displays the clock on screen with
         * ncurses.
         */
        void displayClock();
};

#endif /* CLOCK_H */
