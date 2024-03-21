/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** lib_sfml
*/

#include "lib_sfml.hpp"

lib_sfml::lib_sfml() : window(sf::VideoMode(1920, 1080), "SFML Window")
{
    init();
}

void lib_sfml::init()
{
    x = BASE_X;
    y = BASE_Y;
    square_size = 30;
    key_pressed = false;
    _font.loadFromFile("font/ARCADE_N.TTF");
}

void lib_sfml::stop() {
    std::cout << "3 pass\n";
}

arcade::KeyPressed lib_sfml::getKey()
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
        key_pressed = false;
        return arcade::KeyPressed::OTHER;
    } else if (key_pressed == false) {
        key_pressed = true;
        return key;
    } else {
        return arcade::KeyPressed::OTHER;
    }
}

bool lib_sfml::game()
{
    window.pollEvent(event);
    window.clear();
    if (event.type == sf::Event::Closed) {
        window.close();
        return true;
    }
    return false;
}

sf::Color lib_sfml::check_two_char(std::size_t j, std::string str)
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

void lib_sfml::displayMap(std::array<std::string, 19> map)
{
    sf::RectangleShape rect;
    for (std::size_t i = 0; i < map.size(); i++) {
        for (std::size_t j = 0; j < (map.size() * 2); j += 2) {
            rect.setSize(get_position(square_size, square_size));
            rect.setFillColor( check_two_char(j, map.at(i)));
            rect.setPosition(get_position(x, y));
            window.draw(rect);
            x += square_size;
        }
        x = BASE_X;
        y += square_size;
    }
    x = BASE_X;
    y = BASE_Y;
    window.display();
}

void lib_sfml::textDisplay(const std::string displayText, int xPos, int yPos)
{
    sf::Text txt;

    txt.setFont(_font);
    txt.setCharacterSize(50);
    txt.setFillColor(sf::Color::White);
    txt.setPosition(get_position(xPos, yPos));
    txt.setString(displayText.c_str());
    window.draw(txt);
}

sf::Color lib_sfml::RGB(int r, int g, int b)
{
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

sf::Vector2f lib_sfml::get_position(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}
