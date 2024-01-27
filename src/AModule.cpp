/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** AModule.cpp
*/

#include <fstream>
#include <iostream>

#include "AModule.hpp"

namespace Krell {
AModule::AModule(const std::string& path)
    : _path{path} {
}

void AModule::update() {
    std::ifstream file(_path, std::ios::in);
    std::ostringstream oss;
    oss << file.rdbuf();
    _stream = std::istringstream(oss.str());

    std::clog << _stream.str() << std::endl;
}
}
