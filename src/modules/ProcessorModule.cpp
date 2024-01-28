/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** ProcessorModule.cpp
*/

#include <sstream>
#include <string>
#include <memory>
#include <unordered_map>

#include "Data.hpp"
#include "AModule.hpp"
#include "modules/ProcessorModule.hpp"
#include "Utils.hpp"

namespace {
inline const std::unordered_map<std::string, std::string> relevantKeys{
    {"model name", "Model name"}, {"cpu MHz", "CPU MHz"},
    {"cache size", "Cache size"}, {"cpu cores", "CPU cores"},
    {"siblings", "Threads"}, {"vendor_id", "Vendor ID"}
};
}

namespace Krell {
ProcessorModule::ProcessorModule(std::string path)
    : AModule(path)
{
}

std::shared_ptr<ModuleTab> ProcessorModule::getData() const
{
    return _data;
}

std::string const& ProcessorModule::getName() const
{
    return _name;
}

void ProcessorModule::update()
{
    AModule::update();
    std::string line;
    bool isCore = false;
    std::string coreName{};
    while (std::getline(_stream, line)) {
        std::istringstream iss(line);
        std::string key{};
        std::string value{};
        std::getline(iss, key, ':');
        key = Utils::trim(key);
        std::getline(iss, value);
        value = Utils::trim(value);
        if (key == "processor") {
            coreName = value;
            continue;
        }
        if (!isCore && key.empty()) {
            isCore = true;
            continue;
        }
        if (isCore && key != "cpu MHz") {
            continue;
        }
        if (key == "cpu MHz") {
            (*_data)[relevantKeys.at(key) + ' ' + coreName] = std::make_unique<
                Data::StringData>(value);
            continue;
        }
        if (relevantKeys.contains(key)){
            (*_data)[relevantKeys.at(key)] = std::make_unique<Data::StringData>(value);
        }
    }
}
} // Krell
