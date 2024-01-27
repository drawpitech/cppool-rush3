/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** SystemInfo.hpp
*/

#pragma once

#include <string>

#include "AModule.hpp"

namespace Krell {
class SystemInfoModule final : public AModule
{
   public:
    explicit SystemInfoModule(const std::string &file = "/proc/sys/kernel/hostname");

    void update() override;
    DataTab &getData() override;
    void subscribe(std::string const &name) override;
    void unsubscribe(std::string const &name) override;

   private:
    DataTab _data;
};
}  // namespace Krell
