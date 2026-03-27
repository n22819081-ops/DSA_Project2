#include "AStar.h"
#include <queue>
#include <algorithm>
#include <limits>
#include <cmath>
#include <chrono>
using namespace std;




//Manhattan distance equation to get a good estimate of the distance for our heuristic function.
static int manhattan_distance (Point p, Point q) {
    return abs(p.row - q.row) + abs(p.col - q.col);
}


//helper to check if the position thats being checked is inside the map or not.
static bool inside_map (int row, int col, int total_rows, int total_cols) {
    return row >= 0 && row < total_rows && col >= 0 && col < total_cols;

}


//checks if cell is a wall
static bool is_wall(char cell) {
    return cell == '#';
}

static int get_tile_cost(char cell) {
    if (cell == '.') {
        return 1;
    }
    else if (cell == '^') {
        return 3;
    }
    else {
        return 2;
    }
}


// The main A* search function 
Path_Result search_Astar(const vector<vector<char>>& grid, Point start_pos, Point end_pos) {


    //the result thats gets returned at the end of the function
    Path_Result sol_result;
    auto start_time = chrono::high_resolution_clock::now();

//gets the amount of rows and columns in the grid.
    int total_rows = grid.size();
    int total_cols = total_rows > 0 ? grid[0].size() : 0;


    //checks if grid is empty, if start and end positions are inside the grid and if they are not walls.
    if (total_rows == 0 || total_cols == 0 || !inside_map(start_pos.row, start_pos.col, 
        total_rows, total_cols) ||
        !inside_map(end_pos.row, end_pos.col, total_rows, total_cols) ||
        is_wall(grid[start_pos.row][start_pos.col]) ||
        is_wall(grid[end_pos.row][end_pos.col])  ) {

        auto finish_time = chrono::high_resolution_clock::now();
        sol_result.Astar_time = chrono::duration<double>(finish_time - start_time).count();

        return sol_result;
    }


    //since no infinity this is the best I can do, unless there is then lemme know 
    const int bigNumber = numeric_limits<int>::max();

    //2d vector that stores the current lowest cost to get the the cell.
    //stores the parent cell to build the path at the end.
    //stores if the cell has been checked or not.
    vector<vector<int>> curr_shortest_path(total_rows, vector<int>(total_cols, bigNumber));
    vector<vector<Point>> parent_cell(total_rows, vector<Point>(total_cols, {-1, -1}));
    vector<vector<bool>> been_checked(total_rows, vector<bool>(total_cols, false));


    //Node used for the priority queue
    struct Node {
        int total, curr_cost, node_row, node_col;
    };


    //compares the cost of the nodes in the priority so the lowest total gets picked first.
    struct NodeCompare {
        bool operator() (const Node& p, const Node& q) const {
            return p.total > q.total; 
        }
    };


    //makes the priority queue that stores the unchecked cells.
    priority_queue<Node, vector<Node>, NodeCompare> unchecked_cells;


    //gets the cost of the start position and adds it to the priority queue.
    curr_shortest_path[start_pos.row][start_pos.col] = 0;
    unchecked_cells.push({manhattan_distance(start_pos, end_pos), 0, start_pos.row, start_pos.col});

    int row_dir[4] = {-1, 1, 0, 0};
    int col_dir[4] = {0, 0, -1, 1};

    while (!unchecked_cells.empty()) {

        Node curr_node = unchecked_cells.top();
        unchecked_cells.pop();


        if (been_checked[curr_node.node_row][curr_node.node_col]) {
            continue; 
        }
        been_checked[curr_node.node_row][curr_node.node_col] = true;

        sol_result.nodes_visited++;
        sol_result.visited_order.push_back({curr_node.node_row, curr_node.node_col});

        
        if (curr_node.node_row == end_pos.row && curr_node.node_col == end_pos.col) {
            sol_result.found = true;
            sol_result.cost = curr_shortest_path[end_pos.row][end_pos.col];
            
            Point temp_pos = end_pos;

            while (!(temp_pos.row == -1 && temp_pos.col == -1)) {
                sol_result.final_path.push_back(temp_pos);
                temp_pos = parent_cell[temp_pos.row][temp_pos.col];
            }

            reverse(sol_result.final_path.begin(), sol_result.final_path.end());
            auto finish_time = chrono::high_resolution_clock::now();
            sol_result.Astar_time = chrono::duration<double>(finish_time - start_time).count();

            return sol_result;

        }

        for (int i = 0; i <4; i++) {

            int nr = curr_node.node_row + row_dir[i];
            int nc = curr_node.node_col + col_dir[i];

            if (!inside_map(nr, nc, total_rows, total_cols) || is_wall(grid[nr][nc]) || been_checked[nr][nc]) {
                continue; 
            }

            int temp_cost = curr_shortest_path[curr_node.node_row][curr_node.node_col] + get_tile_cost(grid[nr][nc]);

            if (temp_cost < curr_shortest_path[nr][nc]) {
                curr_shortest_path[nr][nc] = temp_cost;
                parent_cell[nr][nc] = {curr_node.node_row, curr_node.node_col};
                unchecked_cells.push({temp_cost + manhattan_distance({nr, nc}, end_pos), temp_cost, nr, nc});
            }
        }
    }

    auto finish_time = chrono::high_resolution_clock::now();
    sol_result.Astar_time = chrono::duration<double>(finish_time - start_time).count();
    return sol_result;



}
