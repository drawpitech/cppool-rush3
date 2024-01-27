/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_

#include "IDisplay.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include "Orchestrator.hpp"

class SFMLDisplay : public Krell::IDisplay {
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;

    public:
        void initialize() override;
        void update(std::shared_ptr<Krell::OrchTable> data) override;
        void render() override;
        void mainLogic(Krell::Orchestrator& orchestrator);
        ~SFMLDisplay() override = default;
};


#endif /* !SFMLDISPLAY_HPP_ */
