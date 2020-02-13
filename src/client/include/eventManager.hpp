/*
** EPITECH PROJECT, 2019
** CPP_rtype_2019
** File description:
** eventManager
*/

#ifndef EVENTMANAGER_HPP_
#define EVENTMANAGER_HPP_

#include "./interface.hpp"
#include <iostream>
#include <vector>

class EventManager {
    public:
        EventManager(void);
        void    manageEvents(InterfaceCore *core);
        void    movePlayer(InterfaceCore *core);
        void    moveProjectiles(InterfaceCore *core);
        void    detectIdlePlayers(InterfaceCore *core);
        void    firePlayerProjectile(InterfaceCore *core);
        bool    destroyProjectile(Projectile* projectile);
        void    animEnnemies(InterfaceCore *core);
        bool    isPlayerMoving;
    private:
        std::vector<int> eventStack;
};


#endif /* !EVENTMANAGER_HPP_ */
