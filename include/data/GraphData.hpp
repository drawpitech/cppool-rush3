/*
** EPITECH PROJECT, 2024
** MyGKrellm
** File description:
** GraphData.hpp
*/

#pragma once

#include <cstddef>
#include <deque>
#include <optional>
#include <type_traits>

namespace Krell::Data {
template <typename T> requires std::is_arithmetic_v<T>
class GraphData final : public IData
{
public:
    explicit GraphData(
        std::size_t size,
        std::string unit,
        std::optional<T> max = std::nullopt,
        std::optional<T> min = 0)
        : _unit(std::move(unit)), _size(size), _max{max ? *max : 0},
          _min{min ? *min : 0}
    {
    }

    void push(T value)
    {
        if (!_max) {
            _max = value;
        }
        if (!_min) {
            _min = value;
        }
        _max = std::max(_max, value);
        _min = std::min(_min, value);
        if (_data.size() >= _size) {
            _data.pop_back();
        }
        _data.emplace_front(value);
    }

    std::string str() const override
    {
        return std::to_string(_data.front()) + (
                   _unit.empty() ? "" : " " + _unit);
    }

    const std::deque<T>& data() const
    {
        return _data;
    }

    std::size_t size() const
    {
        return _size;
    }

    void size(const std::size_t size)
    {
        _size = size;
        while (_data.size() > _size) {
            _data.pop_back();
        }
    }

    T max() const
    {
        return _max;
    }

    T min() const
    {
        return _min;
    }

    constexpr DataClass type() const override
    {
        return Graph;
    }

private:
    std::string _unit{};

    std::size_t _size;

    T _max{0};
    T _min{0};
    std::deque<T> _data;
};
}
