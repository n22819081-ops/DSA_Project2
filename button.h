//
// Created by omgit on 3/25/2026.
//

#ifndef DSA_PROJECT2_BUTTON_H
#define DSA_PROJECT2_BUTTON_H
#pragma once
#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics.hpp>


class Button {
    private:
    sf::RectangleShape shape;
    sf::Text text;

    public:
    // constructor
    // Scale and set position
    Button(float x, float y, float w, float h, sf::Font& font, std::string mystring) : text(font, mystring, 12) {
        shape.setSize(sf::Vector2f(w, h));
        shape.setPosition(sf::Vector2f(x, y));
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2.0);


        text.setFillColor(sf::Color::Black);
        text.setPosition(sf::Vector2f(x + 10, y + 8));
    }

    void draw (sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isClicked(sf::Vector2f mousePos) {
        return shape.getGlobalBounds().contains(mousePos);
    }
};
#endif //DSA_PROJECT2_BUTTON_H