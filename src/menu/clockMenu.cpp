#include "clockMenu.hpp"

void ClockMenu::refreshMenu()
{
    mHeight = 1;
    mWidth = Tui::Cols();
    mY = Tui::Lines() - 1;
    mX = 0;
}

ClockMenu::ClockMenu(const Tui::ColorPairs color)
    : mColor(color)
{
    refreshMenu();

    mMessages.push_back("q: Quit | h: Hide Menu | m: Move inner frame");
    mMessages.push_back("m: Main Menu | s: Save to out.cf | Use the arrow keys to move frame");
    mCurrMessage = 0;
}

void ClockMenu::displayMenu()
{
    refreshMenu();

    std::string message = mMessages[mCurrMessage];

    if (mWidth > message.size())
    {
        message.append(mWidth - message.size(), ' ');
    }

    Tui::DisplayMessage(mX, mY, message, mColor);
}

bool ClockMenu::changeMessage(size_t index)
{
    if(index >= mMessages.size())
        return false;

    mCurrMessage = index;
    return true;
}
