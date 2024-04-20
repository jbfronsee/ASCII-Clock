#include "tui.hpp"
#include <ncurses.h>

Tui::Tui()
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

void Tui::DisplayMessagesAndMove(const std::vector<std::string>& messages, int add_x, int add_y)
{
    int y, x;
    getyx(stdscr, y, x);
    int i = 0;
    for(std::string message : messages)
    {
       mvprintw(y + i, x, "%s", message.c_str());
       i++;
    }

    move(y + add_y, x + add_x);
}

Tui::~Tui()
{
  endwin();
}
