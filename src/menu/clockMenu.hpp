#ifndef CLOCKMENU_H
#define CLOCKMENU_H

#include <string>
#include <vector>

#include "../tui/tui.hpp"

class ClockMenu
{
    private:
        size_t mX, mY, mHeight, mWidth;
        Tui::ColorPairs mColor;
        std::vector<std::string> mMessages;
        size_t mCurrMessage;

        /**
         * Refreshes border in case of resize.
         */
        void refreshMenu();
    public:
        /**
         * Construct menu object with
         * color pair specified by color.
         */
        ClockMenu(const Tui::ColorPairs color = Tui::ColorPairs::BLACK);
        /**
         * Display menu to screen.
         */
        void displayMenu();

        /**
         * Change which message is printed.
         *
         * @param index - The message index to display.
         * @return true if index in range false otherwise.
         */
        bool changeMessage(size_t index);

        /**
         * Returns the list of messages to display.
         */
       // std::vector<std::string>& getMessages();
};

#endif /* CLOCKMENU_H */
