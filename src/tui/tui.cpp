#include "tui.hpp"
#include <ncurses.h>

void Tui::Init()
{
    enum ColorPairs
    {
        PAIR_BLACK = 1,
        PAIR_RED = 2,
        PAIR_GREEN = 3,
        PAIR_YELLOW = 4,
        PAIR_BLUE = 5,
        PAIR_MAGENTA = 6,
        PAIR_CYAN = 7,
        PAIR_WHITE = 8,
        PAIR_MENU = 9
    };

    initscr();
    keypad(stdscr, TRUE);
    // Don't pause for user input.
    nodelay(stdscr, TRUE);
    // Don't echo usr input.
    noecho();
    // Turn off cursor.
    curs_set(0);

    if(has_colors() == false)
    {
        endwin();
        printf("Color is not supported by terminal.");
        exit(1);
    }

    // Set up colors.
    start_color();
    use_default_colors();
    init_pair(PAIR_BLACK, COLOR_BLACK, -1);
    init_pair(PAIR_RED, COLOR_RED, -1);
    init_pair(PAIR_GREEN, COLOR_GREEN, -1);
    init_pair(PAIR_YELLOW, COLOR_YELLOW, -1);
    init_pair(PAIR_BLUE, COLOR_BLUE, -1);
    init_pair(PAIR_MAGENTA, COLOR_MAGENTA, -1);
    init_pair(PAIR_CYAN, COLOR_CYAN, -1);
    init_pair(PAIR_WHITE, COLOR_WHITE, -1);
    init_pair(PAIR_MENU, COLOR_WHITE, COLOR_BLUE);
}

int Tui::Lines()
{
  return LINES;
}

int Tui::Cols()
{
  return COLS;
}

void Tui::Clear()
{
    clear();
}

std::pair<int, int> Tui::GetXY()
{
    int y, x;
    getyx(stdscr, y, x);
    return std::pair<int, int>(x, y);
}

void Tui::Move(const int x, const int y)
{
    move(y, x);
}

void Tui::DisplayMessage(
  const int x,
  const int y,
  const std::string& message,
  const std::optional<int> color
)
{
    if (color)
    {
        attron(COLOR_PAIR(color.value()));
    }

    mvprintw(y, x, "%s", message.c_str());

    if (color)
    {
        attroff(COLOR_PAIR(color.value()));
    }
}

void Tui::DisplayMessages(
    const std::vector<std::string>& messages,
    const int add_x,
    const int add_y,
    const std::optional<int> color
)
{
    if (color)
    {
        attron(COLOR_PAIR(color.value()));
    }

    int y, x;
    getyx(stdscr, y, x);
    int i = 0;
    for(std::string message : messages)
    {
        DisplayMessage(x, y + i, message);
        i++;
    }

    Move(x + add_x, y + add_y);

    if (color)
    {
        attroff(COLOR_PAIR(color.value()));
    }
}

void Tui::Refresh()
{
    refresh();
}

void Tui::Close()
{
    endwin();
}
