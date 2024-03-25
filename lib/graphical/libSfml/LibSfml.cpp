/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibSfml
*/

#include "LibSfml.hpp"

libSfml::libSfml() : window(sf::VideoMode(1920, 1080), WINDOW_TITLE.c_str())
{
    init();
}

void libSfml::init()
{
    x = BASE_X;
    y = BASE_Y;
    squareSize = 30;
    keyPressed = false;
    _font.loadFromFile(FONT_PATH.c_str());
    
}

void libSfml::stop() {
    window.close();
}

arcade::KeyPressed libSfml::getKey()
{
    arcade::KeyPressed key = arcade::KeyPressed::OTHER;
    bool pressed = false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true) {
        key = arcade::KeyPressed::UP;
        pressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true) {
        key = arcade::KeyPressed::DOWN;
        pressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true) {
        key = arcade::KeyPressed::LEFT;
        pressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true) {
        key = arcade::KeyPressed::RIGHT;
        pressed = true;
    }
    if (!pressed) {
        keyPressed = false;
        return arcade::KeyPressed::OTHER;
    } else if (keyPressed == false) {
        keyPressed = true;
        return key;
    } else {
        return arcade::KeyPressed::OTHER;
    }
}

bool libSfml::game()
{
    window.pollEvent(event);
    window.clear();
    if (event.type == sf::Event::Closed) {
        window.close();
        return true;
    }
    return false;
}

sf::Color libSfml::checkTwoChar(std::size_t j, std::string str)
{
    if (str.at(j) == str.at(j + 1) && str.at(j) == '#') {
        return RGB(50,50,50);
    }
    if (str.at(j) == '8' && str.at(j + 1) == '~') {
        return RGB(25,250,50);
    }
    if (str.at(j) == '=' && str.at(j + 1) == '=') {
        return RGB(25,25,255);
    }
    if (str.at(j) == '<' && str.at(j + 1) == '=') {
        return RGB(25,25,255);
    }
    if (str.at(j) == ' ' && str.at(j + 1) == ' ') {
        return RGB(0,0,0);
    }
    return RGB(255,0,0);
}

void libSfml::displayMap(std::array<std::string, 19> map)
{
    sf::RectangleShape rect;
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.size() * 2); j += 2) {
            rect.setSize(getPosition(squareSize, squareSize));
            rect.setFillColor( checkTwoChar(j, map.at(i)));
            rect.setPosition(getPosition(x, y));
            window.draw(rect);
            x += squareSize;
        }
        x = BASE_X;
        y += squareSize;
    }
    x = BASE_X;
    y = BASE_Y;
    window.display();
}

void libSfml::displayText(std::vector<std::string> textToDisplay)
{
    sf::Text txt;
    int x = 50;
    int y = 10;

    for (int i = 0; i < textToDisplay.size(); i++) {
        txt.setFont(_font);
        txt.setCharacterSize(50);
        txt.setFillColor(sf::Color::White);
        txt.setPosition(getPosition(x, y));
        txt.setString(textToDisplay.at(i).c_str());
        window.draw(txt);
        x += 50;
    }
}

sf::Color libSfml::RGB(int r, int g, int b)
{
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

sf::Vector2f libSfml::getPosition(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}
