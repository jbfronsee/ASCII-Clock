#ifndef TUI_H
#define TUI_H
#include <string>

class TUI
{
  private:

  public:
    TUI();
    ~TUI();

    void DisplayMessageAt(const std::string& message, int x, int y);
};

#endif /* TUI_H */
