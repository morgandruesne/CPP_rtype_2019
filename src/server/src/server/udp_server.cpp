/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type udp_server
*/

#include "../../include/server/udp_server.hpp"

rtype::udp_server::udp_server(boost::asio::io_service& io_service, int port)
{
    ptr = rtype::udp_connection::create(io_service, port);
    ptr->_ref = &_current;
}

rtype::udp_server::~udp_server()
{
}

void rtype::udp_server::show_current() const
{
    /*std::cout << "VECTOR COMMAND CONTENT :";
    for (unsigned int i = 0; i < _current.size(); i++)
        std::cout << "  -  " << _current[i]._type;*/
}

int rtype::udp_server::get_nb_player(boost::asio::ip::udp::endpoint ip)
{
    int i = 0;

    for (unsigned int e = 0; e < _ips.size(); e++) {
        // std::cout << ip.address().to_string() << std::endl;
        // std::cout << _ips[e].address().to_string() << std::endl;
        if (ip.address().to_string() == _ips[e].address().to_string())
            return (i);
        i++;
    }
    return (-1);
}
