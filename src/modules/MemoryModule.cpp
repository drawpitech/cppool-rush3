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
        std::string value;
        iss >> key >> value;
        key.pop_back();
        _data[key] = std::make_unique<StringData>(value);
    }
}

DataTab& MemoryModule::getData() {
    return _data;
}

void MemoryModule::subscribe(std::string const& name) {
}

void MemoryModule::unsubscribe(std::string const& name) {
}
}
