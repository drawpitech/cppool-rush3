/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** NumberData.hpp
*/

#pragma once
#include <string>
#include <utility>

#include "Data.hpp"

namespace Krell::Data {
template <typename T> requires std::is_arithmetic_v<T>
class NumberData final : public IData
{
public:
    explicit NumberData(std::string unit)
        : _unit(std::move(unit))
    {
    }

    const T& data() const
    {
        return _data;
    }

    void data(const T& data)
    {
        _data = data;
    }

    std::string str() const override
    {
        return std::to_string(_data) + (_unit.empty() ? "" : " " + _unit);
    }

    constexpr DataClass type() const override
    {
        return Number;
    }

private:
    T _data;
    std::string _unit;
};
};
