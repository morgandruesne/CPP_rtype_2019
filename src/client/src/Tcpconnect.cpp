/*
** EPITECH PROJECT, 2019
** cpp_rtype_2019
** File description:
** interface
*/

#include "../../include/commucication_struct.hpp"
#include "../include/interface.hpp"
#include <cstring>

void TcpStart(InterfaceCore   *core, instruction_t t, rtype::tcp_client &client) {
    static int i = 0;

    if (i == 0) {
        t._type = M_GC;
        std::memset(t._txt, 0, 20);
        client.ptr->write(t);
        i = 1;
    }
}

void TcpEntry(InterfaceCore   *core, int value)
{
    instruction_t t;
    static boost::asio::io_service io_service;
    static boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(core->ip), 7171);
    static rtype::tcp_client client(io_service, endpoint);

    if (core->tcpEntry == false) {
        client._io.run();
        core->tcpEntry = true;
    }
    client._io.poll();
    client.ptr->read();
    if (client.get_current().size() > 0) {
        if (client.get_current()[0]._type == M_PORT) {
            core->port = client.get_current()[0]._code;
        }
        client.get_current().erase(client.get_current().begin());
    }
    if (value == 1 && core->port == -1)
        TcpStart(core, t, client);
}
