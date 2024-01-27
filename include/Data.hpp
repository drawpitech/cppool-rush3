/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Data.hpp
*/

#pragma once
#include <map>
#include <memory>
#include <string>

namespace Krell {
class IData {
public:
    virtual ~IData() = default;

    virtual std::string toString() const = 0;

private:
};

class NumberData : public IData {
public:
    NumberData(const double& size, const std::string& unit);

    std::string toString() const override;

private:
    std::string _unit;
    double _size;
};

using DataTab = std::map<std::string, std::unique_ptr<IData>>;
}
