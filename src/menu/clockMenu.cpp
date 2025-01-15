#include "clockMenu.hpp"
#include "../tui/tui.hpp"

void ClockMenu::refreshMenu()
{
    height = 1;
    width = Tui::Cols();
    y = Tui::Lines() - 1;
    x = 0;
}

ClockMenu::ClockMenu(int color)
    : m_color(color)
{
    refreshMenu();

    messages.push_back("q: Quit | h: Hide Menu | m: Move inner frame");
    messages.push_back("m: Main Menu | s: Save to out.cf | Use the arrow keys to move frame");
    currMessage = 0;
}

void ClockMenu::displayMenu()
{
    refreshMenu();

    std::string message = messages[currMessage];

    if (width > message.size())
    {
        message.append(width - message.size(), ' ');
    }

    Tui::DisplayMessage(x, y, message, m_color);
}

bool ClockMenu::changeMessage(size_t index)
{
    if(index >= messages.size())
        return false;

    currMessage = index;
    return true;
}
