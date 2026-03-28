//
// Created by omgit on 3/16/2026.
//

#ifndef DSA_PROJECT2_MAP_CREATION_H
#define DSA_PROJECT2_MAP_CREATION_H

// This file will be used for calling the WarehouseMap class and
// generating a map and saving that to a csv file
#pragma once
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>

#include "warehouse_map.h"


// We need to ensure that the map is traversable by the algo
// BY TESTING IT WITH ANOTHER F***ING ALGO
// BFS
// https://www.geeksforgeeks.org/dsa/breadth-first-traversal-bfs-on-a-2d-array/
bool canReach(std::vector<std::vector<char>>& map,std::pair<int, int> start, std::pair<int, int> goal) {
    int rows = map.size();
    int cols = map[0].size();
    // Create vector of vector of bools that is of size rows, cols and all values are false
    // Dont process same cell more than once
    std::vector<std::vector<bool>> visitedVec(rows, std::vector<bool>(cols, false));
    std::queue<std::pair<int, int>> map_queue;

    // Start BFS from starting cell
    map_queue.push(start);
    visitedVec[start.first][start.second] = true;

    // Direct vectors
    // (-1, 0)(back) (1,0)(forward) (0,-1)(left) (0,1)(right)
    std::vector<int> row_direction{-1, 1, 0, 0};
    std::vector<int>  col_direction{0, 0, -1, 1};
    // SEARCH WHILE THERE ELEMENTS IN THE QUEUE
    while (!map_queue.empty()) {
        // Everything in queue is int int pair
        std::pair<int, int> curr = map_queue.front();
        map_queue.pop();
        // BASE IF WE SUCESSFULLY FOUND GOAL
        if (curr == goal) {
            return true;
        }
        for (int i = 0; i < 4 ; i++) {
            // curr is the first position of the queue [x, y]
            // we loop thru our 4 different position the robot could poisiton itself
            // and explore
            int n_row = curr.first + row_direction[i];
            int n_col = curr.second + col_direction[i];

            // if new row & col inside grid | not visitied | not a wall
            if (n_row >= 0 && n_row < rows && n_col >= 0 && n_col < cols) { // INSIDE GRID
                if (!visitedVec[n_row][n_col] ) { // IF THE VALUE LOCATED AT CELL IS FALSE
                    if (map[n_row][n_col] != '#') {
                        // marked visited
                        visitedVec[n_row][n_col] = true;

                        // Add it to q so we continue exploring
                        map_queue.push({n_row, n_col});
                    }
                }
            }
        }
    }
    return false;
}
//
void saveToCSV(std::ofstream& csvFile, int map_id, std::vector<std::vector<char>> grid) {
    if (!csvFile.is_open()) {
        std::cerr << "ERROR UR COOKED" << std::endl;
        return;
    }
    if (map_id == 0 ) {
        csvFile << "map_id" << "," << "map";
        csvFile << "\n";
    }
    csvFile << map_id << ",";
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            csvFile << grid[i][j] << ",";
        }
    }
    csvFile << "\n";
    std::cout << "Map "<< map_id << " saved"<<std::endl;

    return;
}

std::vector<std::vector<char>> loadFromCSV(std::ifstream& csvFile, int map_id) {
    std::string line;
    if (!csvFile.is_open()) {
        std::cerr << "ERROR UR COOKED" << std::endl;
    }
    std::vector<std::vector<char>> map;
    for (int i = 0; i != map_id; i++) {
        std::getline(csvFile, line);
    }
    std::stringstream ss(line);
    map.resize(22, std::vector<char>(22));
    //std::cout << ss.str() << std::endl;
    std::string newMap;
    for (int i=0; i<ss.str().size(); i++) {
        if (ss.str()[i] ==  '.' || ss.str()[i] == '#' || ss.str()[i] == '^' || ss.str()[i] == '%' || ss.str()[i] == 'P' || ss.str()[i] == 'F' || ss.str()[i] == 'S') {
            //std::cout << ss.str()[i] << std::endl;
            newMap += ss.str()[i];
        }
    }
    //std::cout << newMap;
    for (int j=0; j<22; j++) {
        for (int k=0; k<22; k++) {
            int index = j*22 + k;
            //std:: cout << index << std::endl;
            map[j][k] = newMap[index];
            //std::cout << map[j][k] << std::endl;
        }
    }
    return map;


}




// from main take in map idx

std::vector<std::vector<char>> create_map(std::default_random_engine& gen) {
    int rows = 22;
    int cols = 22;
    bool canSolve = false;
    while (!canSolve) {
        WarehouseMap warehouseMap = WarehouseMap(rows, cols);
        warehouseMap.fillOpen();
        warehouseMap.addBorderWalls();
        warehouseMap.generateFromTiles(gen);
        warehouseMap.replaceOpen(gen);
        warehouseMap.placeSpecialCells(gen);
        std::pair<int,int> start = warehouseMap.findCell('S');
        std::pair<int,int> goal = warehouseMap.findCell('F');
        std::pair<int,int> item = warehouseMap.findCell('P');
        //std::cout << canReach(warehouseMap.getGrid(), start, item) << " AND " << canReach(warehouseMap.getGrid(), item, goal) << std::endl;
        if (canReach(warehouseMap.getGrid(), start, item) && canReach(warehouseMap.getGrid(), item, goal )){
            //warehouseMap.print();
            canSolve = true;
            //create_count++;
            //std::cout << create_count  << std::endl;
            return  warehouseMap.getGrid();
        }
    }
    // SHOULD NEVER REACH BUT
    return std::vector<std::vector<char>>();
}
#endif //DSA_PROJECT2_MAP_CREATION_H