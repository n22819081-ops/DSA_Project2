#pragma once
#include <vector>

struct Point {
    int row;
    int col;

};

struct Path_Result {

    bool found = false; 

    std::vector<Point> final_path;
    std::vector<Point> visited_order;
    double Astar_time = 0.0;
    int nodes_visited = 0;
    int cost = 0;

    

    

    
};

Path_Result search_Astar(const std::vector<std::vector<char>>& grid, Point start_pos, Point end_pos);