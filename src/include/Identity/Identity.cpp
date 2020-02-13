/*
** EPITECH PROJECT, 2019
** r-type_2019
** File description:
** R-type Identity
*/

#include "Identity.hpp"

rtype::Identity::Identity()
{
}

rtype::Identity::~Identity()
{
}

int rtype::Identity::getInt(const std::string name)
{
    std::map<std::string, int>::iterator it;

    it = _currentInt.find(name);
    if (it == _currentInt.end())
        return (-1);
    return (it->second);
}

std::string rtype::Identity::getString(const std::string name)
{
    std::map<std::string, std::string>::iterator it;

    it = _currentString.find(name);
    if (it == _currentString.end())
        return ("unknown");
    return (it->second);
}

int rtype::Identity::pushInt(const std::string name, int value)
{
    std::map<std::string, int>::iterator it;

    it = _currentInt.find(name);
    if (it != _currentInt.end())
        return (-1);
    if (value < 0)
        return (-1);
    _currentInt.insert(std::map<std::string, int>::value_type(name, value));
    return (0);
}

int rtype::Identity::pushString(const std::string name, const std::string value)
{
    std::map<std::string, std::string>::iterator it;

    it = _currentString.find(name);
    if (it != _currentString.end())
        return (-1);
    if (value != "unknown")
        return (-1);
    _currentString.insert(std::map<std::string, std::string>::value_type(name, value));
    return (0);
}

int rtype::Identity::setInt(const std::string name, int value)
{
    std::map<std::string, int>::iterator it;

    it = _currentInt.find(name);
    if (it == _currentInt.end())
        return (-1);
    it->second = value;
    return (0);
}

int rtype::Identity::setString(const std::string name, const std::string value)
{
    std::map<std::string, std::string>::iterator it;

    it = _currentString.find(name);
    if (it == _currentString.end())
        return (-1);
    it->second = value;
    return (0);
}