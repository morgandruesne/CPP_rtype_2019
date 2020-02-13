/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** eventManager
*/

#include "../include/interface.hpp"
#include "../include/eventManager.hpp"

EventManager::EventManager(void) {
    this->eventStack.push_back(0);
    this->eventStack.push_back(2);
    this->isPlayerMoving = false;
}

void    EventManager::detectIdlePlayers(InterfaceCore *core)
{
    for (int i = 0; i < core->nbrPlayers; i++) {
        if (core->players[i]->state.id_animation == ANIM_UP && !sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            core->players[i]->setState(ANIM_IDLE);
        if (core->players[i]->state.id_animation == ANIM_DOWN && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            core->players[i]->setState(ANIM_IDLE);
        if (core->players[i]->state.id_animation == ANIM_LEFT && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            core->players[i]->setState(ANIM_IDLE);
        if (core->players[i]->state.id_animation == ANIM_RIGHT && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            core->players[i]->setState(ANIM_IDLE);
    }
}

void    EventManager::movePlayer(InterfaceCore *core) {
    instruction_t t;

    if (core->scene != 2 || core->clock.getElapsedTime().asMilliseconds() < 30)
        return;
    this->detectIdlePlayers(core);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        t._type = M_MOVE;
        t._code = 0;
        core->uclient->ptr->send_to(t, "", core->uclient->ptr->_port);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        t._type = M_MOVE;
        t._code = 2;
        core->uclient->ptr->send_to(t, "", core->uclient->ptr->_port);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        t._type = M_MOVE;
        t._code = 1;
        core->uclient->ptr->send_to(t, "", core->uclient->ptr->_port);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        t._type = M_MOVE;
        t._code = 3;
        core->uclient->ptr->send_to(t, "", core->uclient->ptr->_port);
    }
    core->clock.restart();
}

void    EventManager::moveProjectiles(InterfaceCore *core) {
    for (int i = 0; i < core->projectiles.size(); i++) {
        core->projectiles[i]->movePlayerMissile();
        core->projectiles[i]->moveBigEyeMissile();
        // if (this->destroyProjectile(core->projectiles[i]) == true) {
        //     core->projectiles.erase(core->projectiles.begin() + i);
        // }
    }
}

void    EventManager::firePlayerProjectile(InterfaceCore *core) {
    sf::Vector2f    position = core->players[core->clientPlayer - 1]->player->getPosition();
    instruction_t t;

    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || core->fireDelay.getElapsedTime().asMilliseconds() < PLAYER_FIRE_DELAY)
        return;
    t._type = M_SHOOT;
    t._code = 0;
    t.x = position.x;
    t.y = position.y;
    core->uclient->ptr->send_to(t, "", core->uclient->ptr->_port);
    core->fireDelay.restart();
}

bool    EventManager::destroyProjectile(Projectile* projectile) {
    sf::Vector2f    position = projectile->projectile->getPosition();

    if (position.x < 0 || position.x > 1024 || position.y < 0 || position.y > 800)
        return (true);
    return (false);
}

void    EventManager::animEnnemies(InterfaceCore *core)
{
    for (int i = 0; i < core->ennemies.size(); i++) {
        core->ennemies[i]->animIdleBigEye();
    }
}

void    EventManager::manageEvents(InterfaceCore *core) {
    if (core->scene == 3) {
        core->animGameOver();
    }
    if (core->scene == 2) {
        this->movePlayer(core);
        this->firePlayerProjectile(core);
        this->moveProjectiles(core);
        this->animEnnemies(core);
    }
    while (core->window.pollEvent(core->event)) {
        if (core->event.type == sf::Event::Closed)
            core->window.close();
        for (auto i = eventStack.begin(); i != eventStack.end(); ++i) {
            eventStack.erase(i);
            i--;
        }
    }
}
