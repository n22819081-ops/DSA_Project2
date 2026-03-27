//
// Created by omgit on 3/27/2026.
//

#include <iostream>
#include <format>
#include <SFML/Graphics.hpp>
#ifndef DSA_PROJECT2_STAT_WINDOW_H
#define DSA_PROJECT2_STAT_WINDOW_H
class statWindow : public sf::RenderWindow
{
private:
    int width;
    int height;
    int num_nodesExplored;
    int num_pathLen;
    double num_totalTime;
    sf::Text timeText;
    sf::Text nodeExplored;
    sf::Text pathLength;
    sf::Font font;
public:
    // constructor
    // INT INT DOUBLE
    statWindow(unsigned int w, unsigned int h,int nodesExplored, int pathLen, double totalTime) : sf::RenderWindow(sf::VideoMode({w,h}), "Stats"), timeText(font), nodeExplored(font), pathLength(font) {
        this->width = w;
        this->height = h;
        this->num_nodesExplored = nodesExplored;
        this->num_totalTime = totalTime;
        this->num_pathLen = pathLen;
        if (!font.openFromFile("font.ttf")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD FONT" << std::endl;
        }
        std::string myTime = std::format("{:.9f}", num_totalTime);
        timeText.setFont(font);
        timeText.setCharacterSize(30);
        timeText.setFillColor(sf::Color::White);
        timeText.setPosition(sf::Vector2f(0, height / 6));
        timeText.setString("Algorithm time: " + myTime);

        nodeExplored.setFont(font);
        nodeExplored.setCharacterSize(30);
        nodeExplored.setFillColor(sf::Color::White);
        nodeExplored.setPosition(sf::Vector2f(0, height / 4 + 25));
        nodeExplored.setString("Nodes explored: " + std::to_string(nodesExplored));

        pathLength.setFont(font);
        pathLength.setCharacterSize(30);
        pathLength.setFillColor(sf::Color::White);
        pathLength.setPosition(sf::Vector2f(0, height / 4 + 50));
        pathLength.setString("Path Length: " + std::to_string(pathLen));


    }

    void run() {
        while (isOpen()) {
            while (std::optional<sf::Event> event = pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    this->close();
                    break;
                }
            }
            clear(sf::Color::Black);
            draw(timeText);
            draw(nodeExplored);
            draw(pathLength);
            display();
        }
    }
};
#endif //DSA_PROJECT2_STAT_WINDOW_H