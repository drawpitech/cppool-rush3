/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** ProcessorModule.cpp
*/

#include "modules/ProcessorModule.hpp"

#include <algorithm>
#include <iostream>

namespace Krell {
ProcessorModule::ProcessorModule(std::string path)
    : AModule(path) {
}

std::shared_ptr<ModuleTab> ProcessorModule::getData() const {
    return _data;
}

void ProcessorModule::subscribe(const std::string& name) {
}

void ProcessorModule::unsubscribe(const std::string& name) {
}

std::string const& ProcessorModule::getName() const {
    return _name;
}

void ProcessorModule::update() {
    AModule::update();
    std::string line;
    std::getline(_stream, line);
    while (std::getline(_stream, line)) {
        std::istringstream iss(line);
        std::string key{};
        std::string value{};
        std::getline(iss, key, ':');
        std::getline(iss, value);
        if (key == "processor") {
            break;
        }
        (*_data)[key] = std::make_unique<StringData>(value);
    }
}

void ProcessorModule::log() const
{
    for (auto& [key, data] : *_data)
        std::clog << key << ": " << data->str() << "\n";
}
} // Krell
