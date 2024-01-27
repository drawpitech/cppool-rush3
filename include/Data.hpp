/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** Data.hpp
*/

#pragma once
#include <map>
#include <memory>
#include <optional>
#include <string>

namespace Krell {
class IData
{
public:
    virtual ~IData() = default;

    virtual std::string str() const = 0;

private:
};

class StringData final : public IData
{
public:
    explicit StringData(std::string str);

    std::string str() const override;

private:
    std::string _data;
};

class NumberData final : public IData
{
public:
    explicit NumberData(std::string unit, bool isSi = false);

    std::string str() const override;

private:
    std::string _unit;
    bool _isSi;
};



using ModuleTab = std::map<std::string, std::unique_ptr<IData> >;
}
