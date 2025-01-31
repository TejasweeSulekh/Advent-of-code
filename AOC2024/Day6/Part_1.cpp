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

bool pathTraverser(int row, int col, long &uniqueCounter, int rowSize, int colSize, std::vector<std::pair<int, int>> &Directions, 
    std::vector<std::vector<bool>> &visited, std::vector<std::vector<char>> &grid, int &direc){
    while(inBound(row, col, rowSize, colSize)){
        int newRow = row + Directions[direc].first;
        int newCol = col + Directions[direc].second;
        if(!inBound(newRow, newCol, rowSize, colSize)){
            return false;
        }
        if(grid[newRow][newCol] != '#'){ //No obstacle
            row = newRow;
            col = newCol;
            if(!visited[row][col]){
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

long UniquePathUsedFinder(std::vector<std::vector<char>> &grid, int row, int col){
    int rowSize = grid.size(), colSize = grid[0].size();
    if(rowSize == 0){
        std::cout << "Empty grid found therefore the unique paths traversed is " << 0 << std::endl;
        return 0;
    }
    std::vector<std::vector<bool>> visited(rowSize, std::vector<bool>(colSize, 0)); //Visited array stored bool i.e. visited or not visited
    std::vector<std::pair<int, int>> Directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Direction which the guard is facing
    int direc = 0;
    long uniqueCounter = 1;
    visited[row][col] = 1;
    // if part 1
    pathTraverser(row, col, uniqueCounter, rowSize, colSize, Directions, visited, grid, direc);

    return uniqueCounter;
}



int main(){
    std::ifstream f("testInput.txt");
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
    long uniqueCounter = UniquePathUsedFinder(grid, row, col);
    std::cout << "The unique path blocks traversed are " << uniqueCounter << std::endl;

    return 0;
}