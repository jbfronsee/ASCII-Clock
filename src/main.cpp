#include "frame.hpp"
#include <thread>
#include <ncurses.h>

/**
 * Main contains the main loop for clock.
 * Displays the current time with ASCII art.
 */
int main()
{
    initscr();
    // Don't pause for user input.
    nodelay(stdscr, TRUE); 
    // Don't echo usr input.
    noecho();
    // Turn off cursor.
    curs_set(0);

    if(has_colors() == false)
    {
        endwin();
        printf("Color is not supported by terminal.");
        exit(1);
    }

    // Set up colors.
    start_color();
    use_default_colors(); 

    // Tracks time passed for updates.
    time_t prev = 0;
    time_t now;
    
    Clock c;

    bool run = true;
    while(run)
    {
        now = std::time(0);
        time_t elapsed = now - prev;
        
        if(elapsed > 1)
        {
            clear();
            c.printTime();
            refresh();
            prev = now;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }

        int ch = getch();
        if(ch == 'q')
        {
            run = false;
        }
    }

    endwin();
    return 0;
}
