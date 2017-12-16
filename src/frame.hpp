#ifndef FRAME_H
#define FRAME_H
#include <ctime>

class Clock
{
    private:
        static const int NUMDIG = 10;
        
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
