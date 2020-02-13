/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type game_engine
*/


#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include "../GameEngine/game_engine.hpp"


namespace rtype {
    class Room {
        public:
            Room(int idx);
            ~Room();
            void add_player();
            void setup_players();
            float *move_player(int idx, int code);
            void check_enemies(int timer, rtype::udp_server &server);
            int player_shoot(int idx, int code, int *pos);
            float *move_player_projectile(int idx, int mv);
            void move_all_projectiles(int timer, rtype::udp_server &server);
            void move_all_enemies(int timer, rtype::udp_server &server);
            void check_collides(rtype::udp_server &server);
            int is_end(rtype::udp_server &server);
            std::vector<Player> players;
        private:
            float *move_enemy(int idx, int mv);
            void create_enemy(int pos_y, int idx);
            Map map;
            std::vector<Enemy> enemies;
            std::vector<Projectile> allies_projectiles;
            std::vector<Projectile> enemies_projectiles;
    };
}

#endif //ROOM_HPP
