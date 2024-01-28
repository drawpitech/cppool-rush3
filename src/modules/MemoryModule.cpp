/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** MemoryModule.cpp
*/

#include <string>
#include <tuple>
#include <unordered_map>
#include <sstream>
#include <memory>

#include "modules/MemoryModule.hpp"

#include <iostream>

#include "Data.hpp"
#include "AModule.hpp"
#include "data/GraphData.hpp"
#include "data/NumberData.hpp"

namespace {
inline const std::unordered_map<
    std::string, std::tuple<std::string, Krell::Data::DataClass>
>
relevantKeys{
    {"Active", {"Active", Krell::Data::Graph}},
    {"Cached", {"Cached", Krell::Data::Graph}},
    {"Inactive", {"Inactive", Krell::Data::Graph}},
    {"MemFree", {"Free", Krell::Data::Graph}},
    {"MemTotal", {"Total", Krell::Data::Number}},
    {"MemAvailable", {"Available", Krell::Data::Graph}}
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
        std::size_t value;
        std::string unit;
        std::getline(iss, key, ':');
        iss >> value >> unit;
        if (relevantKeys.contains(key)) {
            const auto [name, type] = relevantKeys.at(key);
            if (!_data->contains(name))
                switch (type) {
                    case Data::Graph:
                        (*_data)[name] = std::make_unique<Data::GraphData<
                            std::size_t> >(
                            60, unit);
                        break;
                    case Data::Number:
                        std::cout << unit << std::endl;
                        (*_data)[name] = std::make_unique<Data::NumberData<
                            std::size_t> >(
                            unit);
                        break;
                    default:
                        break;
                }
            switch (type) {
                case Data::Graph:
                    dynamic_cast<Data::GraphData<std::size_t> *>((*_data)[name].get())->push(value);
                    break;
                case Data::Number:
                    dynamic_cast<Data::NumberData<std::size_t> *>((*_data)[name].get())->data(value);
                    break;
                default:
                    break;
            }
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
