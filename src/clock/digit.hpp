#ifndef DIGIT_H
#define DIGIT_H

#include <string>
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
        size_t mRow, mCol;
        std::vector<std::string> mDig;
        int mColor;

    public:
        /* Class constants */
        static const int DEF_COLOR = 2;
        static const size_t DEF_ROW = 3;
        static const size_t DEF_COL = 3;
        static const std::vector<std::string>
            ASCII_ZERO,
            ASCII_ONE,
            ASCII_TWO,
            ASCII_THREE,
            ASCII_FOUR,
            ASCII_FIVE,
            ASCII_SIX,
            ASCII_SEVEN,
            ASCII_EIGHT,
            ASCII_NINE;

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
        Digit(std::vector<std::string>& vec);

        /**
         * Constructs an ASCII art digit from a vector.
         *
         * @param vec - The 2D vector representing the digit.
         * @param color - The initial color of the digit.
         */
         Digit(std::vector<std::string>& vec, int color);

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
