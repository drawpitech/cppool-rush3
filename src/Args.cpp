/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Args.cpp
*/

#include "Args.hpp"

#include <iostream>
#include <span>

static void set_short_flag(options_t &options, char c)
{
    for (options_t i = 0; OPTIONS.at(i).bit_mask != 0; i++) {
        if (OPTIONS.at(i).c == c) {
            options |= OPTIONS.at(i).bit_mask;
            return;
        }
    }
    std::cerr << "Invalid option `-" << c << "`.\n" << std::flush;
}

static void set_large_flag(options_t &options, const std::string &str)
{
    for (options_t i = 0; OPTIONS.at(i).bit_mask != 0; i++) {
        if (!OPTIONS.at(i).large.empty() && OPTIONS.at(i).large == str) {
            options |= OPTIONS.at(i).bit_mask;
            return;
        }
    }
    std::cerr << "Invalid option `--" << str << "`.\n" << std::flush;
}

static void get_option(options_t &options, char const *str)
{
    if (*str != '-') {
        for (; *str != '\0'; str += 1)
            set_short_flag(options, *str);
        return;
    }
    str += 1;
    set_large_flag(options, str);
}

options_t get_params(uint32_t argc, const char *argv[])
{
    options_t options = 0;
    std::span args{argv, static_cast<std::size_t>(argc)};

    for (const auto &arg : args.subspan(1)) {
        if (arg[0] == '-') {
            get_option(options, arg + 1);
            continue;
        }
        std::cerr << "Invalid option `" << arg << "`.\n" << std::flush;
    }
    return options;
}
