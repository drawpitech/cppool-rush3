/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** MemoryModule.cpp
*/

#include <string>
#include <unordered_map>
#include <sstream>
#include <memory>

#include "modules/MemoryModule.hpp"
#include "Utils.hpp"
#include "Data.hpp"
#include "AModule.hpp"
#include "data/GraphData.hpp"

namespace {
inline const std::unordered_map<std::string, std::string> relevantKeys{
    {"Active", "Active"}, {"Cached", "Cached"}, {"Inactive", "Inactive"},
    {"MemFree", "Free"}, {"MemTotal", "Total"}, {"MemAvailable", "Available"}
};
}

namespace Krell {
MemoryModule::MemoryModule(const std::string& file)
    : AModule{file}
{
}

void MemoryModule::update()
{
    AModule::update();
    std::string line;
    while (std::getline(_stream, line)) {
        std::istringstream iss(line);
        std::string key;
        std::string value;
        std::getline(iss, key, ':');
        key = Utils::trim(key);
        std::getline(iss, value);
        value = Utils::trim(value);
        if (relevantKeys.contains(key)) {
            (*_data)[relevantKeys.at(key)] = std::make_unique<
                StringData>(value);
        }
    }
}

std::shared_ptr<ModuleTab> MemoryModule::getData() const
{
    return _data;
}

std::string const& MemoryModule::getName() const
{
    return _name;
}
} // namespace Krell
