#ifndef TUI_H
#define TUI_H

#include <string>
#include <vector>
#include <ncurses.h>

namespace Tui
{
    namespace Input
    {
        enum class Keys
        {
            UP = KEY_UP,
            DOWN = KEY_DOWN,
            LEFT = KEY_LEFT,
            RIGHT = KEY_RIGHT
        };

        int GetChar();
    }

    enum class ColorPairs
    {
        DEFAULT = 0,
        BLACK = 1,
        RED = 2,
        GREEN = 3,
        YELLOW = 4,
        BLUE = 5,
        MAGENTA = 6,
        CYAN = 7,
        WHITE = 8,
        MENU = 9
    };

    ColorPairs AsColor(const std::string& colorStr);

    void Init();

    void Close();

    int Lines();

    int Cols();

    void Clear();

    std::pair<int, int> GetXY();

    void Move(const int x, const int y);

    void DisplayMessage(
      const int x,
      const int y,
      const std::string& message,
      const Tui::ColorPairs color = Tui::ColorPairs::DEFAULT
    );

    void DisplayMessages(
      const std::vector<std::string>& message,
      const int addX,
      const int addY,
      const Tui::ColorPairs color = Tui::ColorPairs::DEFAULT
    );

    // Refresh and dump contents to screen
    void Refresh();
};

#endif /* TUI_H */
