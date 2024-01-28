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

namespace Krell::Data {
enum DataClass
{
    String,
    Number,
    Graph
};

class IData
{
public:
    virtual ~IData() = default;

    virtual std::string str() const = 0;

    virtual DataClass type() const = 0;

private:
};

class StringData final : public IData
{
public:
    explicit StringData(std::string str);

    std::string str() const override;

    constexpr DataClass type() const override;

private:
    std::string _data;
};
}


namespace Krell {
using ModuleTab = std::map<std::string, std::unique_ptr<Data::IData> >;
}
