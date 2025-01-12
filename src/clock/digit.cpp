#include "digit.hpp"
#include <ncurses.h>

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

Digit::Digit() : Digit(0) { }

Digit::Digit(int val) : Digit(val, DEF_COLOR) { }

Digit::Digit(int val, int color)
{
    // ncurses colors go from 1 - 8.
    if(color < 1 || color > 8)
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
    row = DEF_ROW; 
    col = DEF_COL;

    dig = arr;

    this->color = color;
}

Digit::Digit(std::vector<std::string>& vec) : Digit(vec, DEF_COLOR) { }

Digit::Digit(std::vector<std::string>& vec, int color)
{
    if(color < 1 || color > 8)
    {
        color = DEF_COLOR;
    }

    row = vec.size();
    col = vec.at(0).size();

    dig = vec;

    this->color = color;
}

Digit::Digit(const Digit& digit)
{
    this->row = digit.row;
    this->col = digit.col;

    this->dig = digit.dig;

    this->color = digit.color;
}

Digit::~Digit()
{

}

Digit& Digit::operator=(const Digit& digit)
{
    this->row = digit.row;
    this->col = digit.col;

    this->dig = digit.dig;
    this->color = digit.color;

    return *this;
}

void Digit::setColor(int color)
{
    if(color < 1 || color > 8)
    {
        color = DEF_COLOR;
    }

    this->color = color;
}

void Digit::printDig(const Tui& tui)
{
    // Print the digit with ncurses.
    // ncurses should be initialized first.
    attron(COLOR_PAIR(color));
    tui.DisplayMessagesAndMove(dig, col, 0);
    attroff(COLOR_PAIR(color));
}

size_t Digit::getRow()
{
    return row;
}

size_t Digit::getCol()
{
    return col;
}

int Digit::getColor()
{
    return color;
}
