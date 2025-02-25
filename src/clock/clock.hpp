#pragma once

#include <string>

#include "analog/analogDisplay.hpp"
#include "digital/digitalDisplay.hpp"
#include "../tui/tui.hpp"

enum class ClockMode
{
    DIGITAL,
    ANALOG
};

/**
 * Outer frame of clock.
 */
class Clock
{
    private:
        size_t mHeight, mWidth;
        int mStartY, mStartX;
        std::vector<std::string> mFrame;
        Tui::ColorPairs mColor;
        DigitalDisplay mDigital;
        AnalogDisplay mAnalog;
        ClockMode mMode;

        /**
         * Helper function to call default constructor.
         */
        void constructDefault();

    public:
        static const size_t DEFAULT_H = 5;
        static const size_t DEFAULT_W = 19;
        static const std::vector<std::string> DEFAULT;
        static const std::vector<std::string> DEFAULT_ANALOG;
        static const int DEFAULT_YSTART = 1;
        static const int DEFAULT_XSTART = 3;

        /**
         * Read the clock contents from a file.
         * 
         * @param filename - The name of the file to read from.
         */
        Clock(
            const std::string& filename = "",
            Tui::ColorPairs color = Tui::ColorPairs::DEFAULT,
            Tui::ColorPairs dig_color = Tui::ColorPairs::DEFAULT,
            ClockMode mode = ClockMode::DIGITAL
        );

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
        void switchFrame(std::string filename, Tui::ColorPairs color = Tui::ColorPairs::DEFAULT);
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
