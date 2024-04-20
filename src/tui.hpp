#ifndef TUI_H
#define TUI_H
#include <string>
#include <vector>

class Tui
{
  private:

  public:
    Tui();
    ~Tui();

    void DisplayMessagesAndMove(const std::vector<std::string>& message, int add_x, int add_y) const;
};

#endif /* TUI_H */
