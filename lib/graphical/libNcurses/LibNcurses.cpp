/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"

arcade::libNcurses::libNcurses()
{
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    start_color();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    init_pair(RED, COLOR_RED, COLOR_RED);
    init_pair(GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLUE);
    init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
    init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
    init_color(100, 150, 150, 150);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(GRAY, 100, 100);
    win = newwin(500 , 500, 0, 0);
    wclear(win);
    keyPressed = false;
}

void arcade::libNcurses::init(std::map<std::string, Color> pattern)
{
    return;
}

void arcade::libNcurses::stop() {
    
    wclear(win);
    delwin(win);
    endwin();
}

void arcade::libNcurses::game()
{
    werase(win);
}

void arcade::libNcurses::color_remove(void) {
    wattroff(win,COLOR_PAIR(RED));
    wattroff(win,COLOR_PAIR(GREEN));
    wattroff(win,COLOR_PAIR(CYAN));
    wattroff(win,COLOR_PAIR(BLACK));
    wattroff(win,COLOR_PAIR(WHITE));
    wattroff(win,COLOR_PAIR(GRAY));
    wattron(win,COLOR_PAIR(DEFAULT));
}

arcade::KeyPressed arcade::libNcurses::getKey()
{
    arcade::KeyPressed key = arcade::KeyPressed::OTHER;
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
    if (c == 'q') {
        delwin(win);
        endwin();
        return arcade::QUITE;
    }
    return key;
}

void arcade::libNcurses::checkTwoChar(std::size_t j, std::string str)
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
        wattron(win,COLOR_PAIR(DEFAULT));
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
    if (str.at(j) == 'F') {
        wattron(win,COLOR_PAIR(BLUE));
        mvwprintw(win, y, x, " ");
    }
}

void arcade::libNcurses::displayMap(std::array<std::string, 23> map, std::size_t size)
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

void arcade::libNcurses::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    wattron(win,COLOR_PAIR(DEFAULT));
    for (size_t i = 0; i < textToDisplay.size(); i++) {
        mvwprintw(win, (textToDisplay.at(i).second.second * 0.1), (textToDisplay.at(i).second.first * 0.04), "%s", textToDisplay.at(i).first.c_str());
    }
}
