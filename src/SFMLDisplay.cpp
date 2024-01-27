/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <memory>
#include <string>

#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "Orchestrator.hpp"
#include "SFMLDisplay.hpp"

namespace {
sf::Color hsvToSfColor(int h, double s, double v)
{
    const std::uint8_t ti = h / 60 % 6;
    const double f = h / 60. - ti;
    const std::uint8_t l = static_cast<std::uint8_t>(v * (1. - s) * 255);
    const std::uint8_t m = static_cast<std::uint8_t>(v * (1. - f * s) * 255);
    const std::uint8_t n = static_cast<std::uint8_t>(
        v * (1. - (1. - f) * s) * 255);
    switch (ti) {
        case 0:
            return sf::Color(v * 255, n, l);
        case 1:
            return sf::Color(m, v * 255, l);
        case 2:
            return sf::Color(l, v * 255, n);
        case 3:
            return sf::Color(l, m, v * 255);
        case 4:
            return sf::Color(n, l, v * 255);
        case 5:
            return sf::Color(v * 255, l, m);
        default:
            return sf::Color(0, 0, 0);
    }
}
};

namespace Krell {
void SFMLDisplay::eventHandler()
{
    sf::Event event{};
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window.close();
        }
    }
}

void SFMLDisplay::nextColor()
{
    _color = hsvToSfColor(_hue, 1., 1.);
    _hue = (_hue + 6) % 360;
}

SFMLDisplay::SFMLDisplay()
{
    _window.create(sf::VideoMode(800, 600), "SFML Display", sf::Style::Close);
    _window.setTitle("MyGKrellM GTK");
    if (!_font.loadFromFile("./assets/arial.ttf")) {
        std::exit(1);
    }
    _text.setFont(_font);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
}

void SFMLDisplay::update(std::shared_ptr<OrchTable> data)
{
    eventHandler();
    nextColor();

    _window.clear();

    int offsetX = 10;
    int offsetY = 10;
    int maxColumnWidth = 0;

    for (const auto& [moduleName, moduleTab] : *data) {
        sf::Text moduleTitle;
        moduleTitle.setFont(_font);
        moduleTitle.setCharacterSize(15);
        moduleTitle.setFillColor(sf::Color::Red);
        moduleTitle.setString(moduleName);

        float maxWidth = moduleTitle.getLocalBounds().width;

        std::string moduleText;
        for (const auto& [key, value] : *moduleTab) {
            std::string const currentString =
                key + ": " + value->str();
            moduleText += currentString + "\n";

            sf::Text const tempText(currentString, _font, 10);
            float const currentWidth = tempText.getLocalBounds().width;
            if (currentWidth > maxWidth) {
                maxWidth = currentWidth;
            }
        }

        int const rectangleHeight =
            30 + std::ranges::count(moduleText, '\n') * 15;

        if (offsetY + rectangleHeight > _window.getSize().y) {
            offsetX += maxColumnWidth + 20;
            offsetY = 10;
            maxColumnWidth = 0;
        }

        maxColumnWidth = std::max(
            maxColumnWidth, static_cast<int>(maxWidth + 10));

        if (offsetX + maxWidth + 10 > _window.getSize().x) {
            break;
        }

        sf::RectangleShape rectangle(
            sf::Vector2f(maxWidth + 10, rectangleHeight));
        rectangle.setPosition(offsetX, offsetY);
        rectangle.setFillColor(sf::Color(200, 200, 200));
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(_color);

        moduleTitle.setPosition(offsetX + 5, offsetY + 5);

        sf::Text moduleData;
        moduleData.setFont(_font);
        moduleData.setCharacterSize(10);
        moduleData.setFillColor(sf::Color::Black);
        moduleData.setString(moduleText);
        moduleData.setPosition(offsetX + 5, offsetY + 30);

        _window.draw(rectangle);
        _window.draw(moduleTitle);
        _window.draw(moduleData);

        offsetY += rectangleHeight + 10;
    }

    _window.display();
}

bool SFMLDisplay::isRunning() const
{
    return _window.isOpen();
}


void SFMLDisplay::render()
{
    _window.display();
}
}
