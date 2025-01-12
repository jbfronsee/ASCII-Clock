#include <ncurses.h>
#include "clockMenu.hpp"

void ClockMenu::refreshMenu()
{
    height = 1;
    width = COLS;
    y = LINES - 1;
    x = 0;
}

ClockMenu::ClockMenu() : ClockMenu(1) { }

ClockMenu::ClockMenu(int color)
{
    this->color = color;
    
    refreshMenu();

    messages.push_back("q: Quit | h: Hide Menu | m: Move inner frame");
    messages.push_back("m: Main Menu | s: Save to out.cf | Use the arrow keys to move frame");
    currMessage = 0;
}

void ClockMenu::displayMenu()
{
    refreshMenu();
    
    std::string& message = messages[currMessage];

    attron(COLOR_PAIR(color));
    mvprintw(y, x, message.c_str());
    for(size_t i = message.size(); i < width; i++)
    {
        mvaddch(y, x + i, ' ');
    }
    attroff(COLOR_PAIR(color));
}

bool ClockMenu::changeMessage(size_t index)
{
    if(index >= messages.size())
        return false;
    
    currMessage = index;
    return true;
}
