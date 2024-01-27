/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "SFMLDisplay.hpp"

    void SFMLDisplay::initialize() {
        window.create(sf::VideoMode(800, 600), "SFML Display");
        window.setTitle("MyGKrellM GTK");
        if (!font.loadFromFile("arial.ttf")) {
            exit(1);
        }
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
    }

    void SFMLDisplay::render(const std::string& data) {
        sf::RectangleShape rectangle(sf::Vector2f(120, 50));
        rectangle.setSize(sf::Vector2f(150, 100));
        rectangle.setFillColor(sf::Color(100, 250, 50));
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            text.setString(data);
            window.clear();
            window.draw(rectangle);
            window.draw(text);
            window.display();
        }
    }

