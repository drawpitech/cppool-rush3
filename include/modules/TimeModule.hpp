/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Time.hpp
*/

#pragma once

#include <memory>
#include <string>

#include "AModule.hpp"
#include "Data.hpp"

namespace Krell {
class TimeModule final : public AModule
{
   public:
    explicit TimeModule(const std::string& file = "/proc/sys/kernel/hostname");

    void update() override;

    std::shared_ptr<ModuleTab> getData() const override;

    const std::string& getName() const override;

   private:
    std::shared_ptr<ModuleTab> _data{new ModuleTab};

    static inline std::string _name{"Time"};
};
}  // namespace Krell
