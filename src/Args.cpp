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
    for (const auto& opt : OPTIONS) {
        if (opt.c == c) {
            options |= opt.bit_mask;
            return;
        }
    }
    std::cerr << "Invalid option `-" << c << "`.\n" << std::flush;
}

static void set_large_flag(options_t &options, const std::string &str)
{
    for (const auto& opt : OPTIONS) {
        if (!opt.large.empty() && opt.large == str) {
            options |= opt.bit_mask;
            return;
        }
    }
    std::cerr << "Invalid option `--" << str << "`.\n" << std::flush;
}

options_t get_params(uint32_t argc, const char *argv[])
{
    options_t options = 0;
    std::span args{argv, static_cast<std::size_t>(argc)};

    for (const auto &arg : args.subspan(1)) {
        std::string str{arg};
        if (str[0] != '-') {
            std::cerr << "Invalid option `" << str << "`.\n" << std::flush;
            continue;
        }
        if (str[1] == '-') {
            set_large_flag(options, str.substr(2));
            continue;
        }
        for (size_t i = 1; str[i] != '\0'; i++)
            set_short_flag(options, str[i]);
    }
    return options;
}
