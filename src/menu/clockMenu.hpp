#include <vector>
#include <string>

class ClockMenu
{
    private:
        size_t mX, mY, mHeight, mWidth;
        int mColor;
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
        ClockMenu(int color = 1);
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
