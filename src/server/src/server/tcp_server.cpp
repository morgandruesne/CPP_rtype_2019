/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_server
*/

#include "../../include/server/tcp_server.hpp"
#include "../../include/server/udp_server.hpp"

void create_room(int port, int map);

rtype::tcp_server::tcp_server(boost::asio::io_service& io_service, int port) :
m_acceptor(_io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{
    (void) io_service;
    _port = port;
    funcs.insert(std::pair<itype_t, ptr_func>(M_GC, &tcp_server::m_gc));
    start_accept();
}

rtype::tcp_server::~tcp_server()
{
}

void rtype::tcp_server::start_accept()
{
    rtype::tcp_connection::pointer new_connection = rtype::tcp_connection::create(_io);

    m_acceptor.async_accept(new_connection->get_socket(),
    boost::bind(&rtype::tcp_server::handle_accept, this, new_connection,
    boost::asio::placeholders::error));
}

void rtype::tcp_server::handle_accept(rtype::tcp_connection::pointer new_connection, const boost::system::error_code& error)
{
    static int i = 1;

    if (!error)
    {
        std::cout << "Server got a client [" << i << "]" << std::endl;
        new_connection->get_Idenity().pushInt("index", i);
        new_connection->ptr = this;
        new_connection->start();
        i++;
        start_accept();
    }
}

void rtype::tcp_server::handle(rtype::tcp_connection &c, instruction_t t, instruction_t *response)
{
    std::cout << "---\n";
    std::cout << "- _type : " << t._type << std::endl;
    std::cout << "- _txt : [" << t._txt << "]" << std::endl;
    std::cout << "---\n";

    if (funcs.find(t._type) != funcs.end())
        (this->*(ptr_func)funcs[t._type])(c, t, response);
    else {
        response->_type = M_ERR;
        std::memset(response->_txt, 0, sizeof(char) * 20);
    }
}

void rtype::tcp_server::m_gc(rtype::tcp_connection &c, instruction_t t, instruction_t *response)
{
    static int port = _port;

    port += 1;
    response->_type = M_PORT;
    response->_code = port;
    response->_txt[0] = '\0';
    boost::thread th1(&create_room, port, 0);
}
