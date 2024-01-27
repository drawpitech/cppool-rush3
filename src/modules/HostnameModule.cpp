/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** HostnameModule.cpp
*/


#include <iostream>
#include <pwd.h>

#include "modules/HostnameModule.hpp"

namespace Krell {
HostnameModule::HostnameModule(const std::string& file)
    : AModule{file} {
}

void HostnameModule::update() {
    std::string line;

    // Hostname
    _path = "/proc/sys/kernel/hostname";
    AModule::update();
    while (std::getline(_stream, line)) {
        if (line.empty())
            continue;
        (*_data)["hostname"] = std::make_unique<StringData>(line);
    }

    // Username
    uid_t uid = geteuid();
    struct passwd* pw = getpwuid(uid);
    if (pw != nullptr)
        (*_data)["username"] = std::make_unique<StringData>(std::string(pw->pw_name));
}

void HostnameModule::log() const
{
    for (auto& [key, data] : *_data)
        std::clog << key << ": " << data->str() << "\n";
}

std::shared_ptr<ModuleTab> HostnameModule::getData() const {
    return _data;
}

std::string const& HostnameModule::getName() const {
    return _name;
}

void HostnameModule::subscribe(std::string const& name) {
}

void HostnameModule::unsubscribe(std::string const& name) {
}
} // namespace Krell
