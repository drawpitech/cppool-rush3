/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** IDisplay.hpp
*/

#pragma once

namespace Krell {

#include <string>

class IDisplay {
    public:
        virtual ~IDisplay() = default;
        virtual void initialize() = 0;
        virtual void render(const std::string &data) = 0;
    };

} // Krell
