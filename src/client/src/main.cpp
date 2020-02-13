/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type main tcp_client
*/

#include <iostream>
#include <SFML/Graphics/Color.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.hpp>
#include "../include/client/tcp_client.hpp"
#include "../include/client/udp_client.hpp"
#include <cstring>
#include "../../include/udp_connection.hpp"
#include "../include/interface.hpp"
#include "../include/eventManager.hpp"

int main(int ac, char **av)
{
    InterfaceCore   *core = new InterfaceCore();
    EventManager    *event = new EventManager();

    if (ac >= 2)
        core->ip = av[1];
    else
        core->ip = "127.0.0.1";
    srand(time(NULL));
    core->window.setFramerateLimit(60);
    while (core->window.isOpen()) {
        core->mousePos = sf::Mouse::getPosition(core->window);
        event->manageEvents(core);
        core->window.clear();
        displayScene(core);
        core->window.display();
    }
    return (0);
}