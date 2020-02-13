/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_connection
*/

#include "../../../include/commucication_struct.hpp"
#include "../../include/client/tcp_client.hpp"

rtype::tcp_connection::tcp_connection(boost::asio::io_service& io_service) : _s(io_service)
{
    _io = &io_service;
}

rtype::tcp_connection::~tcp_connection()
{
}

void rtype::tcp_connection::write(instruction_t m)
{
    boost::asio::async_write(_s, boost::asio::buffer(&m, sizeof(m)),
    boost::bind(&tcp_connection::handle_write, shared_from_this(),
    boost::asio::placeholders::error)
    );
    _io->reset();
}

void rtype::tcp_connection::read()
{
    boost::asio::async_read(_s, boost::asio::buffer(&_t, sizeof(instruction_t)),
    boost::asio::transfer_at_least(sizeof(_t)),
    boost::bind(&tcp_connection::handle_read, shared_from_this(),
    boost::asio::placeholders::error,
    boost::asio::placeholders::bytes_transferred));
    _io->reset();
}

void rtype::tcp_connection::handle_write(const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "Client wrote a message to the server" << std::endl;
    } else {
        std::cout << error.message() << std::endl;
    }
}

void rtype::tcp_connection::handle_read(const boost::system::error_code& error, size_t number_bytes_read)
{
    if (!error) {
        ptr->handle(_t, NULL);
        return;
    }
    std::cout << "Client error read\n";
}