//
// Created by omgit on 3/18/2026.
//
#include "warehouse_map.h"
#include "tilesets.h"




WarehouseMap::WarehouseMap(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;

    // THEN RESIZE GRID
    // In C++, the vector resize() is a built-in method used to change the size of vector container after it is declared.
    // It can be used to increase or decrease the size of vector.
    // https://www.geeksforgeeks.org/cpp/vector-resize-c-stl/
    grid.resize(rows, std::vector<char>(cols));
}
void WarehouseMap::fillOpen() {
    // Loop until rows
    for (int row=0; row<rows; row++) {
        // Loop unti cols
        for (int col=0; col<cols; col++) {
            // Set grid[row][col] value to '.'
            grid[row][col] = '.';
        }
    }
}

void WarehouseMap::replaceOpen(std::default_random_engine& ro_Generator) {
    std::uniform_int_distribution<int> distribution(0, 2);

    //std::cout << "RANDOM GENERATOR: " << rand_n << std::endl;
    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            int rand_n = distribution(ro_Generator);
            if (grid[row][col] == '.') {
                if (rand_n != 1 && rand_n != 2) {
                    grid[row][col] = '.';
                }
                else if (rand_n == 1) {
                    grid[row][col] = '^';
                }
                else if (rand_n == 2) {
                    grid[row][col] = '%';
                }
            }
        }
    }
}

void WarehouseMap::addBorderWalls() {
    for (int row=0; row<rows; row++) {
        // RIGHT SIDE and LEFT SIDE
        grid[row][0] = '#';
        grid[row][cols-1] = '#';
    }
    for (int col=0; col<cols; col++) {
        // FIRST ROW
        grid[0][col] = '#';
        // LAST ROW
        grid[rows-1][col] = '#';
    }
}
// SO 22x22 | walls all around so 20x20
// First tile of the warehouse is at grid[1][1]
// From there we create our regions(4x4) each with 5x5 tiles.
// Grid [1][1] -> grid[5][5] | grid[6][6] -> grid[10][10] -> grid[11][11] -> grid[15][15] -> grid[16][16] -> grid[20][20]
// GET A RANDOM TILESET FROM TILESET.H and using random
// loopthru tileset and apply it to grid. repeat this 4 times. and then 4 more times
void WarehouseMap::generateFromTiles(std::default_random_engine& tileset_generator) {

    // Picking a random tileset
    std::uniform_int_distribution<int> distribution(0, tileSets.size()-1);

    int count = 0;
    while (count != 16) {
        //std::cout << gridX << " " << gridY << std::endl;
        int tileSetIndex = distribution(tileset_generator);
        std::vector<std::string>myTileSet = tileSets[tileSetIndex];
        //std::cout << count << std::endl;
        if (count >= 0 && count <= 3) {
            int shift = (count % 4)  * 5;
            // This part should correctly handle region (1,1) -> (1, 4)
            // This handles one region of the map.
            // EVERY ELEMENT
            for (int i=0; i<myTileSet.size(); i++) {
                // EVERY CHAR IN STRING
                for (int j=0; j<myTileSet[i].size(); j++) {
                    //std::cout << "Assinging " << myTileSet[i][j] << "to" << grid[i][j] << std::endl;
                    grid[i+1][j+1+shift] = myTileSet[i][j];
                }
                //this->print();
            }
        }
        if (count >= 4 && count <= 7) {
            int shift = (count % 4)  * 5;

            // This part should correctly handle region (2,1) -> (2, 4)
            // This handles one region of the map.
            // EVERY ELEMENT
            for (int i=0; i<myTileSet.size(); i++) {
                // EVERY CHAR IN STRING
                for (int j=0; j<myTileSet[i].size(); j++) {
                    //std::cout << "Assinging " << myTileSet[i][j] << "to" << grid[i][j] << std::endl;
                    grid[i+6][j+1+shift] = myTileSet[i][j];
                }
                //this->print();
            }
        }
        if (count >= 8 && count <= 11) {
            int shift = (count % 4)  * 5;

            // This part should correctly handle region (3,1) -> (3, 4)
            // This handles one region of the map.
            // EVERY ELEMENT
            for (int i=0; i<myTileSet.size(); i++) {
                // EVERY CHAR IN STRING
                for (int j=0; j<myTileSet[i].size(); j++) {
                    //std::cout << "Assinging " << myTileSet[i][j] << "to" << grid[i][j] << std::endl;
                    grid[i+11][j+1+shift] = myTileSet[i][j];
                }
                //this->print();
            }
        }
        if (count >= 12 && count <= 16) {
            int shift = (count % 4)  * 5;

            // This part should correctly handle region (4,1) -> (4, 4)
            // This handles one region of the map.
            // EVERY ELEMENT
            for (int i=0; i<myTileSet.size(); i++) {
                // EVERY CHAR IN STRING
                for (int j=0; j<myTileSet[i].size(); j++) {
                    //std::cout << "Assinging " << myTileSet[i][j] << "to" << grid[i][j] << std::endl;
                    grid[i+16][j+1+shift] = myTileSet[i][j];
                }
                //this->print();
            }
        }
        count += 1;
    }

}
bool WarehouseMap::inBounds(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
bool WarehouseMap::isWalkable(int row, int col) {
    return inBounds(row, col) && grid[row][col];
}

char WarehouseMap::getCell(int row, int col) {
    return this->grid[row][col];
}
void WarehouseMap::setCell(int row, int col, char value) {
    this->grid[row][col] = value;
}
std::pair<int, int> WarehouseMap::findCell(char target) {
    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            if (grid[row][col] == target) {
                return std::make_pair(row, col);
            }
        }
    }
    return std::make_pair(-1, -1);
}

void WarehouseMap::print() {
    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            std::cout << getCell(row, col) << ' ';
        }
        std::cout << std::endl;
    }
}
std::vector<std::vector<char>>& WarehouseMap::getGrid() {
    return this->grid;
}
void WarehouseMap::placeSpecialCells(std::default_random_engine& pos_Generator) {
    bool s_placed = false;
    bool f_placed = false;
    bool p_placed = false;

    std::uniform_int_distribution<int> distribution(0, 20);
    int positionX = distribution(pos_Generator);
    int positionY = distribution(pos_Generator);
    while (!s_placed || !f_placed || !p_placed) {
        positionX = distribution(pos_Generator);
        positionY = distribution(pos_Generator);


        if ((grid[positionX][positionY] == '.' || grid[positionX][positionY] == '^' || grid[positionX][positionY] == '%' ) && !s_placed) {
            s_placed = true;
            //std::cout << "Placing S at " << positionX << "," << positionY << std::endl;
            grid[positionX][positionY] = 'S';
        }
        if (grid[positionX][positionY] == '#' && !p_placed && (positionX != 0 && positionY != 0 )) {
            p_placed = true;
            //std::cout << "Placing P at " << positionX << "," << positionY << std::endl;
            grid[positionX][positionY] = 'P';
        }
        if ((grid[positionX][positionY] == '.' || grid[positionX][positionY] == '^' || grid[positionX][positionY] == '%' ) && !f_placed && s_placed) {
            f_placed = true;
            //std::cout << "Placing F at " << positionX << "," << positionY << std::endl;
            grid[positionX][positionY] = 'F';
        }

        // Generate random position on grid
        // Check if pos it '.' char
        // If open assign S cell to that pos
        // Otherwise try again


        // P tile should be on some shelf for cool factor
        // Generate random position on grid
        // Check if pos is '#' char
        // assign P cell to that pos
        // Otherwise try again

        // same thing for S but use F
    }
}






