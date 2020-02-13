/*
** EPITECH PROJECT, 2019
** cpp_rtype_2019
** File description:
** interface
*/

#include "../../include/commucication_struct.hpp"
#include "../include/interface.hpp"
#include <cstring>

void UdpEntry(InterfaceCore   *core) {
    instruction_t t;
    static boost::asio::io_service sio_service;
    static rtype::udp_client uclient(sio_service, core->port, core->ip);

    if (core->UdpEntry == false) {
        t._type = M_UDPC;
        uclient.ptr->send_to(t, "", uclient.ptr->_port);
        uclient.ptr->receive_from();
        core->uclient = &uclient;
        core->UdpEntry = true;
    }
    sio_service.poll();
}

void UdpGame(InterfaceCore   *core) {
    if (core->UdpEntry == true && core->uclient->get_current().size() > 0) {
        if (core->uclient->get_current()[0]._type == M_MOVE) {
            core->players[core->uclient->get_current()[0]._code]->posTogo.x = core->uclient->get_current()[0].x;
            core->players[core->uclient->get_current()[0]._code]->posTogo.y = core->uclient->get_current()[0].y;
        }
        if (core->uclient->get_current()[0]._type == M_SHOOT) {
            core->camran.play();
            core->addProjectile(
                DEFAULT_ID,
                core->getTexture(TEXTURE_PROJECTILE),
                PLAYER_MISSILE,
                (sf::Vector2f){core->uclient->get_current()[0].x + 32, core->uclient->get_current()[0].y}
            );
        }
        if (core->uclient->get_current()[0]._type == E_CREATE) {
            core->addEnnemy(
                DEFAULT_ID,
                core->getTexture(TEXTURE_BIG_EYE),
                BIG_EYE,
                (sf::Vector2f){core->uclient->get_current()[0].x, core->uclient->get_current()[0].y}
            );
        }
        if (core->uclient->get_current()[0]._type == PM_MOVE) {
            core->projectiles[core->uclient->get_current()[0]._code]->setDestination((sf::Vector2f){core->uclient->get_current()[0].x, core->uclient->get_current()[0].y});
        }
        if (core->uclient->get_current()[0]._type == PM_DESTROY) {
            core->projectiles.erase(core->projectiles.begin() + core->uclient->get_current()[0]._code);
        }
        if (core->uclient->get_current()[0]._type == E_MOVE) {
            core->ennemies[core->uclient->get_current()[0]._code]->setDestination((sf::Vector2f){core->uclient->get_current()[0].x, core->uclient->get_current()[0].y});
        }
        if (core->uclient->get_current()[0]._type == E_DESTROY) {
            core->ennemies.erase(core->ennemies.begin() + core->uclient->get_current()[0]._code);
        }
        if (core->uclient->get_current()[0]._type == M_DEAD) {
            std::cout << "Mort\n";
            core->players[core->uclient->get_current()[0]._code]->isDead = true;
        }
        if (core->uclient->get_current()[0]._type == M_LOOSE) {
            core->scene = 3;
        }
        if (core->uclient->get_current()[0]._type == M_WIN) {
            core->win = true;
            core->scene = 3;
        }
        // if (core->uclient->get_current()[0]._type == M_CREATE) {
        //     //// CREATE UN NEW MOD OU FIRE
        // }
        core->uclient->get_current().erase(core->uclient->get_current().begin());
    }
}
