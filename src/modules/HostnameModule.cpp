/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** HostnameModule.cpp
*/

#include "modules/HostnameModule.hpp"

#include <pwd.h>

#include <string>
#include <unordered_map>

#include "AModule.hpp"
#include "Utils.hpp"

namespace {
inline const std::unordered_map<std::string, std::string> RELEVANT_KEYS{
    {"hostname", "Hostname"},
    {"username", "Username"},
};
}  // namespace

namespace Krell {
HostnameModule::HostnameModule(const std::string& file) : AModule{file} {}

void HostnameModule::update()
{
    std::string line;

    // Hostname
    _path = "/proc/sys/kernel/hostname";
    AModule::update();
    while (std::getline(_stream, line))
        if (!line.empty())
            Utils::add_to_data(*_data, RELEVANT_KEYS, "hostname", line);

    // Username
    uid_t uid = geteuid();
    struct passwd* pw = getpwuid(uid);
    if (pw != nullptr)
        Utils::add_to_data(*_data, RELEVANT_KEYS, "username", pw->pw_name);
}

std::shared_ptr<ModuleTab> HostnameModule::getData() const
{
    return _data;
}

std::string const& HostnameModule::getName() const
{
    return _name;
}
}  // namespace Krell
