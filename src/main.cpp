#include "clock/clock.hpp"
#include "config/config.hpp"
#include "menu/clockMenu.hpp"
#include "tui/tui.hpp"

#include <chrono>
#include <thread>

/**
 * Main contains the main loop for clock.
 * Displays the current time with ASCII art.
 */
int main(int argc, char* argv[])
{
    Config::Opts opts = Config::GetOpts(std::vector<std::string>(argv, argv + argc));

    Tui::Init();

    // Tracks time passed for updates.
    std::chrono::milliseconds now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    std::chrono::milliseconds prev = now;

    Clock c("", opts.clockColor, opts.digitsColor);
    ClockMenu menu(Tui::ColorPairs::MENU);

    if(opts.readClock)
    {
        c = Clock(opts.clockFile, opts.clockColor, opts.digitsColor);
    }

    if(opts.readDigit)
    {
        c.switchFrame(opts.digitFile, opts.digitsColor);
    }

    bool run = true;
    bool showMenu = !opts.autoHide;
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
                case 'q':
                    run = false;
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
