/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibSdl
*/

#include "LibSdl.hpp"

arcade::libSdl::libSdl()
{
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    x = BASE_X;
    y = BASE_Y;
    squareSize = 30;
    TTF_Init();
    _font = TTF_OpenFont(FONT_PATH.c_str(), 28);
}

void arcade::libSdl::init(std::map<std::string, Color> pattern)
{
    return;
}

void arcade::libSdl::stop()
{
    SDL_DestroyRenderer(render);
    SDL_DestroyWindow(window);
}

void arcade::libSdl::game()
{
    SDL_RenderPresent(render);
    SDL_PollEvent(&event);
    SDL_RenderClear(render);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

void arcade::libSdl::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    if (_font == NULL) {
        fprintf(stderr, "error: font not found\n");
        exit(84);
    }
    int text_size = 25;
    SDL_Color White = {255, 255, 255, 255};
    for (size_t i = 0; i < textToDisplay.size(); i++) {
        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(_font, textToDisplay.at(i).first.c_str(), White); 
        SDL_Texture* Message = SDL_CreateTextureFromSurface(render, surfaceMessage);
        SDL_Rect Message_rect;

        Message_rect.x = textToDisplay.at(i).second.first;
        Message_rect.y = textToDisplay.at(i).second.second;
        Message_rect.w = (textToDisplay.at(i).first.size() * text_size);
        Message_rect.h = text_size;
        SDL_RenderCopy(render, Message, NULL, &Message_rect);
        SDL_DestroyTexture(Message);
        SDL_FreeSurface(surfaceMessage);
    }
}

void arcade::libSdl::checkTwoChar(std::size_t j, std::string str)
{
    SDL_Rect rect;
    rect.w = squareSize;
    rect.h = squareSize;
    rect.x = x;
    rect.y = y;
    if (str.at(j) == '#') {
        SDL_SetRenderDrawColor(render, 50, 50, 50, 255);
    }
    if (str.at(j) == '8') {
        SDL_SetRenderDrawColor(render, 25,250,50, 255);
    }
    if (str.at(j) == '=' || str.at(j) == '<') {
        SDL_SetRenderDrawColor(render, 25,25,255, 255);
    }
    if (str.at(j) == ' ') {
        SDL_SetRenderDrawColor(render, 0,0,0, 255);
    }
    if (str.at(j) == '[') {
        SDL_SetRenderDrawColor(render, 255,0,0, 255);
    }
    if (str.at(j) == 'o') {
        rect.w = squareSize / 8;
        rect.h = squareSize / 8;
        rect.x = x + (squareSize / 2.5);
        rect.y = y + (squareSize / 2.5);
        SDL_SetRenderDrawColor(render, 255,255,255, 255);
    }
    if (str.at(j) == 'O') {
        rect.w = squareSize / 4;
        rect.h = squareSize / 4;
        rect.x = x + (squareSize / 3);
        rect.y = y + (squareSize / 3);
        SDL_SetRenderDrawColor(render, 74,86,237, 255);
    }
    if (str.at(j) == 'P') {
        SDL_SetRenderDrawColor(render, 255,240,0, 255);
    }
    if (str.at(j) == 'M') {
        SDL_SetRenderDrawColor(render, 255,0,124, 255);
    }
    if (str.at(j) == 'F') {
        SDL_SetRenderDrawColor(render, 0,0,124, 255);
    }
    SDL_RenderFillRect(render, &rect);
    SDL_RenderDrawRect(render, &rect);
}


void arcade::libSdl::displayMap(std::array<std::string, 23> map, std::size_t size)
{
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.at(i).size()); j += size) {
            checkTwoChar(j, map.at(i));
            x += squareSize;
        }
        x = BASE_X;
        y += squareSize;
    }
    x = BASE_X;
    y = BASE_Y;
    SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
}

arcade::KeyPressed arcade::libSdl::getKey()
{
    switch (event.type) {
        case SDL_QUIT:
            return QUITE;
    }
    switch(event.type) {
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_LEFT:
                    return arcade::LEFT;
                    break;
                case SDLK_RIGHT:
                    return arcade::RIGHT;
                    break;
                case SDLK_UP:
                    return arcade::UP;
                    break;
                case SDLK_DOWN:
                    return arcade::DOWN;
                    break;
                default:
                    return arcade::OTHER;
                    break;
            }
    }
    return arcade::OTHER;
}
