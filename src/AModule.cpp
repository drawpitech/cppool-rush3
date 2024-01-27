/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** AModule.cpp
*/

#include "AModule.hpp"

#include <fstream>
#include <iostream>

namespace Krell {
AModule::AModule(const std::string& path) : _path{path} {}

void AModule::update()
{
    std::ifstream file(_path, std::ios::in);
    std::ostringstream oss;
    oss << file.rdbuf();
    _stream = std::istringstream(oss.str());
}

void AModule::log() const
{
    for (auto& [key, data] : *getData())
        std::clog << key << ": " << data->str() << "\n";
}
}  // namespace Krell
