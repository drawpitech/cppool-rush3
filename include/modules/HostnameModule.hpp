/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Hostname.hpp
*/

#pragma once

#include <string>

#include "AModule.hpp"

namespace Krell {
class HostnameModule final : public AModule
{
   public:
    explicit HostnameModule(const std::string &file = "/proc/sys/kernel/hostname");

    void update() override;
    DataTab &getData() override;
    void subscribe(std::string const &name) override;
    void unsubscribe(std::string const &name) override;

   private:
    DataTab _data;
};
}  // namespace Krell
