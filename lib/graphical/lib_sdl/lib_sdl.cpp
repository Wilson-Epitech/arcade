/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** lib_sdl
*/

#include "lib_sdl.hpp"

lib_sdl::lib_sdl()
{
    init();
}

void lib_sdl::init()
{
    window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    x = BASE_X;
    y = BASE_Y;
    square_size = 30;
    TTF_Init();
    _font = TTF_OpenFont("lib/graphical/font/ARCADE_N.TTF", 28);
}

void lib_sdl::stop()
{
    std::cout << "3 pass\n";
}

bool lib_sdl::game()
{
    SDL_RenderPresent(render);
    SDL_PollEvent(&event);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
    switch (event.type) {
        case SDL_QUIT:
            return true;
            break;
    }
    return false;
}

void lib_sdl::textDisplay(const std::string displayText, int xPos, int yPos)
{
    if (_font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }
    int text_size = 50;
    SDL_Color White = {255, 255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, displayText.c_str(), White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
    SDL_Rect Message_rect;

    Message_rect.x = xPos;
    Message_rect.y = yPos;
    Message_rect.w = (displayText.size() * text_size);
    Message_rect.h = text_size;
    SDL_RenderCopy(render, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);
}

void lib_sdl::check_two_char(std::size_t j, std::string str, SDL_Rect rect)
{
    int pass = 0;
    if (str.at(j) == str.at(j + 1) && str.at(j) == '#') {
        SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
        pass = 1;
    }
    if (str.at(j) == '8' && str.at(j + 1) == '~' && pass == 0) {
        SDL_SetRenderDrawColor(render, 25, 250, 50, 255);
        pass = 1;
    }
    if (str.at(j) == '=' && str.at(j + 1) == '=' && pass == 0) {
        SDL_SetRenderDrawColor(render, 25, 25, 255, 255);
        pass = 1;
    }
    if (str.at(j) == '<' && str.at(j + 1) == '=' && pass == 0) {
        SDL_SetRenderDrawColor(render, 25, 25, 255, 255);
        pass = 1;
    }
    if (str.at(j) == ' ' && str.at(j + 1) == ' ' && pass == 0) {
        SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
        pass = 1;
    }
    if (pass == 0) {
        SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(render, &rect);
    SDL_RenderDrawRect(render, &rect);
}

void lib_sdl::displayMap(std::array<std::string, 19> map)
{
    SDL_Rect rect;
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.size() * 2); j += 2) {
            rect.w = square_size;
            rect.h = square_size;
            rect.x = x;
            rect.y = y;
            check_two_char(j, map.at(i), rect);
            x += square_size;
        }
        x = BASE_X;
        y += square_size;
    }
    x = BASE_X;
    y = BASE_Y;
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

arcade::KeyPressed lib_sdl::getKey()
{
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    return arcade::KeyPressed::LEFT;
                    break;
                case SDLK_RIGHT:
                    return arcade::KeyPressed::RIGHT;
                    break;
                case SDLK_UP:
                    return arcade::KeyPressed::UP;
                    break;
                case SDLK_DOWN:
                    return arcade::KeyPressed::DOWN;
                    break;
                default:
                    return arcade::KeyPressed::OTHER;
                    break;
            }
    }
    return arcade::KeyPressed::OTHER;
}
