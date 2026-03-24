//
// Created by omgit on 3/18/2026.
//

#ifndef DSA_PROJECT2_WAREHOUSE_MAP_H
#define DSA_PROJECT2_WAREHOUSE_MAP_H
#include <random>
#include <vector>
// Map is a 20x20 grid
// consider
// . open
// # blocked
// S - Start | P - Pickup | F - Finish

// We want to generate pattern of tiles not just randoms cell
// DIVIDE AND CONQUER -> We want 20x20 -> 400 cells
// Split 20x20 -> 4x4 regions contain 25 tiles
// Board will be made up of 4 tiles across 4 tiles down
// Each tileset is randomly chosen
// 20x20 map -> 4x4 tileset -> each region is 5x5 tiles
// WE WILL DEFINE OUR TILE TEMPLATE THAT WILL RANDOMLY BE USED

class WarehouseMap {
private:
    std::vector<std::vector<char>> grid;
    int rows;
    int cols;


public:
    WarehouseMap(int rows=20, int cols=20);

    // Fills every cell in the grid with open marker ('.')
    void fillOpen();

    // Places walls around outer border of the warehouse map
    void addBorderWalls();

    // Builds the warehouse layour by randomly selecting and
    // placing tilesets into grid
    void generateFromTiles(std::default_random_engine& ts_gen);

    // RANDOMLY places special cells "S", "P" and "F"
    // on valid open positions
    void placeSpecialCells(std::default_random_engine& pos_gen);

    // Returns true if given row and col are insidide bounds
    bool inBounds(int row, int col);

    // Returns true if the given cell is inside the grid
    // and not blocked by a wall or obstacle.
    bool isWalkable(int row, int col);

    // Returns character stored at the given grid position
    char getCell(int row, int col);

    // Sets the given grid position to the specified character
    // value
    void setCell(int row, int col, char value);

    // Searches grid for target character
    // Returns cords or -1-1 if not found
    std::pair<int, int> findCell(char target);

    void print();
    // returns grid vector of vector of chars
    std::vector<std::vector<char>>& getGrid();
};


#endif //DSA_PROJECT2_WAREHOUSE_MAP_H