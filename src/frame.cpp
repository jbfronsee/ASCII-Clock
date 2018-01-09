#include "frame.hpp"
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <sstream>

void Frame::constructDefault()
{
    // Initialize array of digits.
    for(size_t i = 0; i < NUMDIG; i++)
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
Frame::Frame()
{
    constructDefault();
}

Frame::Frame(std::string filename)
{
    std::ifstream inFile(filename);
    if(inFile.is_open())
    {
        std::string header;
        std::getline(inFile, header);
        std::stringstream headStream(header);

        // Store header info.
        size_t row;
        size_t col;
        if(!(headStream >> row))
        {
            //TODO: Error message
            constructDefault();
        }
        else if(!(headStream >> col))
        {
            //TODO: Error message
            constructDefault();
        }
        else
        {
            bool fail = false;
            for(size_t i = 0; !fail && i < NUMDIG; i++)
            {
                std::vector<std::vector<char>> asciiDig;
                std::string line;
                for(size_t j = 0; !fail && j < row && std::getline(inFile,line); j++)
                {
                    if(line.size() != col)
                    {
                        //TODO: Error message
                        constructDefault();
                        fail = true;
                    }
                    else
                    {
                        asciiDig.push_back(std::vector<char>());
                        for(size_t k = 0; k < col; k++)
                        {
                            asciiDig.at(j).push_back(line.at(k));
                        }
                    }
                }

                if(asciiDig.size() != row)
                {
                    //TODO: Error message
                    constructDefault();
                    fail = true;
                }
                else
                {
                    digits.push_back(Digit(asciiDig));
                }
            }

            if(!fail)
            {
                height = row;
                width = col*4 + 1;
                separator.push_back(' ');
                separator.push_back('.');
                separator.push_back('.');
    
                updateTime();
            }
        }
    }
    else
    {
        //TODO: Error message
        constructDefault();
    }
}
Frame::Frame(const Frame& frame)
{
    this->digits = frame.digits;
    this->separator = frame.separator;
    this->currTime = frame.currTime;
}

Frame::~Frame()
{
}

Frame& Frame::operator=(const Frame& frame)
{
    this->digits = frame.digits;
    this->separator = frame.separator;
    this->currTime = frame.currTime;
    return *this;
}

void Frame::updateTime()
{
    time_t t = std::time(0);
    currTime = std::localtime(&t);
}

void Frame::printSeparator()
{
    //init_pair(1, COLOR_WHITE, -1);
    //attron(COLOR_PAIR(1));
    int y, x;
    getyx(stdscr, y, x);
    for(size_t i = 0; i < separator.size(); i++)
    {
       char sstr[] = {separator[i], '\0'};
       mvprintw(y + i, x, sstr); 
    }

    move(y, x + 1);
    //attroff(COLOR_PAIR(1));
}

void Frame::printTime()
{
    updateTime();

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
        move(y, x + Digit::DEF_COL);
    }

    digits[hour].printDig();

    printSeparator();

    digits[mMSB].printDig();

    digits[mLSB].printDig();
}

void Frame::printDigits()
{
    for(Digit d: digits)
    {
        d.printDig();
    }
}
