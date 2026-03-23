vector<int> dijkstra(vector<vector<pair<int,int>>>& adj, int src) {

    int totalRows = grid.size();
    int totalCols = grid[0].size();

    priority_queue<tuple<int,int,int> vector<tuple<int, int, int>>, greater<tuple<int, int, int>>> pq;

    vector<int> nodeDistance(graphSize, INT_MAX);

    nodeDistance[startRow][starCol] = 0;
    pq.emplace(0, startRow, startCol);


     int rowOffset[] = {-1, 1, 0, 0};
     int colOffset[] = {0, 0, -1, 1};


    while (!pq.empty()) {
        
        auto [distanceValue, currentRow, currentCol] = pq.top();
        pq.pop();


         if (distanceValue > nodeDistance[currentRow][currentCol])
            continue;



    for (int i = 0; i < 4; i++) {

        
        int neighborRow = currentRow + rowOffset[i];
        int neighborCol = currentRow + colOffset[i];


        int edgeWeight = 1;
    

        if grid[neighborRow][neighborCol] == '*' {   //assuming I have a vector that holds the actual map data 
            continue;
        }


        if (neighborRow < 0 || neighborRow >= totalRows || neighborCol < 0 || neighborCol >= totalCols) {
            continue;
        }



           if (nodeDistance[currentRow][currentCol] + edgeWeight < nodeDistance[neighborRow][neighborCol]) {
                nodeDistance[neighborRow][neighborCol] = nodeDistance[currentRow][currentCol] + 1;   
                pq.emplace(distance, neighborRow, neighborCol);
            }
        }
    }


    return nodeDistance;
}



