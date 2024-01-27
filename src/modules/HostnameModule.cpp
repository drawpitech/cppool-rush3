/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** HostnameModule.cpp
*/

#include "modules/HostnameModule.hpp"

#include <iostream>

namespace Krell {
HostnameModule::HostnameModule(const std::string& file) : AModule{file} {}

void HostnameModule::update()
{
    AModule::update();

    std::string line;
    while (std::getline(_stream, line)) {
        if (line.empty())
            continue;
        _data["hostname"] = std::make_unique<StringData>(line);
    }
}

DataTab& HostnameModule::getData()
{
    return _data;
}

void HostnameModule::subscribe(std::string const& name) {}

void HostnameModule::unsubscribe(std::string const& name) {}
}  // namespace Krell
