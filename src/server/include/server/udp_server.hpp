/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type udp_connection
*/

#include "../../../include/commucication_struct.hpp"
#include "../../../include/udp_connection.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <map>

#ifndef UDP_SERVER_HPP
#define UDP_SERVER_HPP

namespace rtype {

class udp_server {

    public:

        udp_connection::pointer ptr;

        udp_server(boost::asio::io_service& io_service, int port);
        ~udp_server();

        instruction_t &get_t() { return (_t); };
        std::vector<boost::asio::ip::udp::endpoint> &get_ips() { return (_ips); };
        std::map<boost::asio::ip::udp::endpoint, instruction_t> &get_current() { return (_current); };

        void show_current() const;
        int get_nb_player(boost::asio::ip::udp::endpoint);

    private:

        instruction_t _t;
        std::vector<boost::asio::ip::udp::endpoint> _ips;
        std::map<boost::asio::ip::udp::endpoint, instruction_t> _current;
};

}

#endif //UDP_SERVER_HPP