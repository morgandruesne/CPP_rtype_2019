/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type Identity
*/

#include <iostream>
#include <map>

#ifndef IDENTITY_HPP
#define IDENTITY_HPP

namespace rtype {

class Identity {

    public:
        Identity();
        ~Identity();

        int pushInt(const std::string, int);
        int pushString(const std::string, const std::string);

        int getInt(const std::string);
        std::string getString(const std::string);

        int setInt(const std::string, int);
        int setString(const std::string, const std::string);

    private:
        std::map<std::string, int> _currentInt;
        std::map<std::string, std::string> _currentString;
};

}

#endif //IDENTITY_HPP