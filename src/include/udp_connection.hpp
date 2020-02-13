/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type udp_connection
*/

#include "Boost.hpp"
#include "commucication_struct.hpp"
#include <vector>
#include <map>

#ifndef NEWUDP_CONNECTION_HPP
#define NEWUDP_CONNECTION_HPP

namespace rtype {

class udp_connection : public boost::enable_shared_from_this<udp_connection> {

    public:

        typedef boost::shared_ptr<udp_connection> pointer;
        static pointer create(boost::asio::io_service& io_service, std::string ip, int port)
        {
            return pointer(new udp_connection(io_service, ip, port));
        }
        static pointer create(boost::asio::io_service& io_service, int port)
        {
            return pointer(new udp_connection(io_service, port));
        }

        std::map<boost::asio::ip::udp::endpoint, instruction_t> *_ref;
        std::vector<instruction_t> *_refv;
        int _port;

        udp_connection(boost::asio::io_service& io_service, std::string ip, int port);
        udp_connection(boost::asio::io_service& io_service, int port);
        ~udp_connection();

        void send_to(instruction_t bsend, std::string ip, int port);
        void receive_from();

        void handle_send_to(const boost::system::error_code& error, size_t bytes_sent);
        void handle_receive_from(const boost::system::error_code& error, size_t bytes_sent);

    private:

        int _type;
        boost::asio::ip::udp::socket _socket;

        boost::asio::io_service *_io;
        instruction_t _buffer;
        boost::asio::ip::udp::endpoint _receive;
        boost::asio::ip::udp::endpoint _send;
        boost::asio::ip::udp::endpoint _remote;
};


}

#endif //NEWUDP_CONNECTION_HPP