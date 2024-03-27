/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibSdl
*/

#include "LibSdl.hpp"

arcade::libSdl::libSdl()
{
    return;
}

void arcade::libSdl::init(std::map<std::string, Color> pattern)
{
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, 0);
    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    x = BASE_X;
    y = BASE_Y;
    squareSize = 30;
    TTF_Init();
    _font = TTF_OpenFont(FONT_PATH.c_str(), 28);
    oldKeyPressed = arcade::OTHER;
    pickColor(pattern);
}

SDL_Texture* arcade::libSdl::madeRectangle(int r, int g, int b)
{
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, r, g, b));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(render, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void arcade::libSdl::pickColor(std::map<std::string, arcade::Color> patternMap)
{
    for (auto tt = patternMap.begin(); tt != patternMap.end(); tt++) {
        if (tt->second == arcade::BLACK) {
            charMap.insert({tt->first, madeRectangle(0,0,0)});
        }
        if (tt->second == arcade::WHITE) {
            charMap.insert({tt->first, madeRectangle(255,255,255)});
        }
        if (tt->second == arcade::RED) {
            charMap.insert({tt->first, madeRectangle(255,0,0)});
        }
        if (tt->second == arcade::BLUE) {
            charMap.insert({tt->first, madeRectangle(0,0,124)});
        }
        if (tt->second == arcade::GREEN) {
            charMap.insert({tt->first, madeRectangle(0,255,0)});
        }
        if (tt->second == arcade::YELLOW) {
            charMap.insert({tt->first, madeRectangle(255,240,0)});
        }
        if (tt->second == arcade::GRAY) {
            charMap.insert({tt->first, madeRectangle(50,50,50)});
        }
        if (tt->second == arcade::CYAN) {
            charMap.insert({tt->first, madeRectangle(74,86,237)});
        }
    }
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
    for (auto tt = charMap.begin(); tt != charMap.end(); tt++) {
        if (tt->first.at(0) == str.at(j)) {
            if (str.at(j) == 'o') {
                rect.w = squareSize / 8;
                rect.h = squareSize / 8;
                rect.x = x + (squareSize / 2.5);
                rect.y = y + (squareSize / 2.5);
            } else if (str.at(j) == 'O') {
                rect.w = squareSize / 4;
                rect.h = squareSize / 4;
                rect.x = x + (squareSize / 3);
                rect.y = y + (squareSize / 3);
            }
            SDL_RenderCopy(render, tt->second, NULL, &rect);
            break;
        }
    }
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
    switch (event.type) {
        case SDL_QUIT:
            oldKeyPressed = arcade::QUITE;
    }
}

arcade::KeyPressed arcade::libSdl::getKey()
{
    if (oldKeyPressed != arcade::OTHER) {
        return arcade::QUITE;
    }
    
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) {
        return arcade::LEFT;
    } else if (state[SDL_SCANCODE_RIGHT]) {
        return arcade::RIGHT;
    } else if (state[SDL_SCANCODE_UP]) {
        return arcade::UP;
    } else if (state[SDL_SCANCODE_DOWN]) {
        return arcade::DOWN;
    }

    return arcade::OTHER;
}
