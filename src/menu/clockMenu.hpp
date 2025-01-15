#include <vector>
#include <string>

class ClockMenu
{
    private:
        size_t x, y, height, width;
        int m_color;
        std::vector<std::string> messages;
        size_t currMessage;

        
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
