//
// Created by omgit on 3/21/2026.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "button.h"
#include <random>
#include <chrono>
#include "map_creation.h"
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
        sf::Texture cratetexture;
        sf::Texture humantexture;
        sf::Texture stairtexture;

        sf::Font font;
        Button* loadMapButton;
        Button* saveMapButton;
        Button* runDijkstraButton;
        Button* runAStarButton;
        Button* resetButton;


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
        if (!humantexture.loadFromFile("images/tile_open_w2.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD HUMAN" << std::endl;
        }
        if (!stairtexture.loadFromFile("images/tile_open_w1.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD STAIRS" << std::endl;
        }
        if (!openTexture.loadFromFile("images/tile_open_4.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD OPEN.PNG" << std::endl;
        }
        if (!s_special_texture.loadFromFile("images/tile_ss_2.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD SSPECIAL.PNG" << std::endl;
        }
        if (!p_special_texture.loadFromFile("images/tile_sp_3.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD PSPECIAL.PNG" << std::endl;
        }
        if (!f_special_texture.loadFromFile("images/tile_sf_2.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD FSPECIAL.PNG" << std::endl;
        }
        if (!cratetexture.loadFromFile("images/tile_crate.png")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD CRATE" << std::endl;
        }

        if (!font.openFromFile("font.ttf")) {
            std::cerr << "YOU ARE COOKED FAILED TO LOAD FONT" << std::endl;
        }
        loadMapButton = new Button(20.f, 720.f, 150.f, 50.f, font, "Load Random Map" );
        runAStarButton = new Button (190.f, 720.f,120.f, 50.f, font, "Run A*");
        runDijkstraButton = new Button(330.f, 720.f, 140.f, 50.f, font, "Run Dijkstra");
        resetButton = new Button(490.f, 720.f, 100.f, 50.f,  font, "Reset");
        // Generate tiles
        // 32 x 32 images
        for (int y=0; y<this->row; y++) {
            for (int x=0; x<this->col; x++) {
                tiles.emplace_back(openTexture, wallTexture, s_special_texture, p_special_texture, f_special_texture, cratetexture,humantexture, stairtexture,  static_cast<float>(x*32), static_cast<float>(y*32));
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
                if (map[y][x] == '.' ) {
                    tiles[index].setState(Tile::TileState::Open);
                }
                if (map[y][x] == '%') {
                    tiles[index].setState(Tile::TileState::OpenStair);
                }
                if (map[y][x] == '^') {
                    tiles[index].setState(Tile::TileState::OpenHuman);
                }
                if (map[y][x] == '#') {
                    if (y == 0 || y == (this->row-1) || x == 0 || x == (this->col-1)) {
                        tiles[index].setState(Tile::TileState::Wall);
                    }else {
                        tiles[index].setState(Tile::TileState::Crate);
                    }
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
                if (event->is<sf::Event::MouseButtonPressed>()) {
                    if (auto* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>()) {
                        if (mouseEvent->button == sf::Mouse::Button::Left) {
                            sf::Vector2f mousePos(
                                static_cast<float>(mouseEvent->position.x),
                                static_cast<float>(mouseEvent->position.y)
                            );

                            if (loadMapButton->isClicked(mousePos)) {
                                std::cout << "LOADING MAP" << std::endl;
                                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                                std::mt19937 rng(seed);

                                int range_min = 2;
                                int range_max = 299;
                                std::uniform_int_distribution<int> dist(range_min, range_max);
                                int rand_num = dist(rng);
                                std::ifstream csvFile("data1.csv");
                                std::vector<std::vector<char>> myMap = loadFromCSV(csvFile, rand_num);
                                setMap(myMap);
                            }
                            else if (runAStarButton->isClicked(mousePos)) {
                                std::cout << "RUN A* STAR" << std::endl;
                            }
                            else if (runDijkstraButton->isClicked(mousePos)) {
                                std::cout << "RUN DIJKSTRA" << std::endl;
                            }
                            else if (resetButton->isClicked(mousePos)) {
                                std::cout << "RESET BUTTON" << std::endl;
                            }
                        }
                    }
                }
            }
            clear();
            for (auto& tile : this->tiles) {
                draw(tile.getSprite());
            }
            loadMapButton->draw(*this);
            runAStarButton->draw(*this);
            runDijkstraButton->draw(*this);
            resetButton->draw(*this);

            display();
        }
    }
};
#endif //DSA_PROJECT2_MAIN_WINDOW_H