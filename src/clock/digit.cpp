#include "digit.hpp"

const std::vector<std::string> Digit::ASCII_ZERO = {
    " _ ",
    "| |",
    "|_|"
};

const std::vector<std::string> Digit::ASCII_ONE = {
    "   ",
    "  |",
    "  |"
};

const std::vector<std::string> Digit::ASCII_TWO = {
    " _ ",
    " _|",
    "|_ "
};

const std::vector<std::string> Digit::ASCII_THREE = {
    " _ ",
    " _|",
    " _|"
};

const std::vector<std::string> Digit::ASCII_FOUR = {
    "   ",
    "|_|",
    "  |"
};

const std::vector<std::string> Digit::ASCII_FIVE = {
    " _ ",
    "|_ ",
    " _|"
};

const std::vector<std::string> Digit::ASCII_SIX = {
    " _ ",
    "|_ ",
    "|_|"
};

const std::vector<std::string> Digit::ASCII_SEVEN = {
    " _ ",
    "  |",
    "  |"
};

const std::vector<std::string> Digit::ASCII_EIGHT = {
    " _ ",
    "|_|",
    "|_|"
};

const std::vector<std::string> Digit::ASCII_NINE = {
    " _ ",
    "|_|",
    "  |"
};

Digit::Digit(int val, Tui::ColorPairs color)
{
    // ncurses colors go from 1 - 8.
    if(color == Tui::ColorPairs::DEFAULT)
    {
        color = DEF_COLOR;
    }

    // Determine which array to use.
    std::vector<std::string> arr;
    switch(val)
    {
        case 1:
            arr = ASCII_ONE;
            break;
        case 2:
            arr = ASCII_TWO;
            break;
        case 3:
            arr = ASCII_THREE;
            break;
        case 4:
            arr = ASCII_FOUR;
            break;
        case 5:
            arr = ASCII_FIVE;
            break;
        case 6:
            arr = ASCII_SIX;
            break;
        case 7:
            arr = ASCII_SEVEN;
            break;
        case 8:
            arr = ASCII_EIGHT;
            break;
        case 9:
            arr = ASCII_NINE;
            break;
        default:
            arr = ASCII_ZERO;
            break;
    }


    // Build the dig array with ASCII default.
    mRow = DEF_ROW;
    mCol = DEF_COL;

    mDig = arr;

    mColor = color;
}

Digit::Digit(std::vector<std::string>& vec, Tui::ColorPairs color)
{
    if(color == Tui::ColorPairs::DEFAULT)
    {
        color = DEF_COLOR;
    }

    mRow = vec.size();
    mCol = vec.at(0).size();

    mDig = vec;

    mColor = color;
}

void Digit::setColor(Tui::ColorPairs color)
{
    mColor = color;
}

void Digit::printDig()
{
    Tui::DisplayMessages(mDig, mCol, 0, mColor);
}

size_t Digit::getRow()
{
    return mRow;
}

size_t Digit::getCol()
{
    return mCol;
}

Tui::ColorPairs Digit::getColor()
{
    return mColor;
}
