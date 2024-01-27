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
class HostnameModule final : public AModule {
public:
    explicit HostnameModule(
        const std::string& file = "/proc/sys/kernel/hostname");

    void update() override;

    std::shared_ptr<ModuleTab> getData() const override;

    const std::string& getName() const override;

    void subscribe(std::string const& name) override;

    void unsubscribe(std::string const& name) override;

    void log() const override;

private:
    std::shared_ptr<ModuleTab> _data{new ModuleTab};

    static inline std::string _name{"hostname"};
};
} // namespace Krell
