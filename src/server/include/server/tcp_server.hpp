/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_connection
*/

#include "../../include/Connection/tcp_connection.hpp"
#include <iostream>
#include <map>

#ifndef TCP_SERVER_HPP
#define TCP_SERVER_HPP

namespace rtype {

class tcp_server {

    typedef void (tcp_server::*ptr_func)(rtype::tcp_connection &, instruction_t, instruction_t *);

    public:

        boost::asio::io_service _io;

        tcp_server(boost::asio::io_service& io_service, int port);
        ~tcp_server();

        void start_accept();
        void handle_accept(rtype::tcp_connection::pointer new_connection, const boost::system::error_code& error);
        void handle(rtype::tcp_connection &, instruction_t, instruction_t *);

        void m_gc(rtype::tcp_connection &, instruction_t, instruction_t *);

    private:

        int _port;
        boost::asio::ip::tcp::acceptor m_acceptor;
        std::map<itype_t, ptr_func> funcs;
};

}

#endif //TCP_SERVER_HPP