/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Args.hpp
*/

#pragma once

#include <cstdint>
#include <span>
#include <string>
#include <vector>

using options_t = uint16_t;

enum OPTS
{
    DEBUG_MOD = 1 << 0,
    HELP_MESS = 1 << 1,
    GRAPHICAL = 1 << 2,
};

struct opt_t
{
    options_t bit_mask;
    char c;
    std::string large;
    std::string description;
};

static const std::vector<opt_t> OPTIONS = {{
    {OPTS::HELP_MESS, 'h', "help", "print this help message"},
    {OPTS::DEBUG_MOD, '\0', "debug", "print debug messages"},
    {OPTS::GRAPHICAL, '\0', "gui", "launch the graphical mode with SFML lib"},
}};

options_t get_params(std::span<const char*> args);
