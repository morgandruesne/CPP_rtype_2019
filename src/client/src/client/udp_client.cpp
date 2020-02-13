/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type udp_client
*/

#include "../../include/client/udp_client.hpp"

rtype::udp_client::udp_client(boost::asio::io_service& io_service, int port, std::string ip)
{
    ptr = rtype::udp_connection::create(io_service, ip, port);
    ptr->_refv = &_current;
}

rtype::udp_client::~udp_client()
{
}