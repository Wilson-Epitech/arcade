/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** lib_sdl
*/

#ifndef LIB_SDL_HPP_
    #define LIB_SDL_HPP_

    #include <string>
    #include <iostream>
    #include "../IDisplayModule.hpp"
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>

#define BASE_X 30
#define BASE_Y 60

class lib_sdl : virtual public arcade::IDisplayModule{
    public:
        lib_sdl();
        ~lib_sdl() {};
        void init() override;
        void stop() override;
        bool game() override;
        void textDisplay(const std::string displayText, int xPos, int yPos) override;
        void displayMap(std::array<std::string, 19> map) override;
        arcade::KeyPressed getKey() override;
        void setKey(arcade::KeyPressed newValue) override {};
    private:
        SDL_Window* window;
        SDL_Event event;
        SDL_Renderer* render;
        float x;
        float y;
        float square_size;
        TTF_Font* _font;

        void check_two_char(std::size_t j, std::string str, SDL_Rect rect);
};

extern "C" {
    arcade::IDisplayModule *entrypoint() {
        return (new lib_sdl);
    }
}

#endif /* !LIB_SDL_HPP_ */
