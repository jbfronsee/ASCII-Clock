#ifndef FRAME_H
#define FRAME_H
#include <ctime>

class Clock
{
    private:
        // Constants initialized here for 3D array.
        static const int NUMDIG = 10;
        static const int DEF_DROW = 3;
        static const int DEF_DCOL = 3;
        static const char ASCII_DIGITS[NUMDIG][DEF_DROW][DEF_DCOL]; 

        // digits is an array of ASCII digits from 0 - 9 
        // with drow x dcol chars. 
        char** digits[NUMDIG];
        int drow, dcol;
        
        char* separator;
        std::tm* currTime;

        void updateTime();

    public:
        Clock();
        
        ~Clock();

        void printTime();
};
#endif /* FRAME_H */
