/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** OSModule.cpp
*/

#include "modules/OSModule.hpp"

#include <iostream>

namespace Krell {
OSModule::OSModule(const std::string& file) : AModule{file} {}

void OSModule::update()
{
    std::string line;

    // OS / Distribution
    _path = "/etc/os-release";
    AModule::update();
    while (std::getline(_stream, line)) {
        std::size_t index = line.find('=');
        if (index == std::string::npos)
            continue;
        std::string key = line.substr(0, index);
        std::string value = line.substr(index + 1);
        if (value.back() == '"')
            value.pop_back();  
        if (value.front() == '"')
            value.erase(0, 1);
        _data[key] = std::make_unique<StringData>(value);
    }

    // Kernel
    _path = "/proc/version";
    AModule::update();
    while (std::getline(_stream, line)) {
        if (line.empty())
            continue;
        std::string kernel = line.substr(0, line.find('('));
        _data["kernel"] = std::make_unique<StringData>(kernel);
    }

    for (auto& [key, data] : _data) {
        std::clog << key << ": " << data->str() << std::endl;
    }
}

DataTab& OSModule::getData()
{
    return _data;
}

void OSModule::subscribe(std::string const& name) {}

void OSModule::unsubscribe(std::string const& name) {}
}  // namespace Krell
