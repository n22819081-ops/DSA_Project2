//
// Created by omgit on 3/21/2026.
//
#include <iostream>
#include <SFML/Graphics.hpp>
#include "tile.h"
#include "Dijkstra.h"
#include "AStar.h"
#include "button.h"
#include <random>
#include <chrono>
#include "map_creation.h"
#include "stat_window.h"
#ifndef DSA_PROJECT2_MAIN_WINDOW_H
#define DSA_PROJECT2_MAIN_WINDOW_H
struct return_paths {
    Path_Result path_result;
    DjikstraResult djikstra_path;
};
class MainWindow : public sf::RenderWindow {
    private:
        int width;
        int height;
        int row;
        int col;
        std::vector<Tile> tiles;
        std::vector<std::vector<char>> map;
        return_paths my_return_paths;
        bool v_astar;
        bool v_dijkstra;
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
        Button* statButton;


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
        this->v_astar = false;
        this->v_dijkstra = false;

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
        statButton = new Button(615.f, 720.f, 75.f, 50.f,  font, "Stats");
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
                    std::cout << map[y][x];
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

    void showPath(bool tryAstar) {
        int startRow = -1, startCol = -1;
        int pickupRow = -1, pickupCol = -1;
        int finishRow = -1, finishCol = -1;
        for (int y = 0; y < this->row; y++) {
            for (int x = 0; x < this->col; x++) {
                if (map[y][x] == 'S') {
                    startRow = y;
                    startCol = x;
                }
                if (map[y][x] == 'P') {
                    pickupRow = y;
                    pickupCol = x;

                }
                if (map[y][x] == 'F') {
                    finishRow = y;
                    finishCol = x;
                }
            }
        }
        if (startRow == -1) return;  // no start cell, nothing to do

        if (!tryAstar) {


            bool pushingP = false;


            DjikstraResult result1 = dijkstra(this->map, startRow, startCol, pushingP);

            pushingP = true;

            DjikstraResult result2 = dijkstra(this->map, result1.path.back().first, result1.path.back().second, pushingP);


            for (auto& [r, c] : result1.path) {
                if (map[r][c] == 'S' || map[r][c] == 'P') continue;
                int index = r * this->col + c;
                tiles[index].setState(Tile::TileState::Path);
            }

            for (auto& [r, c] : result2.path) {
                if (map[r][c] == 'S' || map[r][c] == 'F') continue;
                int index = r * this->col + c;
                tiles[index].setState(Tile::TileState::Path2);
            }
            result2.pathLength += result1.pathLength;
            result2.nodesExplored += result1.nodesExplored;
            result2.totalTime += result1.totalTime;
            // maybe extend vector
            my_return_paths.djikstra_path = result2;

        }
        else {

            Point start_pos = {startRow, startCol};
            Point pickup_pos = {pickupRow, pickupCol};
            Point end_pos = {finishRow, finishCol};

            Path_Result path = search_Astar( this -> map, start_pos, pickup_pos );
            Path_Result path2 = search_Astar(this->map, pickup_pos, end_pos);

            path2.cost += path.cost;
            path2.nodes_visited += path.nodes_visited;
            path2.Astar_time += path.Astar_time;
            my_return_paths.path_result = path2;

            for (auto& p : path.final_path) {
                if (map[p.row][p.col] == 'S' || map[p.row][p.col] == 'P') continue;
                int index = p.row * this->col + p.col;
                tiles[index].setState(Tile::TileState::Path);
            }

            for (auto& p : path2.final_path) {
                if (map[p.row][p.col] == 'P' || map[p.row][p.col] == 'F') continue;
                int index = p.row * this->col + p.col;
                tiles[index].setState(Tile::TileState::Path2);
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
                                this->showPath(true);
                                v_astar = true;
                                v_dijkstra = false;
                                // return_paths.djikstra_path
                            }
                            else if (runDijkstraButton->isClicked(mousePos)) {
                                std::cout << "RUN DIJKSTRA" << std::endl;
                                this->showPath(false);
                                v_dijkstra = true;
                                v_astar = false;
                            }
                            else if (resetButton->isClicked(mousePos)) {
                                std::cout << "RESET BUTTON" << std::endl;
                                this->setMap(this->map);
                            }
                            else if (statButton->isClicked(mousePos)) {
                                std::cout << "STAT BUTTON" << std::endl;
                                if (v_dijkstra == true) {
                                    std::cout << "Path len" << my_return_paths.djikstra_path.pathLength << std::endl;
                                    std::cout <<"nodes explored" << my_return_paths.djikstra_path.nodesExplored << std::endl;
                                    std::cout << "Total time" <<my_return_paths.djikstra_path.totalTime << std::endl;
                                    statWindow stats(500, 300, my_return_paths.djikstra_path.nodesExplored ,my_return_paths.djikstra_path.pathLength, my_return_paths.djikstra_path.totalTime);
                                    stats.run();
                                } else {
                                    std::cout << my_return_paths.path_result.cost << std::endl;
                                    std::cout << my_return_paths.path_result.nodes_visited<< std::endl;
                                    statWindow stats(500, 300, my_return_paths.path_result.nodes_visited, my_return_paths.path_result.cost, my_return_paths.path_result.Astar_time);
                                    stats.run();
                                }
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
            statButton->draw(*this);

            display();
        }
    }
};
#endif //DSA_PROJECT2_MAIN_WINDOW_H