#include <algorithm>
#include <map>
#include <iostream>

#include "tui.hpp"

int Tui::Input::GetChar()
{
    return getch();
}

Tui::ColorPairs Tui::asColor(const std::string& colorStr)
{
    //std::cout << "Color: " << colorStr << std::endl;
    std::map<std::string, Tui::ColorPairs> mapping = {
        { "BLACK", Tui::ColorPairs::BLACK },
        { "RED", Tui::ColorPairs::RED },
        { "GREEN", Tui::ColorPairs::GREEN },
        { "YELLOW", Tui::ColorPairs::YELLOW },
        { "BLUE", Tui::ColorPairs::BLUE },
        { "MAGENTA", Tui::ColorPairs::MAGENTA },
        { "CYAN", Tui::ColorPairs::CYAN },
        { "WHITE", Tui::ColorPairs::WHITE }
    };

    std::string asUpper;
    std::transform(colorStr.cbegin(), colorStr.cend(), back_inserter(asUpper),
        [] (const char c) { return std::toupper(c); }
    );

    //std::cout << "Upper: " << asUpper << std::endl;

    if (mapping.contains(asUpper))
        return mapping[asUpper];
    else
        return Tui::ColorPairs::DEFAULT;
}

void Tui::Init()
{
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
    init_pair(static_cast<short>(Tui::ColorPairs::BLACK), COLOR_BLACK, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::RED), COLOR_RED, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::GREEN), COLOR_GREEN, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::YELLOW), COLOR_YELLOW, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::BLUE), COLOR_BLUE, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::MAGENTA), COLOR_MAGENTA, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::CYAN), COLOR_CYAN, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::WHITE), COLOR_WHITE, -1);
    init_pair(static_cast<short>(Tui::ColorPairs::MENU), COLOR_WHITE, COLOR_BLUE);
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
  const Tui::ColorPairs color
)
{
    if (color != Tui::ColorPairs::DEFAULT)
    {
        attron(COLOR_PAIR(static_cast<short>(color)));
    }

    mvprintw(y, x, "%s", message.c_str());

    if (color != Tui::ColorPairs::DEFAULT)
    {
        attroff(COLOR_PAIR(static_cast<short>(color)));
    }
}

void Tui::DisplayMessages(
    const std::vector<std::string>& messages,
    const int add_x,
    const int add_y,
    const Tui::ColorPairs color
)
{
    //std::cout << "color: " << std::to_string(static_cast<short>(color));
    if (color != Tui::ColorPairs::DEFAULT)
    {
        attron(COLOR_PAIR(static_cast<short>(color)));
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

    if (color != Tui::ColorPairs::DEFAULT)
    {
        attroff(COLOR_PAIR(static_cast<short>(color)));
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
