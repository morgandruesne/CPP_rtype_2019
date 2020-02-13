/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_connection
*/

#include "../../include/server/tcp_server.hpp"
#include <cstring>

rtype::tcp_connection::tcp_connection(boost::asio::io_service& io_service) : _s(io_service)
{
}

rtype::tcp_connection::~tcp_connection()
{
}

void rtype::tcp_connection::write_simple(instruction_t s)
{
    boost::asio::async_write(_s, boost::asio::buffer(&s, sizeof(instruction_t)),
    boost::bind(&tcp_connection::handle_write_simple, shared_from_this(),
    boost::asio::placeholders::error)
    );
}

void rtype::tcp_connection::write(instruction_t s)
{
    boost::asio::async_write(_s, boost::asio::buffer(&s, sizeof(instruction_t)),
    boost::bind(&tcp_connection::handle_write, shared_from_this(),
    boost::asio::placeholders::error)
    );
}

void rtype::tcp_connection::read()
{
    boost::asio::async_read(_s, boost::asio::buffer(&_t, sizeof(instruction_t)),
    boost::bind(&tcp_connection::handle_read, shared_from_this(),
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred)
    );
}

void rtype::tcp_connection::handle_write_simple(const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "SERVER SEND PORT PACKED" << std::endl;

    } else {
        std::cout << error.message() << std::endl;
    }
}


void rtype::tcp_connection::handle_write(const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "Server wrote a message to the client." << std::endl;
        this->read();
    } else {
        std::cout << error.message() << std::endl;
    }
}

void rtype::tcp_connection::handle_read(const boost::system::error_code& error, size_t number_bytes_read)
{
    instruction_t response;

    if (!error) {
        ptr->handle(*this, _t, &response);
        this->write(response);
        return;
    }
    std::cout << error.message() << std::endl;
}

void rtype::tcp_connection::start()
{
    instruction_t t;
    t._type = M_WEL;
    std::memset(t._txt, 0, 20);
    this->write(t);
}