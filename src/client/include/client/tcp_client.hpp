/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_server
*/

#include "../../include/Connection/tcp_connection.hpp"
#include <iostream>
#include <map>
#include <vector>

#ifndef TCP_CLIENT_HPP
#define TCP_CLIENT_HPP

namespace rtype {

class tcp_client {

    public:

        typedef void (tcp_client::*ptr_func)(instruction_t t, instruction_t *);

        boost::asio::io_service _io;
        tcp_connection::pointer ptr;

        tcp_client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint);
        ~tcp_client();

        void connect(boost::asio::ip::tcp::endpoint& endpoint);
        void handle_connect(const boost::system::error_code& error);
        void handle(instruction_t t, instruction_t *);

        std::vector<instruction_t> &get_current() { return (_current); };

    private:

        //tcp_connection::pointer connection;
        //<boost::asio::io_service& m_io_service;
        std::map<itype_t, ptr_func> _funcs;
        std::vector<instruction_t> _current;

};

}

#endif //TCP_CLIENT_HPP