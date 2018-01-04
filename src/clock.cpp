#include "clock.hpp"
#include <fstream>
#include <sstream>
#include <vector>

const char Clock::DEFAULT[][DEFAULT_W + 1] = {"  _______________  ",
                                              " /               \\ ",
                                              "|                 |",
                                              "|                 |",
                                              " \\_______________/ "};

void Clock::constructDefault()
{
    height = DEFAULT_H;
    width = DEFAULT_W;
    starty = DEFAULT_YSTART;
    startx = DEFAULT_XSTART;

    outer = new char*[height];
    for(size_t i = 0; i < height; i++)
    {
        outer[i] = new char[width + 1];
        for(size_t j = 0; j < width + 1; j++)
        {
            outer[i][j] = DEFAULT[i][j];
        }
    }
}

Clock::Clock()
{
    constructDefault();
}

Clock::Clock(std::string& filename)
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

        outer = new char*[height];
        for(size_t i = 0; i < height; i++)
        {
            outer[i] = new char[width + 1];
            for(size_t j = 0; j < width; j++)
            {
                outer[i][j] = clockframe[i][j];
            }

            outer[i][width] = '\0';
        }
    }
    else
    {
        //TODO: Error message
        constructDefault();
    }
}

Clock::Clock(const Clock& clock)
{
    this->height = clock.height;
    this->width = clock.width;
    this->starty = clock.starty;
    this->startx = clock.startx;

    outer = new char*[height];
    for(size_t i = 0; i < height; i++)
    {
        outer[i] = new char[width + 1];
        for(size_t j = 0; j < width + 1; j++)
        {
            outer[i][j] = clock.outer[i][j];
        }
    }

    this->inner = clock.inner;
}

Clock::~Clock()
{
    for(size_t i = 0; i < height; i++)
    {
        delete[] outer[i];
    }

    delete[] outer;
}

Clock& Clock::operator=(const Clock& clock)
{
    for(size_t i = 0; i < height; i++)
    {
        delete[] outer[i];
    }

    delete[] outer;

    this->height = clock.height;
    this->width = clock.width;
    this->starty = clock.starty;
    this->startx = clock.startx;

    outer = new char*[height];
    for(size_t i = 0; i < height; i++)
    {
        outer[i] = new char[width + 1];
        for(size_t j = 0; j < width + 1; j++)
        {
            outer[i][j] = clock.outer[i][j];
        }
    }

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

   // init_pair(1, COLOR_WHITE, -1);
   // attron(COLOR_PAIR(1));
    int y, x;
    getyx(stdscr, y, x); 
    for(size_t i = 0; i < height; i++)
    {
        mvprintw(y + i, x, outer[i]);
    }

    move(y + starty, x + startx);
    //attroff(COLOR_PAIR(1));
    inner.printTime();
}
