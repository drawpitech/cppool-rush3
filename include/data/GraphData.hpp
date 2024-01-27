/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** GraphData.hpp
*/

#pragma once

#include <cstddef>
#include <queue>
#include <type_traits>

namespace Krell::Data {
template <typename T, std::size_t _size> requires std::is_arithmetic_v<T>
class GraphData final : public IData
{
public:
    explicit GraphData(
        std::optional<std::string> unit = std::nullopt,
        std::optional<T> max = std::nullopt,
        std::optional<T> min = 0)
        : _unit(std::move(unit)), _max{max ? *max : 0}, _min{min ? *min : 0}
    {
    }

    void push(T value)
    {
        _max = std::max(_max, value);
        _min = std::min(_min, value);
        if (_data.size() >= _size) {
            _data.pop();
        }
        _data.push(value);
    }

    std::string str() const override
    {
        return _data.back() + (_unit ? " " + *_unit : "");
    }

private:
    std::optional<std::string> _unit{};

    T _max{0};
    T _min{0};
    std::queue<T> _data;
};
}
