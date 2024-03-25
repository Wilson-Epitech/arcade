/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"

libNcurses::libNcurses()
{
    init();
}

void libNcurses::init()
{
    initscr();
    noecho();
    start_color();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    init_pair(RIEN, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_RED);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_color(COLOR_MAGENTA, 150, 150, 150);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(GRAY, COLOR_MAGENTA, COLOR_MAGENTA);
    win = newwin(500 , 500, 0, 0);
    wclear(win);
    keyPressed = false;
}

void libNcurses::stop() {
    clear();
    wclear(win);
    delwin(win);
    clear();
    endwin();
}

bool libNcurses::game()
{
    wclear(win);
    refresh();
    timeout(100);
    int c = getch();
    if (c == 'q') {
        delwin(win);
        clear();
        endwin();
        return true;
    }
    return false;
}

void libNcurses::color_remove(void) {
    wattroff(win,COLOR_PAIR(RED));
    wattroff(win,COLOR_PAIR(GREEN));
    wattroff(win,COLOR_PAIR(CYAN));
    wattroff(win,COLOR_PAIR(BLACK));
    wattroff(win,COLOR_PAIR(WHITE));
    wattroff(win,COLOR_PAIR(GRAY));
    wattron(win,COLOR_PAIR(RIEN));
}

arcade::KeyPressed libNcurses::getKey()
{
    arcade::KeyPressed key = arcade::KeyPressed::OTHER;
    timeout(100);
    int c = getch();
    if (c == KEY_UP) {
        key = arcade::KeyPressed::UP;
    }
    if (c == KEY_DOWN) {
        key = arcade::KeyPressed::DOWN;
    }
    if (c == KEY_LEFT) {
        key = arcade::KeyPressed::LEFT;
    }
    if (c == KEY_RIGHT) {
        key = arcade::KeyPressed::RIGHT;
    }
    return key;
}

void libNcurses::checkTwoChar(std::size_t j, std::string str)
{
    if (str.at(j) == '#') {
        wattron(win,COLOR_PAIR(GRAY));
        mvwprintw(win, y, x, " ");
    }
    if (str.at(j) == '8') {
        wattron(win,COLOR_PAIR(GREEN));
        mvwprintw(win, y, x, " ");
    }
    if (str.at(j) == '=' || str.at(j) == '<') {
        wattron(win,COLOR_PAIR(BLUE));
        mvwprintw(win, y, x, " ");
    }
    if (str.at(j) == ' ') {
        wattron(win,COLOR_PAIR(BLACK));
        mvwprintw(win, y, x, " ");
    }
    if (str.at(j) == '[') {
        wattron(win,COLOR_PAIR(RED));
        mvwprintw(win, y, x, " ");
    }
    if (str.at(j) == 'o') {
        wattron(win,COLOR_PAIR(RIEN));
        mvwprintw(win, y, x, "*");
    }
    if (str.at(j) == 'O') {
        wattron(win,COLOR_PAIR(CYAN));
        mvwprintw(win, y, x, "O");
    }
    if (str.at(j) == 'P') {
        wattron(win,COLOR_PAIR(YELLOW));
        mvwprintw(win, y, x, " ");
    }
    if (str.at(j) == 'M') {
        wattron(win,COLOR_PAIR(RED));
        mvwprintw(win, y, x, " ");
    }
}

void libNcurses::displayMap(std::array<std::string, 21> map, std::size_t size)
{
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.at(i).size()); j += size) {
            for (size_t k = 0; k < size; k++) {
                checkTwoChar(j, map.at(i));
                x += 1;
            }
            color_remove();
        }
        x = BASE_X;
        y += 1;
    }
    x = BASE_X;
    y = BASE_Y;
    wrefresh(win);
}

void libNcurses::displayText(std::vector<std::string> textToDisplay)
{
    wattron(win,COLOR_PAIR(RIEN));
    int x = 50;
    int y = 10;
    for (size_t i = 0; i < textToDisplay.size(); i++) {
        mvwprintw(win, (y * 0.1), (x * 0.04), "%s", textToDisplay.at(i).c_str());
        x += 50;
    }
}
