/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibNcurses
*/

#include "LibNcurses.hpp"

arcade::libNcurses::libNcurses()
{
    return;
}

void arcade::libNcurses::init(const std::unordered_map<std::string, Color> pattern)
{
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
    start_color();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    init_pair(DEFAULT, COLOR_WHITE, COLOR_BLACK);
    win = newwin(1920 , 1080, 0, 0);
    wclear(win);
    keyPressed = false;
    pickColor(pattern);
    _gameName = "";
    x = 0;
    y = 0;
    nextChar = true;
    pressedChar = 0;
}

void arcade::libNcurses::changeColor(const std::unordered_map<std::string, arcade::Color> patternMap)
{
    charMap.clear();
    pickColor(patternMap);
}

void arcade::libNcurses::pickColor(const std::unordered_map<std::string, Color> patternMap)
{
    for (auto tt = patternMap.begin(); tt != patternMap.end(); tt++) {
        if (tt->second == arcade::BLACK) {
            init_pair(arcade::BLACK, COLOR_BLACK, COLOR_BLACK);
            charMap.insert({tt->first, arcade::BLACK});
        }
        if (tt->second == arcade::WHITE) {
            init_pair(arcade::WHITE, COLOR_WHITE, COLOR_BLACK);
            charMap.insert({tt->first, arcade::WHITE});
        }
        if (tt->second == arcade::RED) {
            init_pair(arcade::RED, COLOR_RED, COLOR_RED);
            charMap.insert({tt->first, arcade::RED});
        }
        if (tt->second == arcade::BLUE) {
            init_pair(arcade::BLUE, COLOR_BLUE, COLOR_BLUE);
            charMap.insert({tt->first, arcade::BLUE});
        }
        if (tt->second == arcade::GREEN) {
            init_pair(arcade::GREEN, COLOR_GREEN, COLOR_GREEN);
            charMap.insert({tt->first, arcade::GREEN});
        }
        if (tt->second == arcade::YELLOW) {
            init_pair(arcade::YELLOW, COLOR_YELLOW, COLOR_YELLOW);
            charMap.insert({tt->first, arcade::YELLOW});
        }
        if (tt->second == arcade::GRAY) {
            init_color(100, 150, 150, 150);
            init_pair(arcade::GRAY, 100, 100);
            charMap.insert({tt->first, arcade::GRAY});
        }
        if (tt->second == arcade::CYAN) {
            init_pair(arcade::CYAN, COLOR_CYAN, COLOR_BLACK);
            charMap.insert({tt->first, arcade::CYAN});
        }
    }
}

void arcade::libNcurses::stop() {
    
    wclear(win);
    delwin(win);
    endwin();
}

void arcade::libNcurses::game(const std::string gameName)
{
    _gameName = gameName;
    otherGetKey();
    if (_gameName.compare("menu") == 0) {
        if ((pressedChar >= 'a' && pressedChar <= 'z') ||
        (pressedChar >= 'A' && pressedChar <= 'Z') ||
        pressedChar == '_' ||
        (pressedChar >= '0' && pressedChar <= '9')) {
            _playerName.push_back(pressedChar);
        }
        if (pressedChar == KEY_BACKSPACE) {
            _playerName.pop_back();
        }
    }
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

void arcade::libNcurses::otherGetKey(void)
{
    int c = getch();
    pressedChar = c;
    if (c == KEY_UP) {
        _keyPressed = arcade::KeyPressed::UP;
        return;
    }
    if (c == KEY_DOWN) {
        _keyPressed = arcade::KeyPressed::DOWN;
        return;
    }
    if (c == KEY_LEFT) {
        _keyPressed = arcade::KeyPressed::LEFT;
        return;
    }
    if (c == KEY_RIGHT) {
        _keyPressed = arcade::KeyPressed::RIGHT;
        return;
    }
    if (c == 'g' || c == 'G') {
        _keyPressed = arcade::KeyPressed::G;
        return;
    }
    if (c == 'n' || c == 'N') {
        _keyPressed = arcade::KeyPressed::N;
        return;
    }
    if (c == 'p' || c == 'P') {
        _keyPressed = arcade::KeyPressed::P;
        return;
    }
    if (c == 'r' || c == 'R') {
        _keyPressed = arcade::KeyPressed::R;
        return;
    }
    if (c == 'm' || c == 'M') {
        _keyPressed = arcade::KeyPressed::M;
        return;
    }
    if (c == KEY_BACKSPACE) {
        _keyPressed = arcade::KeyPressed::BACKSPACE;
        return;
    }
    if (c == 10) {
        _keyPressed = arcade::KeyPressed::ENTER;
        return;
    }
    if (c == 'q' && _gameName.compare("menu") != 0) {
        _keyPressed = arcade::BACKSPACE;
    }
    if (c == 27 && _gameName.compare("menu") == 0) {
        _keyPressed = arcade::M;
    }
}

arcade::KeyPressed arcade::libNcurses::getKey() const
{
    return _keyPressed;
}

void arcade::libNcurses::setKey(arcade::KeyPressed newValue)
{
    if (_keyPressed != arcade::BACKSPACE)
        _keyPressed = newValue;
}

void arcade::libNcurses::checkTwoChar(std::size_t j, std::string str)
{
    for (auto tt = charMap.begin(); tt != charMap.end(); tt++) {
        if (tt->first.at(0) == str.at(j)) {
            wattron(win,COLOR_PAIR(tt->second));
            if (str.at(j) == 'o') {
                mvwprintw(win, y, x, "*");
            } else if (str.at(j) == 'O') {
                mvwprintw(win, y, x, "O");
            } else {
                mvwprintw(win, y, x, " ");
            }
        }
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
}

void arcade::libNcurses::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    wattron(win,COLOR_PAIR(DEFAULT));
    if (_gameName.compare("menu") == 0) {
        textToDisplay.push_back({_playerName, {10,10}});
    }
    for (size_t i = 0; i < textToDisplay.size(); i++) {
        mvwprintw(win, (textToDisplay.at(i).second.second * 0.04), (textToDisplay.at(i).second.first * 0.04), "%s", textToDisplay.at(i).first.c_str());
    }
    wrefresh(win);
}

std::string arcade::libNcurses::getPlayerName() const
{
    return _playerName;
}

