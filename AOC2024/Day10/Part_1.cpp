#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int CountTrailHeads(std::vector<std::vector<int>>& grid, int row, int col,
    int rowSize, int colSize, std::vector<std::vector<int>> &visited){
    
    if(grid[row][col] == 9){
        visited[row][col] = 1;
        return 1;
    }
    else if(grid[row][col] > 9){
        visited[row][col] = 1;
        return 0;
    }
    int counter = 0;
    visited[row][col] = 1;
    std::vector<int> delRow = {0, 0, 1, -1};
    std::vector<int> delCol = {1, -1, 0, 0};
    for(int i = 0; i < 4; i++){
        int newRow = row + delRow[i];
        int newCol = col + delCol[i];
        bool valid = newRow < rowSize && newCol < colSize && newRow >= 0 && newCol >= 0;
        if(valid){
            bool possible = (visited[newRow][newCol] == 0) && (grid[newRow][newCol] - grid[row][col] == 1);
            if(possible){
                counter += CountTrailHeads(grid, newRow, newCol,  rowSize, colSize, visited);
            }
        }
    }
    return counter;
}

int scoreCalculator(std::vector<std::vector<int>>& grid, std::vector<std::pair<int, int>>& startingPoint, int rowSize, int colSize){
    int totalScore = 0;
    int StartingPoints = startingPoint.size();
    for(int i = 0; i < StartingPoints; i++){
        auto& it = startingPoint[i];
        int row = it.first;
        int col = it.second;
        std::vector<std::vector<int>> visited(rowSize, std::vector<int>(colSize, 0));
        totalScore += CountTrailHeads(grid, row, col, rowSize, colSize, visited);
    }
    return totalScore;
}



int main(){
    // std::ifstream f("misc/testInput.txt");
    std::ifstream f("input.txt");
    std::string s;
    std::vector<std::vector<int>> grid;
    std::vector<std::pair<int, int>> startingPoint;
    int rowsize = 0, colsize = 0;
    while(getline(f, s)){
        std::vector<int> tempVec;
        colsize = s.size();
        for(int i = 0; i < colsize; i++){
            int temp;
            std::string ch = s.substr(i, 1);
            temp = std::stoi(ch);
            if(temp == 0){
                startingPoint.emplace_back(std::make_pair(rowsize, i));
            }
            // std::cout << temp << " ";
            tempVec.emplace_back(temp);
        }
        // std::cout << std::endl;
        grid.emplace_back(tempVec);
        rowsize++;
    }
    int score = scoreCalculator(grid, startingPoint, rowsize, colsize);
    std::cout << "The total score accumulated for each trailheads is " << score << std::endl;

    return 0;
}