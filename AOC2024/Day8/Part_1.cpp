#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

void updateVisited(std::vector<std::vector<int>>& visited, int delRow, int delCol, int row, int col, int rowSize, int colSize){
    int newRow = row + 2*delRow;
    int newCol = col + 2*delCol;
    if(newRow < 0 || newCol < 0 || newRow >= rowSize || newCol >= colSize){
        return;
    }
    else{
        visited[newRow][newCol] = 1;
        return;
    }
}

int antinodesFinder(std::unordered_map<char, std::vector<std::pair<int, int>>> &AntennaLocation, std::unordered_set<char> &antennas,
    int colSize, int rowSize){
    std::vector<std::vector<int>> visited(rowSize, std::vector<int>(colSize, 0));
    for(char Antenna: antennas){
        int numAntenna = AntennaLocation[Antenna].size();
        int i = 0;
        for(auto& it: AntennaLocation[Antenna]){
            int row = it.first;
            int col = it.second;
            for(int j = 0; j < numAntenna; j++){
                if(i == j){
                    continue;
                }
                int curRow = AntennaLocation[Antenna][j].first;
                int curCol = AntennaLocation[Antenna][j].second;
                int delRow = curRow - row;
                int delCol = curCol - col;
                updateVisited(visited, delRow, delCol, row, col, rowSize, colSize);
            }
            i++;
        }   
    }
    int totalUniqueAntinodes = 0;
    for(int i = 0; i < rowSize; i++){
        for(int j = 0; j < colSize; j++){
            if(visited[i][j] == 1){
                totalUniqueAntinodes++;
            }
        }
    }
    return totalUniqueAntinodes;
}

int main(){
    std::ifstream f("input.txt");
    // std::ifstream f("misc/testInput.txt");
    std::unordered_map<char, std::vector<std::pair<int, int>>> AntennaLocation; // Stores the antenna location in the grid for one type of antenna
    std::unordered_set<char> antennas;
    std::string s;
    int colSize = 0, rowSize = 0;
    while(getline(f, s)){
        colSize = s.size();
        for(int i = 0; i < colSize; i++){
            char c = s[i];
            if(c != '.'){
                // Antenna found
                antennas.insert(c);
                AntennaLocation[c].emplace_back(std::make_pair(rowSize, i));
            }
        }
        rowSize++;
    }
    
    // // Uncomment this to see how the input is stored
    // std::cout << "The row and column sizes are " << rowSize << " " << colSize << std::endl;
    // std::cout << "The input is as follows " << std::endl;
    // for(auto &c: antennas){
    //     std::cout << "Antenna " << c << std::endl;
    //     for(auto& coords: AntennaLocation[c]){
    //         std::cout << coords.first << ", " << coords.second << std::endl;
    //     }   
    // }

    int UniqueAntinodes = antinodesFinder(AntennaLocation, antennas, colSize, rowSize);

    std::cout << "the number of unique antinodes found is " << UniqueAntinodes << std::endl;

    return 0;
}