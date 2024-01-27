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

class SFMLDisplay : public Krell::IDisplay {
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;

    public:
        void initialize() override;
        void render(const std::string& data) override;
        //void searchdata(std::shared_ptr<OrchTable> data)
        ~SFMLDisplay() override = default;
};



#endif /* !SFMLDISPLAY_HPP_ */
