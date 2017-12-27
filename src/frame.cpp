#include "frame.hpp"
#include <ncurses.h>
#include <fstream>
#include <iostream>
#include <sstream>

const char Clock::ASCII_DIGITS[][DEF_DROW][DEF_DCOL] = {{{' ', '_', ' '},
                                                         {'|', ' ', '|'},
                                                         {'|', '_', '|'}},
                                        
                                                        {{' ', ' ', ' '},
                                                         {' ', ' ', '|'},
                                                         {' ', ' ', '|'}},
                                          
                                                        {{' ', '_', ' '},
                                                         {' ', '_', '|'},    
                                                         {'|', '_', ' '}},
                                          
                                                        {{' ', '_', ' '},
                                                         {' ', '_', '|'},
                                                         {' ', '_', '|'}},
                                          
                                                        {{' ', ' ', ' '},
                                                         {'|', '_', '|'},
                                                         {' ', ' ', '|'}},
                                          
                                                        {{' ', '_', ' '},
                                                         {'|', '_', ' '},
                                                         {' ', '_', '|'}},
                                          
                                                        {{' ', '_', ' '},
                                                         {'|', '_', ' '},
                                                         {'|', '_', '|'}},
                                          
                                                        {{' ', '_', ' '},
                                                         {' ', ' ', '|'},
                                                         {' ', ' ', '|'}},
                                          
                                                        {{' ', '_', ' '},
                                                         {'|', '_', '|'},
                                                         {'|', '_', '|'}},
                                          
                                                        {{' ', '_', ' '},
                                                         {'|', '_', '|'},
                                                         {' ', ' ', '|'}}};

Clock::Clock()
{
    drow = DEF_DROW;
    dcol = DEF_DCOL;

    // Initialize array of digits.
    for(int i = 0; i < NUMDIG; i++)
    {
        digits[i] = new char*[drow];
        for(int j = 0; j < drow; j++)
        {
            digits[i][j] = new char[dcol];
            for(int k = 0; k < dcol; k++)
            {
                digits[i][j][k] = ASCII_DIGITS[i][j][k];
            }
        }
    }


/*    // Open file
    std::ifstream inFile(DEFNAME);
    if(!inFile.is_open())
    {
        std::cout << "ERROR: Unable to open file." << std::endl;
        std::exit(1);
    }
    std::string header;

    std::getline(inFile, header);
    std::stringstream headStream(header);

    // Store header info.
    char delim;

    if(!(headStream >> delim))
    {
        std::cout << "ERROR: Too few args in header." << std::endl;
        std::exit(1);
    }

    if(!(headStream >> drow))
    {
        std::cout << "ERROR: Too few args in header." << std::endl;
        std::exit(1);
    }

    if(!(headStream >> dcol))
    {
        std::cout << "ERROR: Too few args in header." << std::endl;
        std::exit(1);
    }

    // Initialize array of digits.
    for(int i = 0; i < NUMDIG; i++)
    {
        digits[i] = new char*[drow];
        for(int j = 0; j < dcol; j++)
        {
            digits[i][j] = new char[dcol];
        }
    }

    int eNum = 0, row = 0, col = 0; 

    // Read each line and process input.
    // Lines represent a row in ASCII representation.
    std::string line;
    while(std::getline(inFile,line))
    {
        std::stringstream strStream(line);
        std::string elem;

        // Process each digit in the row.
        eNum = 0;
        while(std::getline(strStream,elem,delim))
        {
            // Process each character in digit->row->col.
            for(col = 0; eNum < NUMDIG && col < elem.size(); col++)
            {
                digits[eNum][row][col] = elem.at(col);  
            }

            eNum++;
        }

        row++;
    }
*/
    separator = new char[3];
    separator[0] = ' ', separator[1] = '.', separator[2] = '.';
}

Clock::~Clock()
{
    for(int i = 0; i < NUMDIG; i++)
    {
        for(int j = 0; j < drow; j++)
        {
            delete[] digits[i][j];
        }

        delete[] digits[i];
    }

    delete[] separator;
}

void Clock::updateTime()
{
    time_t t = std::time(0);
    currTime = std::localtime(&t);
}

void Clock::printTime()
{
    /*for(int i = 0; i < NUMDIG; i++)
      {
      for(int j = 0; j < drow; j++)
      {
      for(int k = 0; k < dcol; k++)
      {
      std::cout << digits[i][j][k];
      }
      std::cout << std::endl;
      }

      std::cout << std::endl << std::endl;
      }*/

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
    for(int row = 0; row < drow; row++)
    {
        if(len == 2)
        {
            for(int col = 0; col < dcol; col++)
            {
                char dstr[2] = {digits[1][row][col], '\0'};
                printw(dstr);
            }

            printw(" ");
        }

        for(int col = 0; col < dcol; col++)
        {
            char dstr[2] = {digits[hour][row][col], '\0'};
            printw(dstr);
        }

        char sstr[2] = {separator[row], '\0'};
        printw(sstr);

        for(int col = 0; col < dcol; col++)
        {
            char dstr[2] = {digits[mMSB][row][col], '\0'};
            printw(dstr);
        }

        printw(" ");

        for(int col = 0; col < dcol; col++)
        {
            char dstr[2] = {digits[mLSB][row][col], '\0'};
            printw(dstr);
        }

        printw("\n");
    }

}
