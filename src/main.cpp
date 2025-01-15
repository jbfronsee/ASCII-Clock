#include "tui/tui.hpp"
#include "clock/clock.hpp"
#include "menu/clockMenu.hpp"
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

/**
 * Main contains the main loop for clock.
 * Displays the current time with ASCII art.
 */
int main()
{
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

    Tui::Init();

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
            c.displayClock();
            if(showMenu)
            {
                menu.displayMenu();
            }

            Tui::Refresh();
            prev = now;
        }
        else
        {
            // Sleep until update to save cpu usage.
            std::this_thread::sleep_for(milliseconds(50));
        }

        int ch = Tui::Input::GetChar();
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
                using namespace Tui::Input;
                case static_cast<int>(Keys::UP):
                    y = c.getFrameY();
                    c.moveFrame(--y, c.getFrameX());
                    break;
                case static_cast<int>(Keys::DOWN):
                    y = c.getFrameY();
                    c.moveFrame(++y, c.getFrameX());
                    break;
                case static_cast<int>(Keys::LEFT):
                    x = c.getFrameX();
                    c.moveFrame(c.getFrameY(), --x);
                    break;
                case static_cast<int>(Keys::RIGHT):
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

    Tui::Close();
    return 0;
}
