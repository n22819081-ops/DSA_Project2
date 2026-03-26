//
// Created by omgit on 3/16/2026.
//
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "warehouse_map.h"
#include "map_creation.h"
#include "main_window.h"
#include <random>

// WINDOW ENSURING SFML IS WORKING
int main() {

    // Load csv and map;
    std::vector<std::vector<char>> generateMapFromCSV();

    // From loading

    std::default_random_engine gangster_generator;
    std::vector<std::vector<char>> myMap = create_map(gangster_generator);
    // std::ifstream csvFile("data1.csv");
    // std::vector<std::vector<char>> myMap = loadFromCSV(csvFile, 5);
    // csvFile.close();
    // Generating CSV FILE
    // 20 x 20 -> 400 nodes * 300 -> 120000 data points
    // std::ofstream csvFile("data1.csv");
    //
    // for (int i=0; i<300; i++) {
    //     std::vector<std::vector<char>> map = create_map(gangster_generator);
    //     saveToCSV(csvFile, i, map);
    // }
    MainWindow window(704, 804);
    window.setMap(myMap);

    window.run();
    //
    // while (window.isOpen()) {
    //     while (const std::optional event = window.pollEvent()) {
    //         if (event->is<sf::Event::Closed>())
    //             window.close();
    //     }
    //     window.clear();
    //     window.display();
    // }
    return 0;
}