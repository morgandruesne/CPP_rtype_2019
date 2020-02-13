/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_client
*/

#include "../../include/client/tcp_client.hpp"

rtype::tcp_client::tcp_client(boost::asio::io_service& io_service, boost::asio::ip::tcp::endpoint& endpoint)
{
    (void) io_service;
    connect(endpoint);
}

rtype::tcp_client::~tcp_client() 
{
}

void rtype::tcp_client::connect(boost::asio::ip::tcp::endpoint& endpoint)
{
    ptr = tcp_connection::create(_io);
    boost::asio::ip::tcp::socket& socket = ptr->get_socket();
    socket.async_connect(endpoint,
    boost::bind(&rtype::tcp_client::handle_connect, this,
    boost::asio::placeholders::error)
    );
}

void rtype::tcp_client::handle_connect(const boost::system::error_code& error)
{
    instruction_t t;
    t._type = M_WEL;
    t._txt[0] = '\0';

    if (!error)
    {
        std::cout << "pass connect\n";
        ptr->ptr = this;
        ptr->read();
    }
}

void rtype::tcp_client::handle(instruction_t t, instruction_t *response)
{
    std::cout << "---\n";
    std::cout << "- _type : " << t._type << std::endl;
    std::cout << "- _txt : [" << t._txt << "]" << std::endl;
    std::cout << "---\n";
    _current.push_back(t);
    /*if (_funcs.size() != 0 && _funcs.find(t._type) != _funcs.end())
        (this->*(ptr_func)_funcs[t._type])(t, response);*/
}

