#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void directionUpdater(int& direc){
    if(direc == 3){
        direc = 0;
    }
    else{
        direc++;
    }
    return;
}

bool inBound(int row, int col, int rowSize, int colSize){
    if(row < 0 || col < 0 || row >= rowSize || col >= colSize){
        return false;
    }
    else{
        return true;
    }
}

bool pathTraverser(int row, int col, long uniqueCounter, int rowSize, int colSize, std::vector<std::pair<int, int>> &Directions, 
    std::vector<std::vector<bool>> &visited, std::vector<std::vector<char>> &grid){
    int lastNewRow = row, lastNewCol = col;
    int direc = 0;
    while(inBound(row, col, rowSize, colSize)){
        int newRow = row + Directions[direc].first;
        int newCol = col + Directions[direc].second;
        if(!inBound(newRow, newCol, rowSize, colSize)){
            return false;
        }
        if(grid[newRow][newCol] != '#'){ //No obstacle
            row = newRow;
            col = newCol;
            if((row == lastNewRow) && (col == lastNewCol)){
                return true;
            }
            if(!visited[row][col]){
                lastNewCol = col;
                lastNewRow = row;
                visited[row][col] = 1;
                uniqueCounter++;
            }
        }
        else{ // Obstacle found
            directionUpdater(direc);
        }
    }
    return true;
}

void ObstacleCounter(int row, int col, long &uniqueCounter, int rowSize, int colSize, std::vector<std::pair<int, int>> &Directions, 
    std::vector<std::vector<bool>> &visited, std::vector<std::vector<char>> &grid){
    long temp = 0;
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            std::vector<std::vector<bool>> tempVisited(rowSize, std::vector<bool>(colSize, 0));
            tempVisited[row][col] = 1;
            // Check if the guard even goes through that path
            if(visited[i][j] == 0){
                continue;
            }
            // Test if adding an obstacle there is helpful or not
            if(grid[i][j] != '#' && !(i == row && j == col)){
                grid[i][j] = '#'; // Add obstacle
                // Check if a loop happens
                if(pathTraverser(row, col, temp, rowSize, colSize, Directions, tempVisited, grid)){
                    uniqueCounter++;
                }
                grid[i][j] = '.'; // Remove obstacle
            }
        }
    }
    return;
}

long UniquePathUsedFinder(std::vector<std::vector<char>> &grid, int row, int col){
    int rowSize = grid.size(), colSize = grid[0].size();
    if(rowSize == 0){
        std::cout << "Empty grid found therefore the unique paths traversed is " << 0 << std::endl;
        return 0;
    }
    std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, 0)); //Visited array stored bool i.e. visited or not visited
    std::vector<std::pair<int, int>> Directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Direction which the guard is facing
    long uniqueCounter = 1;
    visited[row][col] = 1;
    // if part 1
    pathTraverser(row, col, uniqueCounter, rowSize, colSize, Directions, visited, grid);
    uniqueCounter = 0; // Resetting the counter
    ObstacleCounter(row, col, uniqueCounter, rowSize, colSize, Directions, visited, grid);

    return uniqueCounter;
}



int main(){
    std::ifstream f("input.txt");
    std::string s;
    std::vector<std::vector<char>> grid;
    int row = 0, col = 0; // The starting index (0-based indexing)
    bool start = true;
    while(getline(f, s)){
        std::vector<char> tempRow(s.begin(), s.end());
        grid.emplace_back(tempRow);
        int temp = s.find("^");
        if(temp != -1){
            col = temp;
            start = false;
        }
        if(start){
            row++;
        }
    }
    // std::cout << row << " " << col << std::endl;
    long uniqueCounter = 0;
    uniqueCounter = UniquePathUsedFinder(grid, row, col);
    std::cout << "Possible obstacle placements are " << uniqueCounter << std::endl;
    return 0;
}