/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type tcp_connection
*/

#include "../../../include/Boost.hpp"
#include "../../../include/commucication_struct.hpp"
#include <iostream>

#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

namespace rtype {

class tcp_client;

class tcp_connection : public boost::enable_shared_from_this<tcp_connection> {

    public:

        typedef boost::shared_ptr<tcp_connection> pointer;

        static pointer create(boost::asio::io_service& ios)
        {
            return pointer(new tcp_connection(ios));
        }

        tcp_client *ptr;

        tcp_connection(boost::asio::io_service& io_service);
        ~tcp_connection();

        void read();
        void write(instruction_t);

        void handle_read(const boost::system::error_code& error, size_t number_bytes_read);
        void handle_write(const boost::system::error_code& error);

        boost::asio::ip::tcp::socket &get_socket() { return (_s); };

    private:

        instruction_t _t;
        boost::asio::ip::tcp::socket _s;
        boost::asio::io_service *_io;
};

}

#endif //TCP_CONNECTION_HPP