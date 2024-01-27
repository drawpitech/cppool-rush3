/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** ProcessorModule.cpp
*/

#include "modules/ProcessorModule.hpp"

namespace Krell {
ProcessorModule::ProcessorModule(const std::string& path)
    : AModule(path) {
}

DataTab& ProcessorModule::getData() {
}

void ProcessorModule::subscribe(const std::string& name) {
}

void ProcessorModule::unsubscribe(const std::string& name) {
}

void ProcessorModule::update() {
    AModule::update();

    std::string line;
    std::getline(_stream, line);
    while (std::getline(_stream, line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;
        iss >> key >> value;
        if (key == "processor") {
            break;
        }
        _data[key] = std::make_unique<StringData>(value);
    }
}
} // Krell
