/*
** EPITECH PROJECT, 2019
** cpp_rtype_2019
** File description:
** interface
*/

#include "../../include/commucication_struct.hpp"
#include "../include/interface.hpp"
#include <cstring>

void display_parralaxes(InterfaceCore *core)
{
    core->drawThisAt(SPRITE_GRADIENT, (sf::Vector2f){0, 0});
    core->drawParralax(PARRALAX_CLOUD_5);
    core->drawParralax(PARRALAX_CLOUD_3);
    core->drawParralax(PARRALAX_SKELETON);
    core->drawParralax(PARRALAX_DESERT);
    core->drawParralax(PARRALAX_CLOUD_2);
    core->drawParralax(PARRALAX_RED_DESERT);
    core->drawParralax(PARRALAX_CLOUD_1);
    core->drawParralax(PARRALAX_CLOUD_4);
}

void display_menu(InterfaceCore   *core)
{
    if (core->scene != 0)
        return;
    static std::string phrase;
    static bool keypressed = false;
    TcpEntry(core, 0);
    if (core->event.type == sf::Event::TextEntered && keypressed == false) {
        keypressed = true;
        if (core->event.text.unicode == 8) {
            if (phrase.size() > 0)
                phrase.pop_back();
        } else
            phrase += core->event.text.unicode;
        core->port = atoi(phrase.c_str());
    }
    if (core->event.type == sf::Event::KeyReleased)
        keypressed = false;
    display_parralaxes(core);
    core->window.draw(core->lobbyBackground);
    displayTextAt(core, sf::Vector2f(100, 300), 30, phrase);
    displayBtnPlay(core);
    displayBtnQuit(core, sf::Vector2i(100, 400));
}

void display_lobby(InterfaceCore   *core)
{
    std::string playerconnect = "Player connected : ";
    static std::string number = "0";
    if (core->scene != 1)
        return;
    TcpEntry(core, 1);
    if (core->port != -1)
        UdpEntry(core);
    if (core->UdpEntry == true && core->uclient->get_current().size() > 0) {
        if (core->uclient->get_current()[0]._type == M_UDPNC) {
            number = std::to_string(core->uclient->get_current()[0]._code);
            core->nbrPlayers = core->uclient->get_current()[0]._code;
        }
        if (core->uclient->get_current()[0]._type == M_START) {
            core->acid.play();
            core->scene = 2;
            core->clientPlayer = core->uclient->get_current()[0]._code + 1;
        }
        core->uclient->get_current().erase(core->uclient->get_current().begin());
    }
    display_parralaxes(core);
    core->window.draw(core->lobbyBackground);
    displayBtnQuit(core, sf::Vector2i(0, 670));
    displayTextAt(core, sf::Vector2f(130, 220), 60, playerconnect + number);
}

void display_game(InterfaceCore   *core)
{
    if (core->scene != 2)
        return;
    display_parralaxes(core);
    core->drawProjectiles();
    for (int i = 1; i <= core->nbrPlayers; i++) {
        if (core->players[i]->isDead == true)
            continue;
        core->drawPlayer(i);
    }
    for (int i = 1; i <= core->nbrPlayers; i++)
        core->MovePlayer(i);
    core->drawEnnemies();
    UdpGame(core);
    UdpEntry(core);
}

void display_game_over(InterfaceCore *core)
{
    if (core->scene != 3)
        return;
    if (core->win == true) {
        displayTextAt(core, (sf::Vector2f){50, 50}, 60, "T'as win bogoss yessai");
        displayTextAt(core, (sf::Vector2f){50, 700}, 60, "lol");
    } else {
        displayTextAt(core, (sf::Vector2f){50, 50}, 60, "T'as loose boloss yessai");
        displayTextAt(core, (sf::Vector2f){50, 700}, 60, ":) cheh");
    }
    core->drawThisAt(SPRITE_DEGUEU, (sf::Vector2f){470, 525});
}

void displayScene(InterfaceCore   *core)
{
    display_menu(core);
    display_lobby(core);
    display_game(core);
    display_game_over(core);
}