/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Data.cpp
*/

#include "Data.hpp"

namespace Krell {
StringData::StringData(std::string str)
    : _data{std::move(str)} {
}

std::string StringData::str() const {
    return _data;
}
}
