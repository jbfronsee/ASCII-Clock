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
    height = DEFAULT_H;
    width = DEFAULT_W;
    starty = DEFAULT_YSTART;
    startx = DEFAULT_XSTART;

    outer = DEFAULT;
}

Clock::Clock(Tui& tui)
: m_tui(tui)
{
    constructDefault();
}

Clock::Clock(std::string& filename, Tui& tui)
: m_tui(tui)
{
    std::ifstream inFile(filename);
    if(inFile.is_open())
    {
        std::string header;
        std::getline(inFile, header);
        std::stringstream headStream(header);
        if(!(headStream >> starty))
        {
            //TODO: Error Message
            constructDefault();
            return;
        }

        if(!(headStream >> startx))
        {
            //TODO: Error Message
            constructDefault();
            return;
        }

        std::vector<std::string> clockframe;
        std::string line;
        std::getline(inFile, line);
        width = line.size();
        clockframe.push_back(line);

        while(std::getline(inFile, line))
        {
            if(line.size() != width)
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

        height = clockframe.size();

        outer = clockframe;
    }
    else
    {
        //TODO: Error message
        constructDefault();
    }
}

Clock::Clock(const Clock& clock)
: m_tui(clock.m_tui)
{
    this->height = clock.height;
    this->width = clock.width;
    this->starty = clock.starty;
    this->startx = clock.startx;

    outer = clock.outer;

    this->inner = clock.inner;
}

Clock::~Clock()
{
}

Clock& Clock::operator=(const Clock& clock)
{
    this->height = clock.height;
    this->width = clock.width;
    this->starty = clock.starty;
    this->startx = clock.startx;

    outer = clock.outer;

    this->inner = clock.inner;

    return *this;
}

int Clock::getFrameY()
{
    return starty;
}

int Clock::getFrameX()
{
    return startx;
}

void Clock::moveFrame(int y, int x)
{
    starty = y;
    startx = x;
}

void Clock::switchFrame(std::string filename)
{
    inner = Frame(filename);
}
bool Clock::writeClock()
{
    bool success = false;

    std::ofstream outFile("out.cf");
    if(outFile.is_open())
    {
        outFile << starty << " " << startx << std::endl;
        for(size_t i = 0; i < height; i++)
        {
            outFile << outer[i] << std::endl;
        }

        success = true;
    }

    return success;
}

void Clock::displayClock()
{
    move((LINES - height)/2, (COLS - width)/2);
    m_tui.DisplayMessagesAndMove(outer, startx, starty);
    inner.printTime();
}
