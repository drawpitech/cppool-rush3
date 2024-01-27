/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** TimeModule.cpp
*/

#include "modules/TimeModule.hpp"

#include <pwd.h>

#include <iostream>

namespace Krell {
TimeModule::TimeModule(const std::string& file) : AModule{file} {}

void TimeModule::update()
{
    time_t t = time(nullptr);
    struct tm* tm = localtime(&t);

    std::string str_date = std::asctime(tm);
    std::size_t index = str_date.find(':');
    if (str_date.empty() || index == std::string::npos)
        return;

    std::string date = str_date.substr(0, index - 3) + " " +
                       std::to_string(tm->tm_year + 1900);
    std::string time = str_date.substr(index - 2, 8);

    (*_data)["date"] = std::make_unique<StringData>(date);
    (*_data)["time"] = std::make_unique<StringData>(time);
}

void TimeModule::log() const
{
    for (auto& [key, data] : *_data)
        std::clog << key << ": " << data->str() << "\n";
}

std::shared_ptr<ModuleTab> TimeModule::getData() const
{
    return _data;
}

const std::string& TimeModule::getName() const
{
    return _name;
}

void TimeModule::subscribe(std::string const& name) {}

void TimeModule::unsubscribe(std::string const& name) {}
}  // namespace Krell
