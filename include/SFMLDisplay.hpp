/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include "IDisplay.hpp"
#include "Orchestrator.hpp"

namespace Krell {
class SFMLDisplay final : public IDisplay
{
    void eventHandler();

    void nextColor();

public:
    SFMLDisplay();

    void update(std::shared_ptr<OrchTable> data) override;

    bool isRunning() const override;

    void render() override;

private:
    std::uint8_t _hue{0};
    sf::Color _color{};

    sf::RenderWindow _window;
    sf::Font _font;
    sf::Text _text;
};
}
