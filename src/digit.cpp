#include "digit.hpp"
#include <ncurses.h>

const char Digit::ASCII_ZERO[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                      "| |",
                                                      "|_|"};
                                        
const char Digit::ASCII_ONE[DEF_ROW][DEF_COL + 1] = {"   ",
                                                     "  |",
                                                     "  |"};
                                          
const char Digit::ASCII_TWO[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                     " _|",    
                                                     "|_ "};
                                          
const char Digit::ASCII_THREE[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                       " _|",
                                                       " _|"};
                                          
const char Digit::ASCII_FOUR[DEF_ROW][DEF_COL + 1] = {"   ",
                                                      "|_|",
                                                      "  |"};
                                          
const char Digit::ASCII_FIVE[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                      "|_ ",
                                                      " _|"};
                                          
const char Digit::ASCII_SIX[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                     "|_ ",
                                                     "|_|"};
                                          
const char Digit::ASCII_SEVEN[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                       "  |",
                                                       "  |"};
                                          
const char Digit::ASCII_EIGHT[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                       "|_|",
                                                       "|_|"};
                                          
const char Digit::ASCII_NINE[DEF_ROW][DEF_COL + 1] = {" _ ",
                                                      "|_|",
                                                      "  |"};

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
    const char (*arr)[DEF_COL + 1];
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
   
    dig = new char*[row];
    for(size_t i = 0; i < row; i++)
    {
        dig[i] = new char[col + 1];
        for(size_t j = 0; j < col + 1; j++)
        {
            dig[i][j] = arr[i][j];
        }
    }

    this->color = color;
}

Digit::Digit(std::vector<std::vector<char>>& vec) : Digit(vec, DEF_COLOR) { }

Digit::Digit(std::vector<std::vector<char>>& vec, int color)
{
    if(color < 1 || color > 8)
    {
        color = DEF_COLOR;
    }
    
    row = vec.size();
    col = vec.at(0).size();

    dig = new char*[row];
    for(size_t i = 0; i < row; i++)
    {
        dig[i] = new char[col + 1];
        for(size_t j = 0; j < col + 1; j++)
        {
            dig[i][j] = vec[i][j];
        }
    }

    this->color = color;
}

Digit::Digit(const Digit& digit)
{
    this->row = digit.row;
    this->col = digit.col;
    
    this->dig = new char*[digit.row];
    for(size_t i = 0; i < digit.row; i++)
    {
        this->dig[i] = new char[digit.col];
        for(size_t j = 0; j < digit.col + 1; j++)
        {
            this->dig[i][j] = digit.dig[i][j];
        }
    }

    this->color = digit.color;
}

Digit::~Digit()
{
    for(size_t i = 0; i < row; i++)
    {
        delete[] dig[i];
    }

    delete [] dig;
}

Digit& Digit::operator=(const Digit& digit)
{
    for(size_t i = 0; i < this->row; i++)
    {
        delete[] this->dig[i];
    }

    delete[] this->dig;

    this->row = digit.row;
    this->col = digit.col;
    
    this->dig = new char*[digit.row];
    for(size_t i = 0; i < digit.row; i++)
    {
        this->dig[i] = new char[digit.col];
        for(size_t j = 0; j < digit.col + 1; j++)
        {
            this->dig[i][j] = digit.dig[i][j];
        }
    }

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

void Digit::printDig()
{
    // Print the digit with ncurses.
    // ncurses should be initialized first.
    attron(COLOR_PAIR(color));
    int y, x;
    getyx(stdscr, y, x);
    for(size_t i = 0; i < row; i++)
    {
        mvprintw(y + i, x, dig[i]); 
    }

    move(y, x + col);
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
