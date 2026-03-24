//
// Created by omgit on 3/21/2026.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "Dijkstra.h"
#ifndef DSA_PROJECT2_MAIN_WINDOW_H
#define DSA_PROJECT2_MAIN_WINDOW_H
class MainWindow : public sf::RenderWindow {
    private:
        int width;
        int height;
        int row;
        int col;
        std::vector<Tile> tiles;
        std::vector<std::vector<char>> map;
        // Texture used for MainWindow
        // For warehouse map
        sf::Texture wallTexture;
        sf::Texture openTexture;
        sf::Texture f_special_texture;
        sf::Texture s_special_texture;
        sf::Texture p_special_texture;

        // Options
        // We need buttons for randomly selection of map,
        // algo selection
        // run reset
        // then result section

        sf::RectangleShape main_window;
    public:
    // Constructor
    MainWindow(unsigned int w, unsigned int h) : sf::RenderWindow(sf::VideoMode({w,h}), "Algo Comparsion", sf::Style::Close)
    {
        this->width = w;
        this->height = h;
        this->row = (height-100)/32;
        this->col = (width)/32;
        this->map.resize(row, std::vector<char>(col, '.'));

        // Load files
        if (!wallTexture.loadFromFile("images/tile_wall_2.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD WALL.PNG" << std::endl;
        }
        if (!openTexture.loadFromFile("images/tile_open_2.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD OPEN.PNG" << std::endl;
        }
        if (!s_special_texture.loadFromFile("images/tile_ss.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD SSPECIAL.PNG" << std::endl;
        }
        if (!p_special_texture.loadFromFile("images/tile_sp.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD PSPECIAL.PNG" << std::endl;
        }
        if (!f_special_texture.loadFromFile("images/tile_sf.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD FSPECIAL.PNG" << std::endl;
        }

        // Generate tiles
        // 32 x 32 images
        for (int y=0; y<this->row; y++) {
            for (int x=0; x<this->col; x++) {
                tiles.emplace_back(openTexture, wallTexture, s_special_texture, p_special_texture, f_special_texture,  static_cast<float>(x*32), static_cast<float>(y*32));
            }
        }
    }
    // looping thru our map and setting tile to the corresponding size.
    void setMap(std::vector<std::vector<char>>& newMap) {
        this->map = newMap;
        for (int y=0; y<this->row; y++) {
            for (int x=0; x<this->col; x++) {
                // need index for tile because 1d vec
                int index = y*this->col + x;
                if (map[y][x] == '.') {
                    tiles[index].setState(Tile::TileState::Open);
                }
                if (map[y][x] == '#') {
                    tiles[index].setState(Tile::TileState::Wall);
                }
                if (map[y][x] == 'S') {
                    tiles[index].setState(Tile::TileState::S_Special);
                }
                if (map[y][x] == 'P') {
                    tiles[index].setState(Tile::TileState::P_Special);
                }
                if (map[y][x] == 'F') {
                    tiles[index].setState(Tile::TileState::F_Special);
                }

            }
        }
    }
    // Runs Dijkstra on the current map and highlights the path tiles yellow.
    // Call this after setMap().
    void showPath() {
        // Find the start cell 'S' in the map
        int startRow = -1, startCol = -1;
        for (int y = 0; y < this->row && startRow == -1; y++) {
            for (int x = 0; x < this->col && startRow == -1; x++) {
                if (map[y][x] == 'S') {
                    startRow = y;
                    startCol = x;
                }
            }
        }
        if (startRow == -1) return;  // no start cell, nothing to do

        // Run Dijkstra — returns ordered path from S to F
        std::vector<std::pair<int,int>> path = dijkstra(this->map, startRow, startCol);

        // Color every path cell except S and F (those keep their special textures)
        for (auto& [r, c] : path) {
            if (map[r][c] == 'S' || map[r][c] == 'F') continue;
            int index = r * this->col + c;
            tiles[index].setState(Tile::TileState::Path);
        }
    }

    void run() {
        sf::Clock clock;

        // Load buttons
        while (this->isOpen()) {
            while (std::optional<sf::Event> event = this->pollEvent()) {
                // close
                if (event->is<sf::Event::Closed>()) {
                    this->close();
                    break;
                }
            }
            clear();
            for (auto& tile : this->tiles) {
                draw(tile.getSprite());
            }
            display();
        }
    }
};
#endif //DSA_PROJECT2_MAIN_WINDOW_H