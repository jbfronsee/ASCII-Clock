#ifndef TUI_H
#define TUI_H

#include <string>
#include <vector>
#include <optional>
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
      const std::optional<int> color = std::nullopt
    );

    void DisplayMessages(
      const std::vector<std::string>& message,
      const int add_x,
      const int add_y,
      const std::optional<int> color = std::nullopt
    );

    // Refresh and dump contents to screen
    void Refresh();
};

#endif /* TUI_H */
