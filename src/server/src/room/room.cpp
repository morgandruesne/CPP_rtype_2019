/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type room
*/

#include "../../include/server/udp_server.hpp"
#include "../../include/GameEngine/game_engine.hpp"
#include "../../include/room/room.hpp"
#include "../../include/global.hpp"

float SCREEN_X = 1024.0;
float SCREEN_Y = 800.0;

void send_udp_packet_to(rtype::udp_server &server, instruction_t packet, int index)
{
    server.ptr->send_to(packet, server.get_ips()[index].address().to_string(), server.get_ips()[index].port());
}

void send_udp_packet_commom(rtype::udp_server &server, instruction_t packet)
{
    // std::cout << "start std common\n";
    for (unsigned int i = 0; i < server.get_ips().size(); i++) {
        // std::cout << server.get_ips()[i] << std::endl;
        // std::cout << server.ptr->_port << std::endl;
        server.ptr->send_to(packet, server.get_ips()[i].address().to_string(), server.get_ips()[i].port());
    }
}

int check_out(float *pos)
{
    if (pos[0] < 0 || pos[0] > SCREEN_X)
        return (1);
    if (pos[1] < 0 || pos[1] > SCREEN_Y)
        return (1);
    return 0;
}

void move(int code, int idx, rtype::udp_server server, rtype::Room &room)
{
    float *new_pos = room.move_player(idx, code);

    instruction_t inst;
    inst._type = M_MOVE;
    inst._code = idx;
    inst.x = new_pos[0];
    inst.y = new_pos[1];
    inst._txt[0] = '\0';
    send_udp_packet_commom(server, inst);
}

void shoot(int code, int idx, int *pos, rtype::udp_server server, rtype::Room &room)
{
    int nb = room.player_shoot(idx, code, pos);

    instruction_t inst;
    inst._type = M_SHOOT;
    inst._code = idx;
    inst.x = pos[0];
    inst.y = pos[1];
    inst._txt[0] = '\0';
    send_udp_packet_commom(server, inst);

    float *fpos = room.move_player_projectile(nb, 0);

    inst._type = PM_MOVE;
    inst._code = nb;
    inst.x = fpos[0];
    inst.y = fpos[1];
    inst._txt[0] = '\0';
    send_udp_packet_commom(server, inst);
}

void check_current_server(rtype::udp_server &server, rtype::Room &room)
{
    std::map<boost::asio::ip::udp::endpoint, instruction_t>::iterator ip;

    if (server.get_current().size() <= 0)
        return;
    ip = server.get_current().begin();
    int idx = server.get_nb_player(ip->first);
    if (room.players[idx].alive == false)
        return;
    int pos[2] = {ip->second.x, ip->second.y};
    switch (ip->second._type) {
        case M_MOVE:
            move(ip->second._code, idx, server, room);
            break;
        case M_SHOOT:
            shoot(ip->second._code, idx, pos, server, room);
            break;
        default:
            break;
    }
    server.get_current().erase(ip);
}

rtype::Room::Room(int idx) : map(ENGINE._maps[idx])
{
    // (this->players).push_back((ENGINE._players)[0]);
}

rtype::Room::~Room()
{
}

void rtype::Room::add_player()
{
    this->players.push_back((ENGINE._players)[0]);
}

void rtype::Room::setup_players()
{
    for(int i = 0; i < this->players.size(); i++) {
        float pos[2] = {70.0, float(175.0 * (i + 1.0))};
        (this->players[i]).set_pos(pos);
    }
}

float *rtype::Room::move_player(int idx, int code)
{
    float *pos = (this->players[idx]).get_pos();
    float speed = (this->players[idx]).get_speed();
    // std::cout << pos[0] << "," << pos[1] << "\n" << speed << "\n";
    switch (code) {
        case 0:
            if (pos[1] - speed > 0)
                pos[1] -= speed;
            break;
        case 1:
            if (pos[0] + speed < SCREEN_X)
                pos[0] += speed;
            break;
        case 2:
            if (pos[1] + speed < SCREEN_Y)
                pos[1] += speed;
            break;
        case 3:
            if (pos[0] - speed > 0)
                pos[0] -= speed;
            break;
    }
    return ((this->players[idx]).set_pos(pos));
}

void rtype::Room::create_enemy(int pos_y, int idx)
{
    this->enemies.push_back(ENGINE._enemies[idx]);
    int last = this->enemies.size() - 1;
    float pos[2] = {SCREEN_X, float(pos_y)};

    this->enemies[last].set_pos(pos);
}

void rtype::Room::check_enemies(int timer, rtype::udp_server &server)
{
    for (int i = 0; i < this->map.enemies.size(); i++) {
        auto tup = this->map.enemies[i];
        int t = std::get<1>(tup);
        if (t == timer) {
            int idx = std::get<0>(tup);
            int pos_y = std::get<2>(tup);
            // std::cout << "Je dois creer " << idx << " at " << pos_y << "\n";
            this->create_enemy(pos_y, idx);

            instruction_t inst;
            inst._type = E_CREATE;
            inst._code = idx;
            inst.x = SCREEN_X;
            inst.y = pos_y;
            inst._txt[0] = '\0';

            send_udp_packet_commom(server, inst);

            int last = this->enemies.size() - 1;
            float *pos = this->move_enemy(last, 0);

            inst._type = E_MOVE;
            inst._code = last;
            inst.x = pos[0];
            inst.y = pos[1];
            inst._txt[0] = '\0';

            send_udp_packet_commom(server, inst);

            this->map.enemies.erase(this->map.enemies.begin());
            i--;
        }
        if (t > timer)
            break;
    }
}

int rtype::Room::player_shoot(int idx, int code, int *pos)
{
    this->allies_projectiles.push_back(this->players[idx].get_weapon(code));

    int max = this->allies_projectiles.size() - 1;

    float fpos[2] = {float(pos[0]), float(pos[1])};
    this->allies_projectiles[max].set_pos(fpos);

    return (max);
}

float *rtype::Room::move_player_projectile(int idx, int move)
{
    float *pos = this->allies_projectiles[idx].get_pos();
    float speed = this->allies_projectiles[idx].get_speed();
    std::vector<float *> pat = this->allies_projectiles[idx].get_pattern();
    float *apply_pattern = pat[move];

    float *fut_pos = new float[2];
    fut_pos[0] = pos[0] + speed * apply_pattern[0];
    fut_pos[1] = pos[1] + speed * apply_pattern[1];
    // float fut_pos[2] = {pos[0] + speed * apply_pattern[0], pos[1] + speed * apply_pattern[1]};
    this->allies_projectiles[idx].set_pos(fut_pos);
    return (fut_pos);
}

void rtype::Room::move_all_projectiles(int timer, rtype::udp_server &server)
{
    for (int i = 0; i < this->allies_projectiles.size(); i++) {
        // float *pos = this->move_player_projectile(i, timer % this->allies_projectiles[i].get_pattern().size());
        float *pos = this->move_player_projectile(i, 0);
        if (check_out(pos) == 1) {
            this->allies_projectiles.erase(this->allies_projectiles.begin() + i);

            instruction_t inst;
            inst._type = PM_DESTROY;
            inst._code = i;
            inst.x = 0;
            inst.y = 0;
            inst._txt[0] = '\0';
            send_udp_packet_commom(server, inst);

            i--;
        } else {
            instruction_t inst;
            inst._type = PM_MOVE;
            inst._code = i;
            inst.x = pos[0];
            inst.y = pos[1];
            inst._txt[0] = '\0';

            send_udp_packet_commom(server, inst);
        }

    }
}

float *rtype::Room::move_enemy(int idx, int move)
{
    float *pos = this->enemies[idx].get_pos();
    float speed = this->enemies[idx].get_speed();
    std::vector<float *> pat = this->enemies[idx].get_pattern();
    float *apply_pattern = pat[move];
    float *fut_pos = new float[2];
    fut_pos[0] = pos[0] - speed * apply_pattern[0];
    fut_pos[1] = pos[1] - speed * apply_pattern[1];
    // float fut_pos[2] = {pos[0] + speed * apply_pattern[0], pos[1] + speed * apply_pattern[1]};
    this->enemies[idx].set_pos(fut_pos);

    return (fut_pos);
}

void rtype::Room::move_all_enemies(int timer, rtype::udp_server &server)
{
    for (int i = 0; i < this->enemies.size(); i++) {
        float *pos = this->move_enemy(i, 0);

        if (check_out(pos) == 1) {
            this->enemies.erase(this->enemies.begin() + i);

            instruction_t inst;
            inst._type = E_DESTROY;
            inst._code = i;
            inst.x = 0;
            inst.y = 0;
            inst._txt[0] = '\0';
            send_udp_packet_commom(server, inst);

            i--;
        } else {
            instruction_t inst;
            inst._type = E_MOVE;
            inst._code = i;
            inst.x = pos[0];
            inst.y = pos[1];
            inst._txt[0] = '\0';

            send_udp_packet_commom(server, inst);
        }
    }
}

int is_collide(float *box1, float *box2)
{
    if (box2[0] > box1[0] && box2[0] < box1[2] && box2[1] > box1[1] && box2[1] < box1[3])
        return (1);
    if (box2[2] > box1[0] && box2[2] < box1[2] && box2[1] > box1[1] && box2[1] < box1[3])
        return (1);
    if (box2[0] > box1[0] && box2[0] < box1[2] && box2[3] > box1[1] && box2[3] < box1[3])
        return (1);
    if (box2[2] > box1[0] && box2[2] < box1[2] && box2[3] > box1[1] && box2[3] < box1[3])
        return (1);
    return (0);
}

void rtype::Room::check_collides(rtype::udp_server &server)
{
    for (int j = 0; j < this->enemies.size(); j++) {
        float *pos = this->enemies[j].get_pos();
        float enembox[4] = {pos[0], pos[1], pos[0] + this->enemies[j].get_width(), pos[1] + this->enemies[j].get_height()};
        for (int i = 0; i < this->players.size(); i++) {
            float *ppos = this->players[i].get_pos();
            float playerbox[4] = {ppos[0], ppos[1], ppos[0] + this->players[i].get_width(), ppos[1] + this->players[i].get_height()};
            if (is_collide(enembox, playerbox) == 1) {
                int life = this->players[i].take_damage(10);
                if (life <= 0) {
                    this->players[i].alive = false;

                    instruction_t inst;
                    inst._type = M_DEAD;
                    inst._code = i;
                    inst.x = 0;
                    inst.y = 0;
                    inst._txt[0] = '\0';

                    send_udp_packet_commom(server, inst);
                }
            }
        }
        for (int i = 0; i < this->allies_projectiles.size(); i++) {
            float *ppos = this->allies_projectiles[i].get_pos();
            float playerbox[4] = {ppos[0], ppos[1], ppos[0] + this->allies_projectiles[i].get_width(), ppos[1] + this->allies_projectiles[i].get_height()};
            if (is_collide(enembox, playerbox) == 1) {
                int life = this->enemies[j].take_damage(this->allies_projectiles[i].get_damage());
                if (life <= 0) {
                    this->enemies.erase(this->enemies.begin() + j);

                    instruction_t inst;
                    inst._type = E_DESTROY;
                    inst._code = j;
                    inst.x = 0;
                    inst.y = 0;
                    inst._txt[0] = '\0';
                    send_udp_packet_commom(server, inst);

                    j--;
                }
                this->allies_projectiles.erase(this->allies_projectiles.begin() + i);

                instruction_t inst;
                inst._type = PM_DESTROY;
                inst._code = i;
                inst.x = 0;
                inst.y = 0;
                inst._txt[0] = '\0';
                send_udp_packet_commom(server, inst);

                i--;
            }
        }
    }
}

int rtype::Room::is_end(rtype::udp_server &server)
{
    int ret = 1;
    for (int i = 0; i < this->players.size(); i++) {
        if (this->players[i].alive == true) {
            ret = 0;
        }
    }
    if (ret == 1) {
        instruction_t inst;
        inst._type = M_LOOSE;
        inst._code = 0;
        inst.x = 0;
        inst.y = 0;
        inst._txt[0] = '\0';
        send_udp_packet_commom(server, inst);
        return 1;
    }
    if (this->map.enemies.size() == 0 && this->enemies.size() == 0){
        instruction_t inst;
        inst._type = M_WIN;
        inst._code = 0;
        inst.x = 0;
        inst.y = 0;
        inst._txt[0] = '\0';
        send_udp_packet_commom(server, inst);
        return 1;
    }
    return 0;
}

void send_udp_packet_player_nb(rtype::udp_server &server, instruction_t packet)
{
    // std::cout << "start std common\n";
    packet._code = 0;
    for (unsigned int i = 0; i < server.get_ips().size(); i++) {
        // std::cout << server.get_ips()[i] << std::endl;
        // std::cout << server.ptr->_port << std::endl;
        server.ptr->send_to(packet, server.get_ips()[i].address().to_string(), server.get_ips()[i].port());
        packet._code += 1;
    }
}

void create_room(int port, int map)
{
    boost::asio::io_service io_service;
    boost::system::error_code ignored_error;
    rtype::udp_server ser(io_service, port);
    std::clock_t c_start = std::clock();
    std::clock_t c_enem = std::clock();
    std::clock_t c_proj = std::clock();
    double duration;

    rtype::Room room(map);

    std::cout << room.players.size() << std::endl;


    instruction_t tr;
    tr._type = M_UDPNC;
    tr._txt[0] = '\0';

    std::cout << "udp server " << port << std::endl;
    ser.ptr->receive_from();

    while (ser.get_ips().size() < 4) {
        io_service.poll();
        if (ser.get_current().size() > 0) {
            std::cout << ser.get_current().begin()->first <<  std::endl;
            std::cout << ser.get_current().begin()->second._type <<  std::endl;
            if (ser.get_current().begin()->second._type == M_UDPC) {
                ser.get_ips().push_back(ser.get_current().begin()->first);
                room.add_player();
                tr._code = ser.get_ips().size();
                send_udp_packet_commom(ser, tr);
            }
            ser.get_current().erase(ser.get_current().begin());
        }

        duration = (std::clock() - c_start)/(double)CLOCKS_PER_SEC;
        if (duration > 5) {
            std::cout << "break\n";
            break;
        }
    }

    std::cout << room.players.size() << std::endl;

    std::cout << "Start game\n";
    tr._type = M_START;
    send_udp_packet_player_nb(ser, tr);

    room.setup_players();

    c_start = std::clock();
    c_proj = std::clock();

    unsigned long long int sec = 0;
    while (1) {
        io_service.poll();
        check_current_server(ser, room);

        duration = (std::clock() - c_start)/(double)CLOCKS_PER_SEC;
        if (duration > 1) {
            c_start = std::clock();
            sec += 1;
            room.check_enemies(sec, ser);
        }
        duration = (std::clock() - c_enem)/(double)CLOCKS_PER_SEC;
        if (duration > 0.1) {
            room.check_collides(ser);
            c_enem = std::clock();
            room.move_all_enemies(sec, ser);
        }
        duration = (std::clock() - c_proj)/(double)CLOCKS_PER_SEC;
        if (duration > 0.05) {
            c_proj = std::clock();
            room.move_all_projectiles(sec, ser);
        }
        if (room.is_end(ser) == 1)
            break;
    }
    std::cout << "End game\n";
}
