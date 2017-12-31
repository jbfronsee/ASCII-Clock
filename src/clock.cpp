#include "clock.hpp"

const char Clock::FRAME1[][FRAME1W + 1] = {"  _______________  ",
                                           " /               \\ ",
                                           "|                 |",
                                           "|                 |",
                                           " \\_______________/ "};

Clock::Clock()
{
    height = FRAME1H;
    width = FRAME1W;
    starty = FRAME1YSTART;
    startx = FRAME1XSTART;

    outer = new char*[height];
    for(size_t i = 0; i < height; i++)
    {
        outer[i] = new char[width + 1];
        for(size_t j = 0; j < width + 1; j++)
        {
            outer[i][j] = FRAME1[i][j];
        }
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
