/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibNcurses
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include <string>
    #include <iostream>
    #include <ncurses.h>
    #include "../../includes/IDisplayModule.hpp"

static const int BASE_X = 2;
static const int BASE_Y = 3;

static const std::string FONT_PATH = "lib/graphical/font/ARCADE_N.TTF";
static const std::string WINDOW_TITLE = "Arcade Ncurses";

namespace arcade
{
    class libNcurses : virtual public arcade::IDisplayModule{
        public:
            libNcurses();
            ~libNcurses() {};
            void init(const std::unordered_map<std::string, Color> pattern) override;
            void stop() override;
            void game(const std::string gameName) override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() const override;
            void setKey(arcade::KeyPressed newValue) override {};
            void changeColor(const std::unordered_map<std::string, Color> patternMap) override {};
            std::string getPlayerName() const override;
        private:
            WINDOW *win;
            int x;
            int y;
            bool keyPressed;
            int quit;
            std::map<std::string, arcade::Color> charMap;
            std::string _gameName;
            std::string _playerName;
    
            void pickColor(const std::unordered_map<std::string, Color> patternMap);
            void color_remove(void);
            void checkTwoChar(std::size_t j, std::string str);
    };
};

extern "C" {
    arcade::IDisplayModule *entryPoint() {
        return (new arcade::libNcurses);
    }
}

#endif /* !SFML_HPP_ */
