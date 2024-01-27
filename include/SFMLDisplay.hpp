/*
** EPITECH PROJECT, 2024
** B-PDG-300-BDX-3-1-PDGRUSH3-jacques.rathier
** File description:
** SFMLDisplay
*/

#ifndef SFMLDISPLAY_HPP_
#define SFMLDISPLAY_HPP_

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "IDisplay.hpp"
#include "Orchestrator.hpp"

class SFMLDisplay : public Krell::IDisplay
{
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;

public:
    SFMLDisplay();

    void update(std::shared_ptr<Krell::OrchTable> data) override;

    bool isRunning() const override;

    void render() override;

    void mainLogic(Krell::Orchestrator& orchestrator);

    ~SFMLDisplay() override = default;
};


#endif /* !SFMLDISPLAY_HPP_ */
