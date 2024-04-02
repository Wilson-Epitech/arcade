/*
** ARCADE PROJECT, 2024
** test_lib
** File description:
** LibSfml
*/

#include "LibSfml.hpp"

arcade::libSfml::libSfml() : window(sf::VideoMode(1920, 1080), WINDOW_TITLE.c_str())
{
    return;
}

void arcade::libSfml::init(const std::unordered_map<std::string, Color> pattern)
{
    x = BASE_X;
    y = BASE_Y;
    squareSize = 30;
    _font.loadFromFile(FONT_PATH.c_str());
    pickColor(pattern);
    return;
}

void arcade::libSfml::changeColor(const std::unordered_map<std::string, arcade::Color> patternMap)
{
    charMap.clear();
    pickColor(patternMap);
}

sf::RectangleShape arcade::libSfml::madeRectangle(sf::Color color, float size)
{
    sf::RectangleShape rect;
    rect.setSize(getPosition(size, size));
    rect.setFillColor(color);
    return rect;
}

void arcade::libSfml::pickColor(const std::unordered_map<std::string, Color> patternMap)
{
    for (auto tt = patternMap.begin(); tt != patternMap.end(); tt++) {
        if (tt->second == arcade::BLACK) {
            charMap.insert({tt->first, madeRectangle(RGB(0,0,0), squareSize)});
        }
        if (tt->second == arcade::WHITE) {
            charMap.insert({tt->first, madeRectangle(RGB(255,255,255), squareSize / 8)});
        }
        if (tt->second == arcade::RED) {
            charMap.insert({tt->first, madeRectangle(RGB(255,0,0), squareSize)});
        }
        if (tt->second == arcade::BLUE) {
            charMap.insert({tt->first, madeRectangle(RGB(0,0,124), squareSize)});
        }
        if (tt->second == arcade::GREEN) {
            charMap.insert({tt->first, madeRectangle(RGB(0,255,0), squareSize)});
        }
        if (tt->second == arcade::YELLOW) {
            charMap.insert({tt->first, madeRectangle(RGB(255,240,0), squareSize)});
        }
        if (tt->second == arcade::GRAY) {
            charMap.insert({tt->first, madeRectangle(RGB(50,50,50), squareSize)});
        }
        if (tt->second == arcade::CYAN) {
            charMap.insert({tt->first, madeRectangle(RGB(74,86,237), squareSize / 4)});
        }
    }
}

void arcade::libSfml::stop() {
    window.close();
}

arcade::KeyPressed arcade::libSfml::getKey() const
{
    arcade::KeyPressed key = arcade::KeyPressed::OTHER;
    if (_keyClose == CLOSE_BUTTON) {
        return arcade::CLOSE_BUTTON;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) == true) {
        return arcade::KeyPressed::UP;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) == true) {
        return arcade::KeyPressed::DOWN;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) == true) {
        return arcade::KeyPressed::LEFT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) == true) {
        return arcade::KeyPressed::RIGHT;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::N) == true) {
        return arcade::KeyPressed::N;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) == true) {
        return arcade::KeyPressed::P;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) == true) {
        return arcade::KeyPressed::G;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) == true) {
        return arcade::KeyPressed::R;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::M) == true) {
        return arcade::KeyPressed::M;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) == true) {
        return arcade::KeyPressed::BACKSPACE;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) == true) {
        return arcade::KeyPressed::ENTER;
    }
    return key;
}

void arcade::libSfml::game(const std::string gameName)
{
    _gameName = gameName;
    window.pollEvent(event);
    if (event.type == sf::Event::Closed) {
        window.close();
        _keyClose = CLOSE_BUTTON;
    }
    window.clear();
}

bool arcade::libSfml::displayRoundShape(sf::RectangleShape rect, char c)
{
    sf::CircleShape cerc;
    cerc.setRadius(rect.getSize().x);
    cerc.setFillColor(rect.getFillColor());
    cerc.setPosition(rect.getPosition());
    if (c == 'o') {
        cerc.setPosition(getPosition(x + (squareSize / 2.5), y + (squareSize / 2.5)));
        window.draw(cerc);
        return true;
    }
    if (c == 'O') {
        cerc.setPosition(getPosition(x + (squareSize / 3), y + (squareSize / 3)));
        window.draw(cerc);
        return true;
    }
    if (c == 'P') {
        cerc.setRadius(rect.getSize().x / 2);
        window.draw(cerc);
        return true;
    }
    if (c == 'F') {
        cerc.setRadius(rect.getSize().x / 2);
        window.draw(cerc);
        return true;
    }
    if (c == 'M') {
        cerc.setRadius(rect.getSize().x / 2);
        window.draw(cerc);
        return true;
    }
    return false;
}

void arcade::libSfml::checkTwoChar(std::size_t j, std::string str)
{

    for (auto tt = charMap.begin(); tt != charMap.end(); tt++) {
        if (tt->first.at(0) == str.at(j)) {
            sf::RectangleShape rect = tt->second;
            rect.setPosition(getPosition(x, y));
            if (displayRoundShape(rect, str.at(j)) == true) {
                break;
            }
            window.draw(rect);
        }
    }
}

void arcade::libSfml::displayMap(std::array<std::string, 23> map, std::size_t size)
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
}

void arcade::libSfml::displayText(std::vector<std::pair<std::string, std::pair<int, int>>> textToDisplay)
{
    sf::Text txt;
    for (size_t i = 0; i < textToDisplay.size(); i++) {
        txt.setFont(_font);
        txt.setCharacterSize(25);
        txt.setFillColor(sf::Color::White);
        txt.setPosition(getPosition(textToDisplay.at(i).second.first, textToDisplay.at(i).second.second));
        txt.setString(textToDisplay.at(i).first.c_str());
        window.draw(txt);
    }
    window.display();
}

sf::Color arcade::libSfml::RGB(int r, int g, int b)
{
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    return color;
}

sf::Vector2f arcade::libSfml::getPosition(float x, float y)
{
    sf::Vector2f vector;

    vector.x = x;
    vector.y = y;
    return (vector);
}

std::string arcade::libSfml::getPlayerName() const
{
    return _playerName;
}
