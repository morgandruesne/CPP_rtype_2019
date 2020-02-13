/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type main tcp_server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "../../include/udp_connection.hpp"
#include "../include/server/tcp_server.hpp"
#include "../include/server/udp_server.hpp"
#include "../include/global.hpp"
#include "../include/GameEngine/game_engine.hpp"

std::string SRC;
rtype::game_engine ENGINE("");

int main(int ac, char **av)
{
    SRC.assign(av[0], strlen(av[0]));
    rtype::game_engine tmp(SRC);
    ENGINE = tmp;

    boost::asio::io_service io_service;
    std::cout << "Server" << std::endl;

    // rtype::game_engine engine(SRC);

    std::cout << "Engine?" << std::endl;

    try {
        rtype::tcp_server server(io_service, 7171);
        server._io.run();
    } catch (...) {
        return (84);
    }
    return (0);
}
