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

void libSfml::checkTwoChar(std::size_t j, std::string str)
{
    sf::RectangleShape rect;
    rect.setSize(getPosition(squareSize, squareSize));
    rect.setPosition(getPosition(x, y));
    rect.setFillColor(RGB(0,0,0));
    sf::CircleShape cerc;
    if (str.at(j) == '#') {
        rect.setFillColor(RGB(50,50,50));
    }
    if (str.at(j) == '8') {
        rect.setFillColor(RGB(25,250,50));
    }
    if (str.at(j) == '=' || str.at(j) == '<') {
        rect.setFillColor(RGB(25,25,255));
    }
    if (str.at(j) == ' ') {
        rect.setFillColor(RGB(0,0,0));
    }
    if (str.at(j) == '[') {
        rect.setFillColor(RGB(255,0,0));
    }
    if (str.at(j) == 'o') {
        cerc.setRadius(squareSize / 8);
        cerc.setFillColor(RGB(255,255,255));
        cerc.setPosition(getPosition(x + (squareSize / 2.5), y + (squareSize / 2.5)));
    }
    if (str.at(j) == 'O') {
        cerc.setRadius(squareSize / 4);
        cerc.setFillColor(RGB(74,86,237));
        cerc.setPosition(getPosition(x + (squareSize / 4), y + (squareSize / 4)));
    }
    if (str.at(j) == 'P') {
        cerc.setRadius(squareSize / 2);
        cerc.setFillColor(RGB(255,240,0));
        cerc.setPosition(getPosition(x, y));
    }
    if (str.at(j) == 'M') {
        cerc.setRadius(squareSize / 2);
        cerc.setFillColor(RGB(255,0,124));
        cerc.setPosition(getPosition(x, y));
    }
    window.draw(rect);
    window.draw(cerc);
}

void libSfml::displayMap(std::array<std::string, 21> map, std::size_t size)
{
    sf::RectangleShape rect;
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
    window.display();
}

void libSfml::displayText(std::vector<std::string> textToDisplay)
{
    sf::Text txt;
    int x = 50;
    int y = 10;

    for (size_t i = 0; i < textToDisplay.size(); i++) {
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
