/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#include <iostream>
#include <thread>

#include "modules/ProcessorModule.hpp"
#include "Args.hpp"
#include "Orchestrator.hpp"
#include "SFMLDisplay.hpp"
#include "IDisplay.hpp"
#include "modules/HostnameModule.hpp"
#include "modules/MemoryModule.hpp"
#include "modules/OSModule.hpp"
#include "modules/TimeModule.hpp"

void SFMLDisplay::initialize() {
    window.create(sf::VideoMode(800, 600), "SFML Display");
    window.setTitle("MyGKrellM GTK");
    if (!font.loadFromFile("./assets/arial.ttf")) {
        exit(1);
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
}

void SFMLDisplay::mainLogic(Krell::Orchestrator& orchestrator) {
    while (window.isOpen()) {
        orchestrator.update();
        auto data = orchestrator.getData();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        update(data);
        render();
    }
}

void SFMLDisplay::update(std::shared_ptr<Krell::OrchTable> data) {
    window.clear();

    int offsetX = 10;
    int offsetY = 10;

    for (const auto& modulePair : *data) {
        const auto& moduleName = modulePair.first;
        const auto& moduleTab = modulePair.second;

        std::string moduleText = moduleName + "\n";
        for (const auto& dataPair : *moduleTab) {
            moduleText += dataPair.first + ": " + dataPair.second->str() + "\n";
        }

        sf::Text moduleTitle;
        moduleTitle.setFont(font);
        moduleTitle.setCharacterSize(15);
        moduleTitle.setFillColor(sf::Color::Black);
        moduleTitle.setString(moduleName);
        moduleTitle.setPosition(offsetX + 5, offsetY + 5);

        sf::Text moduleData;
        moduleData.setFont(font);
        moduleData.setCharacterSize(10);
        moduleData.setFillColor(sf::Color::Black);
        moduleData.setString(moduleText);
        moduleData.setPosition(offsetX + 5, offsetY + 30);

        int rectangleHeight = 30 + (std::count(moduleText.begin(), moduleText.end(), '\n') * 15);

        sf::RectangleShape rectangle(sf::Vector2f(200, rectangleHeight));
        rectangle.setPosition(offsetX, offsetY);
        rectangle.setFillColor(sf::Color(200, 200, 200));
        rectangle.setOutlineThickness(2);
        rectangle.setOutlineColor(sf::Color(0, 0, 0));

        window.draw(rectangle);
        window.draw(moduleTitle);
        window.draw(moduleData);

        offsetY += rectangleHeight + 10;
        if (offsetY + rectangleHeight > window.getSize().y) {
            offsetY = 10;
            offsetX += 210;
        }
    }
}

void SFMLDisplay::render() {
    window.display();
}

