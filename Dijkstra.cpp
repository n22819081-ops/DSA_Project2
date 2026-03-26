#include "Dijkstra.h"
#include <queue>
#include <tuple>
#include <climits>
#include <algorithm>
using namespace std;

vector<pair<int,int>> dijkstra(vector<vector<char>>& grid, int startRow, int startCol, bool pushingP) {

    //First off intiailize the rows and columns of our grid 
    int totalRows = grid.size();
    int totalCols = grid[0].size();

   

  
   //Vector to store the node distances within and also a vector to be able to trace our steps for the actual path 

    vector<vector<int>> nodeDistance(totalRows, vector<int>(totalCols, INT_MAX));

   
    vector<vector<pair<int,int>>> previousNode(totalRows, vector<pair<int,int>>(totalCols, {-1, -1}));

    
    //priority queue to rank nodes from least to greatest 
    priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;

    nodeDistance[startRow][startCol] = 0;
    pq.emplace(0, startRow, startCol);

    
    int rowOffset[] = {-1, 1, 0, 0};
    int colOffset[] = {0, 0, -1, 1};

    int goalRow = -1;
    
    int goalCol = -1;


    
    while (!pq.empty()) {
        auto [distance, currentRow, currentCol] = pq.top();
        pq.pop();

      
        //determines if the path is 'stale' or already covered 
        if (distance > nodeDistance[currentRow][currentCol])
            continue;


        

        //Go to P then F
        if (grid[currentRow][currentCol] == 'P') {
            
            goalRow = currentRow;
            goalCol = currentCol;
            
        }


        if ((grid[currentRow][currentCol] == 'F') && (pushingP == true)) {
        
            goalRow = currentRow;
            goalCol = currentCol;
            
            
        }


      //loop through four times as we can go up, down, right, or left 
        for (int i = 0; i < 4; i++) {
            int neighborRow = currentRow + rowOffset[i];
            int neighborCol = currentCol + colOffset[i];  

            int tileWeight = 1;

      //make sure we remain inbounds 
            if (neighborRow < 0 || neighborRow >= totalRows ||
                neighborCol < 0 || neighborCol >= totalCols)
                continue;

            //just continue if a # as this is a wall 
            if (grid[neighborRow][neighborCol] == '#')
                continue;

            if (grid[neighborRow][neighborCol] == '.') {
                tileWeight = 1; 
                } else if (grid[neighborRow][neighborCol] == '^') {
                tileWeight = 3;
                }
            else {
                tileWeight = 2;
            }

            


          //checks to see if there is a faster path and updates vectors in case there is one 
            int newDist = nodeDistance[currentRow][currentCol] + tileWeight;

            if (newDist < nodeDistance[neighborRow][neighborCol]) {

                nodeDistance[neighborRow][neighborCol] = newDist;
                previousNode[neighborRow][neighborCol] = {currentRow, currentCol};
                pq.emplace(newDist, neighborRow, neighborCol);
            }
        }
    }

  //putting it altogether we can build and return our path 
    vector<pair<int,int>> robotPath;

    if (goalRow == -1) {
        return robotPath;
    }

    while (!(goalRow == startRow && goalCol == startCol)) {
        robotPath.push_back({goalRow, goalCol});
        auto [prevRow, prevCol] = previousNode[goalRow][goalCol];
        goalRow = prevRow;
        goalCol = prevCol;
    }
    robotPath.push_back({startRow, startCol});
    reverse(robotPath.begin(), robotPath.end());
    return robotPath;
}
