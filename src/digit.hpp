#ifndef DIGIT_H
#define DIGIT_H

#include <ncurses.h>
#include <vector>

/**
 * @author Joshua Fronsee <jbfronsee@gmail.com>
 * 
 * Class represents an ASCII art digit.
 *
 */
class Digit
{
    private:
        /* Member variables */
        size_t row, col;
        char** dig;
        int color;

    public:
        /* Class constants */
        static const int DEF_COLOR = 2;
        static const size_t DEF_ROW = 3;
        static const size_t DEF_COL = 3;
        static const char ASCII_ZERO[DEF_ROW][DEF_COL + 1],
        ASCII_ONE[DEF_ROW][DEF_COL + 1],ASCII_TWO[DEF_ROW][DEF_COL + 1],
        ASCII_THREE[DEF_ROW][DEF_COL + 1],ASCII_FOUR[DEF_ROW][DEF_COL + 1],
        ASCII_FIVE[DEF_ROW][DEF_COL + 1],ASCII_SIX[DEF_ROW][DEF_COL + 1],
        ASCII_SEVEN[DEF_ROW][DEF_COL + 1],ASCII_EIGHT[DEF_ROW][DEF_COL + 1],
        ASCII_NINE[DEF_ROW][DEF_COL + 1];
        
       /**
        * Default constructor constructs an
        * ASCII_ZERO digit.
        */
        Digit();

        /**
         * Constructs an ASCII digit based on val.
         * If val < 0 or > 9 constructs ASCII_ZERO.
         *
         * @param val - Value that ASCII digit will represent.
         */
        Digit(int val);

        /**
         * Constructs an ASCII digit based on val.
         * If val < 0 or > 9 constructs ASCII_ZERO.
         * 
         * @param val - Value that ASCII digit will represent.
         * @param color - Initial color of the digit.
         */
        Digit(int val, int color);
       
       /**
        * Constructs an ASCII art digit from a vector.
        *
        * @param vec - The 2D vector representing the digit.
        */
        Digit(std::vector<std::vector<char>>& vec);

        /**
         * Constructs an ASCII art digit from a vector.
         *
         * @param vec - The 2D vector representing the digit.
         * @param color - The initial color of the digit.
         */
         Digit(std::vector<std::vector<char>>& vec, int color); 

        /**
         * Copy constructor for Digit.
         * 
         * @param digit - Digit to copy.
         */
        Digit(const Digit& digit);

        /**
         * Destructor for Digit. Frees memory.
         */
        ~Digit();

        /**
         * Assignment operator for digit.
         *
         * @param digit - Digit to copy.
         */
        Digit& operator=(const Digit& digit);

        /**
         * Set color of Digit.
         *
         * @param color - ncurses color from 0 - 7
         */
        void setColor(int color);

        /**
         * Prints Digit using ncurses. ncurses must be
         * initialized for this to work.
         */
        void printDig();
       
        /* Getter Methods */
        
        /**
         * Returns row.
         *
         * @return row
         */
        size_t getRow();

        /**
         * Returns col.
         *
         * @return col
         */
        size_t getCol();

        /**
         * Returns color component.
         *
         * @return color
         */
        int getColor();
};

#endif /* DIGIT_H */
