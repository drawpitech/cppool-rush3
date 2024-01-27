/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Data.cpp
*/

#include "Data.hpp"

namespace Krell {
NumberData::NumberData(const double& size, const std::string& unit)
    : _unit{unit}, _size{size} {
}

std::string NumberData::toString() const {
    return std::to_string(_size) + _unit;
}
}
