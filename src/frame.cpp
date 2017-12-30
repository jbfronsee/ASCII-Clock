#include "frame.hpp"
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <sstream>

Clock::Clock()
{
    // Initialize array of digits.
    for(int i = 0; i < NUMDIG; i++)
    {
        digits.push_back(Digit(i));
    }

    height = Digit::DEF_ROW;
    width = Digit::DEF_COL*4 + 1;
 
    separator.push_back(' ');
    separator.push_back('.');
    separator.push_back('.');
    
    updateTime();
}

Clock::Clock(const Clock& clock)
{
    this->digits = clock.digits;
    this->separator = clock.separator;
    this->currTime = clock.currTime;
}

Clock::~Clock()
{
}

Clock& Clock::operator=(const Clock& clock)
{
    this->digits = clock.digits;
    this->separator = clock.separator;
    this->currTime = clock.currTime;
}

void Clock::updateTime()
{
    time_t t = std::time(0);
    currTime = std::localtime(&t);
}

void Clock::printSeparator()
{
    int y, x;
    getyx(stdscr, y, x);
    for(size_t i = 0; i < separator.size(); i++)
    {
       char sstr[] = {separator[i], '\0'};
       mvprintw(y + i, x, sstr); 
    }

    move(y, x + 1);
}

void Clock::printTime()
{
    updateTime();

    move((LINES - height)/2, (COLS - width)/2);
    
    // Reformat time.
    int hour;
    if(currTime->tm_hour > 12)
    {
        hour = currTime->tm_hour - 12;
    }
    else if(currTime->tm_hour == 0)
    {
        hour = 12;
    }
    else
    {
        hour = currTime->tm_hour;
    }

    int min = currTime->tm_min;

    // Get digits from time.
    int mLSB = min % 10;
    min /= 10;
    int mMSB = min % 10;

    int len;
    if(hour > 9)
    {
        len = 2;
        hour %= 10;
    }
    else
    {
        len = 1;
    }

    // Print digits to console.
    if(len == 2)
    {
        digits[1].printDig();
    }
    else
    {
        int y, x;
        getyx(stdscr, y, x);
        for(size_t i = 0; i < height; i++)
        {
            char sstr[] = {' ', ' ', ' ', '\0'};
            mvprintw(y + i, x, sstr); 
        }

        move(y, x + Digit::DEF_COL);
    }

    digits[hour].printDig();

    printSeparator();

    digits[mMSB].printDig();

    digits[mLSB].printDig();
}

void Clock::printDigits()
{
    for(Digit d: digits)
    {
        d.printDig();
    }
}
