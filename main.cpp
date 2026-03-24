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

    std::default_random_engine gangster_generator;

    //WarehouseMap myWarehouse = WarehouseMap(22, 22);
    // myWarehouse.fillOpen();
    // myWarehouse.addBorderWalls();
    // myWarehouse.generateFromTiles();
    // myWarehouse.placeSpecialCells();
    // myWarehouse.print();
    std::vector<std::vector<char>> myMap = create_map(gangster_generator);
    //sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML 3.0 Works!");
    MainWindow window(704, 804);
    window.setMap(myMap);
    window.showPath();  // run Dijkstra and highlight the path
    window.run();




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