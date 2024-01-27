/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** AModule.hpp
*/

#pragma once
#include <IModule.hpp>
#include <filesystem>
#include <iosfwd>
#include <sstream>

namespace Krell {
class AModule: public IModule {
public:
    explicit AModule(const std::string& path);

    void update() override;
protected:
    std::istringstream _stream;
    std::filesystem::path _path;
};
}
