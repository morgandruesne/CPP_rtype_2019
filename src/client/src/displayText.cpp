/*
** EPITECH PROJECT, 2019
** cpp_rtype_2019
** File description:
** interface
*/

#include "../include/interface.hpp"

void displayTextAt(InterfaceCore   *core, sf::Vector2f pos, int size, sf::String str) {
    sf::Font font;
    sf::Text text;

    font.loadFromFile("../src/client/assets/font.ttf");
    text.setFont(font);
    text.setString(str);
    text.setPosition(pos);
    text.setCharacterSize(size);
    text.setColor(sf::Color::Red);
    core->window.draw(text);
}
