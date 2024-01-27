/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Utils.hpp
*/

#pragma once
#include <string>

constexpr const char* default_trim = " \t\n\r\f\v";

namespace Krell::Utils {
std::string ltrim(const std::string& s, const char* t = default_trim);

std::string rtrim(const std::string& s, const char* t = default_trim);

std::string trim(const std::string& s, const char* t = default_trim);
}
