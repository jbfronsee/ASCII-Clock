#include "clock.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

const std::vector<std::string> Clock::DEFAULT = {
    "  _______________  ",
    " /               \\ ",
    "|                 |",
    "|                 |",
    " \\_______________/ "
};

void Clock::constructDefault()
{
    mHeight = DEFAULT_H;
    mWidth = DEFAULT_W;
    mStartY = DEFAULT_YSTART;
    mStartX = DEFAULT_XSTART;
    mOuter = DEFAULT;
}

Clock::Clock(const std::string& filename, Tui::ColorPairs color, Tui::ColorPairs dig_color)
    : mColor(color), mInner("", dig_color)
{
    if (filename.empty())
    {
        constructDefault();
        return;
    }

    std::ifstream inFile(filename);
    if(inFile.is_open())
    {
        std::string header;
        std::getline(inFile, header);
        std::stringstream headStream(header);
        if(!(headStream >> mStartY))
        {
            //TODO: Error Message
            constructDefault();
            return;
        }

        if(!(headStream >> mStartX))
        {
            //TODO: Error Message
            constructDefault();
            return;
        }

        std::vector<std::string> clockframe;
        std::string line;
        std::getline(inFile, line);
        mWidth = line.size();
        clockframe.push_back(line);

        while(std::getline(inFile, line))
        {
            if(line.size() != mWidth)
            {
                //TODO: Error message
                constructDefault();
                return;
            }
            else
            {
                clockframe.push_back(line);
            }
        }

        mHeight = clockframe.size();

        mOuter = clockframe;
    }
    else
    {
        //TODO: Error message
        constructDefault();
    }
}

int Clock::getFrameY()
{
    return mStartY;
}

int Clock::getFrameX()
{
    return mStartX;
}

void Clock::moveFrame(int y, int x)
{
    mStartY = y;
    mStartX = x;
}

void Clock::switchFrame(std::string filename, Tui::ColorPairs color)
{
    mInner = Frame(filename, color);
}
bool Clock::writeClock()
{
    bool success = false;

    std::ofstream outFile("out.cf");
    if(outFile.is_open())
    {
        outFile << mStartY << " " << mStartX << std::endl;
        for(size_t i = 0; i < mHeight; i++)
        {
            outFile << mOuter[i] << std::endl;
        }

        success = true;
    }

    return success;
}

void Clock::displayClock()
{
    Tui::Clear();
    // Center the clock in the terminal
    Tui::Move((Tui::Cols() - mWidth)/2, (Tui::Lines() - mHeight)/2);
    Tui::DisplayMessages(mOuter, mStartX, mStartY, mColor);
    mInner.printTime();
}
