/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Utils.cpp
*/

#include "Utils.hpp"

#include <memory>
#include <string>

#include "Data.hpp"

namespace Krell::Utils {
std::string ltrim(const std::string& s, const char* t)
{
    std::string str = s;
    str.erase(0, str.find_first_not_of(t));
    return str;
}

std::string rtrim(const std::string& s, const char* t)
{
    std::string str = s;
    str.erase(str.find_last_not_of(t) + 1);
    return str;
}

std::string trim(const std::string& s, const char* t)
{
    std::string str = s;
    str = ltrim(str, t);
    str = rtrim(str, t);
    return str;
}

void add_to_data(
    Krell::ModuleTab& map,
    std::unordered_map<std::string, std::string> relevant_keys,
    const std::string& key, const std::string& value)
{
    if (relevant_keys.find(key) == relevant_keys.end())
        return;
    map[relevant_keys.at(key)] = std::make_unique<Data::StringData>(value);
}
}  // namespace Krell::Utils
