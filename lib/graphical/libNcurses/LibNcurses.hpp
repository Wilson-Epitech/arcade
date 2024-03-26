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
    #include "../../IDisplayModule.hpp"

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
            void init(std::map<std::string, Color> pattern) override;
            void stop() override;
            void game() override;
            void displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay) override;
            void displayMap(std::array<std::string, 23> map, std::size_t size) override;
            arcade::KeyPressed getKey() override;
            void setKey(arcade::KeyPressed newValue) override {};
            void pickColor(std::map<std::string, Color> patternMap) override {};
        private:
            WINDOW *win;
            enum {
                DEFAULT,
                GREEN,
                BLUE,
                RED,
                CYAN,
                BLACK,
                WHITE,
                GRAY,
                YELLOW
            };
            int x;
            int y;
            bool keyPressed;
            int quit;
    
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
