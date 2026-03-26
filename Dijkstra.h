#ifndef DSA_PROJECT2_DIJKSTRA_H
#define DSA_PROJECT2_DIJKSTRA_H

#include <vector>
using namespace std;


struct DjikstraResult {

    vector<std::pair<int,int>> path;
    int pathLength;
    int nodesExplored;
    double totalTime;
};

DjikstraResult dijkstra(vector<vector<char>>& grid, int startRow, int startCol, bool pushingP);

#endif 
