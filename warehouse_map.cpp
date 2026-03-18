//
// Created by omgit on 3/18/2026.
//

#include "warehouse_map.h"

#include <iostream>

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

bool WarehouseMap::inBounds(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
bool WarehouseMap::isWalkable(int row, int col) {
    return inBounds(row, col) && grid[row][col];
}

char WarehouseMap::getCell(int row, int col) {
    return grid[row][col];
}
void WarehouseMap::setCell(int row, int col, char value) {
    grid[row][col] = value;
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






