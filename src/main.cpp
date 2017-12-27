#include "frame.hpp"
#include <ncurses.h>

int main()
{
    initscr();
    nodelay(stdscr, TRUE); 
    
    time_t prev = 0;
    time_t now;
    
    bool run = true;
    while(run)
    {
        now = std::time(0);
        time_t elapsed = now - prev;
        
        if(elapsed > 1)
        {
            clear();
            Clock c;
            c.printTime();
            refresh();
            prev = now;
        }

        int ch = getch();
        if(ch != ERR)
        {
            run = false;
        }
    }

    endwin();
    return 0;
}
