#include "clock.hpp"
#include "clockMenu.hpp"
#include <chrono>
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

    const int MENU_COLOR_PAIR = 9;

    bool readClock = false, readDigit = false;
    std::string clockFname, digitFname;
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
                lineStream >> clockFname;
            }
            else if(s1 == "read_digit")
            {
                lineStream >> readDigit;
            }
            else if(s1 == "read_digit_file")
            {
                lineStream >> digitFname;
            }
        }
    }

    initscr();
    keypad(stdscr, TRUE);
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
    init_pair(MENU_COLOR_PAIR, COLOR_WHITE, COLOR_BLUE);

    // Tracks time passed for updates.
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds prev = now;

    Clock c;
    ClockMenu menu(MENU_COLOR_PAIR);

    if(readClock)
    {
        c = Clock(clockFname);
    }

    if(readDigit)
    {
        c.switchFrame(digitFname);
    }

    bool run = true;
    bool showMenu = true;
    bool moveInner = false;
    while(run)
    {
        using namespace std::chrono;
        now = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
        milliseconds elapsed = now - prev;
        
        if(elapsed > milliseconds(50))
        {
            clear();
            c.displayClock();
            if(showMenu)
            {
                menu.displayMenu();
            }
            
            refresh();
            prev = now;
        }
        else
        {
            // Sleep until update to save cpu usage.
            std::this_thread::sleep_for(milliseconds(50));
        }

        int ch = getch();
        if(!moveInner)
        {
            switch(ch)
            {
                case 'q':
                    run = false;
                    break;
                case 'h':
                    showMenu = !showMenu;
                    break;
                case 'm':
                    showMenu = true;
                    moveInner = true;
                    menu.changeMessage(1);
                    break;
                default:
                    break;
            }
        }
        else
        {
            int y = 0;
            int x = 0;
            switch(ch)
            {
                case KEY_UP:
                    y = c.getFrameY();
                    c.moveFrame(--y, c.getFrameX());
                    break;
                case KEY_DOWN:
                    y = c.getFrameY();
                    c.moveFrame(++y, c.getFrameX());
                    break;
                case KEY_LEFT:
                    x = c.getFrameX();
                    c.moveFrame(c.getFrameY(), --x);
                    break;
                case KEY_RIGHT:
                    x = c.getFrameX();
                    c.moveFrame(c.getFrameY(), ++x);
                    break;
                case 'm':
                    moveInner = false;
                    menu.changeMessage(0);
                    break;
                case 's':
                    c.writeClock();
                    break;
                default:
                    break;
            }
        }
    }

    endwin();
    return 0;
}
