/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#include <cstdlib>
#include <algorithm>
#include <memory>
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>

#include "Orchestrator.hpp"
#include "SFMLDisplay.hpp"

SFMLDisplay::SFMLDisplay()
{
    window.create(sf::VideoMode(800, 600), "SFML Display", sf::Style::Close);
    window.setTitle("MyGKrellM GTK");
    window.setFramerateLimit(5);
    if (!font.loadFromFile("./assets/arial.ttf")) {
        std::exit(1);
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
}

void SFMLDisplay::update(std::shared_ptr<Krell::OrchTable> data)
{
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
    }

    window.clear();
    static int red = 100;
    static int green = 100;
    static int blue = 100;

    red = (red + 1) % 256;
    green = (green + 2) % 256;
    blue = (blue + 3) % 256;
    sf::Color const dynamicColor(red, green, blue);
    int offsetX = 10;
    int offsetY = 10;
    int maxColumnWidth = 0;

    for (const auto& [moduleName, moduleTab] : *data) {
        sf::Text moduleTitle;
        moduleTitle.setFont(font);
        moduleTitle.setCharacterSize(15);
        moduleTitle.setFillColor(sf::Color::Red);
        moduleTitle.setString(moduleName);

        float maxWidth = moduleTitle.getLocalBounds().width;

        std::string moduleText;
        for (const auto& [key, value] : *moduleTab) {
            std::string const currentString =
                key + ": " + value->str();
            moduleText += currentString + "\n";

            sf::Text const tempText(currentString, font, 10);
            float const currentWidth = tempText.getLocalBounds().width;
            if (currentWidth > maxWidth) {
                maxWidth = currentWidth;
            }
        }

        int const rectangleHeight =
            30 + std::ranges::count(moduleText, '\n') * 15;

        if (offsetY + rectangleHeight > (int)window.getSize().y) {
            offsetX += maxColumnWidth + 20;
            offsetY = 10;
            maxColumnWidth = 0;
        }

        maxColumnWidth = std::max(
            maxColumnWidth, static_cast<int>(maxWidth + 10));

        if (offsetX + maxWidth + 10 > window.getSize().x) {
            break;
        }

        sf::RectangleShape rectangle(
            sf::Vector2f(maxWidth + 10, rectangleHeight));
        rectangle.setPosition(offsetX, offsetY);
        rectangle.setFillColor(sf::Color(200, 200, 200));
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(dynamicColor);

        moduleTitle.setPosition(offsetX + 5, offsetY + 5);

        sf::Text moduleData;
        moduleData.setFont(font);
        moduleData.setCharacterSize(10);
        moduleData.setFillColor(sf::Color::Black);
        moduleData.setString(moduleText);
        moduleData.setPosition(offsetX + 5, offsetY + 30);

        window.draw(rectangle);
        window.draw(moduleTitle);
        window.draw(moduleData);

        offsetY += rectangleHeight + 10;
    }

    window.display();
}

bool SFMLDisplay::isRunning() const
{
    return window.isOpen();
}


void SFMLDisplay::render()
{
    window.display();
}
