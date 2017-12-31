#include "clock.hpp"
#include <thread>
#include <ncurses.h>
#include <fstream>
#include <sstream>

/**
 * Main contains the main loop for clock.
 * Displays the current time with ASCII art.
 */
int main()
{
    enum ColorPairs
    {
        PAIR_BLACK = 1,
        PAIR_RED = 2,
        PAIR_GREEN = 3,
        PAIR_YELLOW = 4,
        PAIR_BLUE = 5,
        PAIR_MAGENTA = 6,
        PAIR_CYAN = 7,
        PAIR_WHITE = 8
    };

    bool readClock = false;
    std::string filename;
    std::ifstream inFile("clock.conf");
    if(inFile.is_open())
    {

        std::string line;
        
        while(std::getline(inFile, line))
        {
            std::stringstream lineStream(line);

            std::string s1;
            lineStream >> s1;

            if(s1 == "read_clock")
            {
                lineStream >> readClock;
            }
            else if(s1 == "read_clock_file")
            {
                lineStream >> filename;
            }
        }
    }

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
    init_pair(PAIR_BLACK, COLOR_BLACK, -1);
    init_pair(PAIR_RED, COLOR_RED, -1);
    init_pair(PAIR_GREEN, COLOR_GREEN, -1);
    init_pair(PAIR_YELLOW, COLOR_YELLOW, -1);
    init_pair(PAIR_BLUE, COLOR_BLUE, -1);
    init_pair(PAIR_MAGENTA, COLOR_MAGENTA, -1);
    init_pair(PAIR_CYAN, COLOR_CYAN, -1);
    init_pair(PAIR_WHITE, COLOR_WHITE, -1);

    // Tracks time passed for updates.
    time_t prev = 0;
    time_t now;
    
    Clock c;

    if(readClock)
    {
        c = Clock(filename);
    }

    bool run = true;
    while(run)
    {
        now = std::time(0);
        time_t elapsed = now - prev;
        
        if(elapsed > 1)
        {
            clear();
            c.displayClock();
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
