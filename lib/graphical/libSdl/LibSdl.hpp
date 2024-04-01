/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** libSdl
*/

#ifndef libSdl_HPP_
    #define libSdl_HPP_

    #include <string>
    #include <iostream>
    #include "../../includes/IDisplayModule.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

static const int BASE_X = 30;
static const int BASE_Y = 60;

static const std::string FONT_PATH = "lib/graphical/font/ARCADE_N.TTF";

static const std::string WINDOW_TITLE = "Arcade SDL2";

namespace arcade
{
    class libSdl : virtual public arcade::IDisplayModule{
        public:
            libSdl();
            ~libSdl() {};
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
            SDL_Window* window;
            SDL_Event event;
            SDL_Renderer* render;
            float x;
            float y;
            float squareSize;
            TTF_Font* _font;
            KeyPressed oldKeyPressed;
            std::map<std::string, SDL_Texture*> charMap;
            std::string _gameName;
            std::string _playerName;

            void pickColor(const std::unordered_map<std::string, Color> patternMap);
            void checkTwoChar(std::size_t j, std::string str);
            SDL_Texture* madeRectangle(int r, int g, int b);
    };
};

extern "C" {
    arcade::IDisplayModule *entryPoint() {
        return (new arcade::libSdl);
    }
}

#endif /* !libSdl_HPP_ */
