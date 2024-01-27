/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** OSModule.cpp
*/

#include "modules/OSModule.hpp"
#include "Utils.hpp"

#include <unordered_map>

namespace {
inline const std::unordered_map<std::string, std::string> RELEVANT_KEYS{
    {"NAME", "Name"},
    {"VERSION", "Version"},
    {"kernel", "Kernel"},
};
}  // namespace

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
        Utils::add_to_data(*_data, RELEVANT_KEYS, key, value);
    }

    // Kernel
    _path = "/proc/version";
    AModule::update();
    while (std::getline(_stream, line)) {
        if (line.empty())
            continue;
        std::string value = line.substr(0, line.find('(') - 1);
        Utils::add_to_data(*_data, RELEVANT_KEYS, "kernel", value);
    }
}

std::shared_ptr<ModuleTab> OSModule::getData() const
{
    return _data;
}

const std::string& OSModule::getName() const
{
    return _name;
}

void OSModule::subscribe(std::string const& name) {}

void OSModule::unsubscribe(std::string const& name) {}
}  // namespace Krell
