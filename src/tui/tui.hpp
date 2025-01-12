#ifndef TUI_H
#define TUI_H
#include <string>
#include <vector>
#include <optional>

class Tui
{
  private:

  public:
    Tui();
    ~Tui();

    int Lines() const;

    int Cols() const;

    void Clear() const;

    void Move(const int x, const int y) const;

    void DisplayMessages(
      const std::vector<std::string>& message,
      const int add_x,
      const int add_y,
      const std::optional<int> color = std::nullopt
    ) const;

    // Refresh and dump contents to screen
    void Refresh() const;
};

#endif /* TUI_H */
