/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Utils.hpp
*/

#pragma once
#include <string>
#include <unordered_map>

#include "Data.hpp"

constexpr const char* default_trim = " \t\n\r\f\v";

namespace Krell::Utils {
std::string ltrim(const std::string& s, const char* t = default_trim);

std::string rtrim(const std::string& s, const char* t = default_trim);

std::string trim(const std::string& s, const char* t = default_trim);

void add_to_data(
    Krell::ModuleTab& map,
    std::unordered_map<std::string, std::string> relevant_keys,
    const std::string& key, const std::string& value);
}  // namespace Krell::Utils
