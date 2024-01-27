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
        (*_data)[key] = std::make_unique<StringData>(value);
    }
}

std::shared_ptr<ModuleTab> MemoryModule::getData() const {
    return _data;
}

std::string const& MemoryModule::getName() const {
    return _name;
}


void MemoryModule::subscribe(std::string const& name) {
}

void MemoryModule::unsubscribe(std::string const& name) {
}
}
