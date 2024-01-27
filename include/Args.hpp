/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Args.hpp
*/

#pragma once

#include <cstdint>
#include <string>
#include <vector>

using options_t = uint16_t;

enum
{
    OPT_DEBUG_MOD = 1 << 0,
    OPT_HELP_MESS = 1 << 1,
};

struct opt_t
{
    char c;
    std::string large;
    options_t bit_mask;
};

static const std::vector<opt_t> OPTIONS = {{
    {'h', "help", OPT_HELP_MESS},
    {'\0', "debug", OPT_DEBUG_MOD},
    {'\0', "", 0},
}};

options_t get_params(uint32_t argc, const char *argv[]);
