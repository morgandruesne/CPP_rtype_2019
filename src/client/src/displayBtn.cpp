/*
** EPITECH PROJECT, 2019
** cpp_rtype_2019
** File description:
** interface
*/

#include "../include/interface.hpp"

void displayBtnPlay(InterfaceCore   *core) {
    if (core->mousePos.x > 100 && core->mousePos.x < 400
    && core->mousePos.y > 200 && core->mousePos.y < 320) {
        core->resizeThis(SPRITE_PLAY_HOVER, sf::Vector2f(4, 4));
        core->drawThisAt(SPRITE_PLAY_HOVER, sf::Vector2f(100, 200));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            core->camran.play();
            core->scene = 1;
        }
    } else {
        core->resizeThis(SPRITE_PLAY, sf::Vector2f(4, 4));
        core->drawThisAt(SPRITE_PLAY, sf::Vector2f(100, 200));
    }
}

void displayBtnQuit(InterfaceCore   *core, sf::Vector2i BtnPos) {
    if (core->mousePos.x > BtnPos.x && core->mousePos.x < BtnPos.x + 400
    && core->mousePos.y > BtnPos.y && core->mousePos.y < BtnPos.y + 120) {
        core->resizeThis(SPRITE_QUIT_HOVER, sf::Vector2f(4, 4));
        core->drawThisAt(SPRITE_QUIT_HOVER, sf::Vector2f(BtnPos.x, BtnPos.y));
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (core->scene == 0)
                core->window.close();
            if (core->scene == 1) {
                core->camran.play();
                core->scene = 0;
            }
        }
    } else {
        core->resizeThis(SPRITE_QUIT, sf::Vector2f(4, 4));
        core->drawThisAt(SPRITE_QUIT, sf::Vector2f(BtnPos.x, BtnPos.y));
    }
}
