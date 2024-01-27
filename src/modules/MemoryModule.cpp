/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** MemoryModule.cpp
*/

#include "modules/MemoryModule.hpp"

namespace Krell {
MemoryModule::MemoryModule(const std::string& file)
    : AModule{file} {
}

void MemoryModule::update() {
    AModule::update();

    std::string line;
    while (std::getline(_stream, line)) {
        std::istringstream iss(line);
        std::string key;
        double value = 0;
        std::string unit;
        iss >> key >> value >> unit;
        key.pop_back();
        _data[key] = std::make_unique<NumberData>(value, unit);
    }
}

DataTab& MemoryModule::getData() {
    return _data;
}
}
