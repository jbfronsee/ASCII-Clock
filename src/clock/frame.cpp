#include "frame.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void Frame::constructDefault(Tui::ColorPairs color)
{
    // Initialize array of digits.
    for(size_t i = 0; i < NUMDIG; i++)
    {
        mDigits.push_back(Digit(i, color));
    }

    mHeight = Digit::DEF_ROW;
    mWidth = Digit::DEF_COL*4 + 1;

    mSeparator.push_back(" ");
    mSeparator.push_back(".");
    mSeparator.push_back(".");

    updateTime();
}

Frame::Frame(std::string filename, Tui::ColorPairs color)
{
    if (filename.empty())
    {
        constructDefault(color);
        return;
    }

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
                std::vector<std::string> asciiDig;
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
                        asciiDig.push_back(line);
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
                    mDigits.push_back(Digit(asciiDig, color));
                }
            }

            if(!fail)
            {
                mHeight = row;
                mWidth = col*4 + 1;
                mSeparator.push_back(" ");
                mSeparator.push_back(".");
                mSeparator.push_back(".");

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

void Frame::updateTime()
{
    time_t t = std::time(0);
    mCurrTime = std::localtime(&t);
}

void Frame::printSeparator()
{
    Tui::DisplayMessages(mSeparator, 1, 0, Tui::ColorPairs::RED);
}

void Frame::printTime()
{
    updateTime();

    // Reformat time.
    int hour;
    if(mCurrTime->tm_hour > 12)
    {
        hour = mCurrTime->tm_hour - 12;
    }
    else if(mCurrTime->tm_hour == 0)
    {
        hour = 12;
    }
    else
    {
        hour = mCurrTime->tm_hour;
    }

    int min = mCurrTime->tm_min;

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
        mDigits[1].printDig();
    }
    else
    {

        auto [x, y] = Tui::GetXY();
        Tui::Move(x + Digit::DEF_COL, y);
    }

    mDigits[hour].printDig();

    printSeparator();

    mDigits[mMSB].printDig();

    mDigits[mLSB].printDig();
}

void Frame::printDigits()
{
    for(Digit d: mDigits)
    {
        d.printDig();
    }
}
