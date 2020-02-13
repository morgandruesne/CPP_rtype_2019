/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type udp_connection
*/

#include "udp_connection.hpp"
#include <iostream>

rtype::udp_connection::udp_connection(boost::asio::io_service& io_service, int port) :
_socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port))
{
    _type = 0;
    _port = port;
    _io = &io_service;
}

rtype::udp_connection::udp_connection(boost::asio::io_service& io_service, std::string ip, int port) :
_socket(io_service), _send(boost::asio::ip::address::from_string(ip), port)
{
    _type = 1;
    _port = port;
    _io = &io_service;
    _socket.open(boost::asio::ip::udp::v4());
}

rtype::udp_connection::~udp_connection()
{
    _socket.close();
}

void rtype::udp_connection::send_to(instruction_t bsend, std::string ip, int port)
{
    _io->reset();
    if (_type == 0) {
        // std::cout << "send server\n";
        _socket.async_send_to(boost::asio::buffer(&bsend, sizeof(bsend)),
        boost::asio::ip::udp::endpoint(boost::asio::ip::address::from_string(ip), port),
        boost::bind(&udp_connection::handle_send_to, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    } else {
        // std::cout << "send client\n";
        _socket.async_send_to(boost::asio::buffer(&bsend, sizeof(bsend)),
        _send,
        boost::bind(&udp_connection::handle_send_to, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }
    _io->poll();
}

void rtype::udp_connection::receive_from()
{
     _io->reset();
    if (_type == 0) {
        // std::cout << "receive server\n";
        _socket.async_receive_from(boost::asio::buffer(&_buffer, sizeof(_buffer)),
        _remote,
        boost::bind(&udp_connection::handle_receive_from, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    } else {
        // std::cout << "receive client\n";
        _socket.async_receive_from(boost::asio::buffer(&_buffer, sizeof(_buffer)),
        _receive,
        boost::bind(&udp_connection::handle_receive_from, shared_from_this(),
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
    }
    _io->poll();
}

void rtype::udp_connection::handle_send_to(const boost::system::error_code& error, size_t bytes_sent)
{
    // std::cout << "handle send\n";
    if (error) {
        std::cout << error.message() << std::endl;
        return;
    }
}

void rtype::udp_connection::handle_receive_from(const boost::system::error_code& error, size_t bytes_sent)
{
    // std::cout << "handle read\n";
    if (error) {
        std::cout << error.message() << std::endl;
    } else {
        if (_type == 0)
            _ref->insert(std::pair<boost::asio::ip::udp::endpoint, instruction_t>(_remote, _buffer));
        else {
            // std::cout << _buffer._type << std::endl;
            _refv->push_back(_buffer);
        }

    }
    receive_from();
}
