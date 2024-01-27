/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** SystemInfoModule.cpp
*/

#include "modules/SystemInfoModule.hpp"

#include <pwd.h>
#include <sys/types.h>

#include <cstddef>
#include <iostream>

namespace Krell {
SystemInfoModule::SystemInfoModule(const std::string& file) : AModule{file} {}

void SystemInfoModule::update()
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

    // Hostname
    _path = "/proc/sys/kernel/hostname";
    AModule::update();
    while (std::getline(_stream, line)) {
        if (line.empty())
            continue;
        _data["hostname"] = std::make_unique<StringData>(line);
    }

    // Username
    uid_t uid = geteuid();
    struct passwd* pw = getpwuid(uid);
    if (pw != nullptr)
        _data["username"] = std::make_unique<StringData>(std::string(pw->pw_name));

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

DataTab& SystemInfoModule::getData()
{
    return _data;
}

void SystemInfoModule::subscribe(std::string const& name) {}

void SystemInfoModule::unsubscribe(std::string const& name) {}
}  // namespace Krell
