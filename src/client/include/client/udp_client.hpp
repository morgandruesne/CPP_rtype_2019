/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type udp_client
*/

#include "../../../include/udp_connection.hpp"
#include <iostream>
#include <map>

#ifndef UDP_CLIENT_HPP
#define UDP_CLIENT_HPP

namespace rtype {

class udp_client {

    public:

        udp_connection::pointer ptr;

        udp_client(boost::asio::io_service& io_service, int port, std::string ip);
        ~udp_client();

        instruction_t &get_t() { return (_t); };
        std::vector<instruction_t> &get_current() { return (_current); };

    private:

        instruction_t _t;
        std::vector<instruction_t> _current;
};

}

#endif //UDP_CLIENT_HPP