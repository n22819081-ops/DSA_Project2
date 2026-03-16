//
// Created by omgit on 3/16/2026.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


// WINDOW ENSURING SFML IS WORKING
int main() {
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML 3.0 Works!");
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();
        window.display();
    }
    return 0;
}