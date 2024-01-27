/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Utils.cpp
*/

#include <string>

#include "Utils.hpp"

#include <iostream>

namespace Krell::Utils {
std::string ltrim(const std::string& s, const char* t)
{
    std::string str = s;
    str.erase(0, str.find_first_not_of(t));
    return str;
}

std::string rtrim(const std::string& s, const char* t)
{
    std::string str = s;
    str.erase(str.find_last_not_of(t) + 1);
    return str;
}

std::string trim(const std::string& s, const char* t)
{
    std::string str = s;
    str = ltrim(str);
    str = rtrim(str);
    return str;
}
}
