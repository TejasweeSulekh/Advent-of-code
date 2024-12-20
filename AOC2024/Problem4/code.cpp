#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

bool validChecker(std::vector<std::string> &input, char target, int row, int col){
    int rowMax = input.size();
    int colMax = input[0].size();
    if(row < 0 || col < 0){
        return false;
    }
    else if(row >= rowMax || col >= colMax){
        return false;
    }
    else{
        if(input[row][col] == target){
            return true;
        }
    }
    return false;
}

void xmasHelper(std::vector<std::string> &input, int row, int col, int delRow, int delCol, int &occurences){
    std::vector<char> lookup = {'X', 'M', 'A', 'S'};
    int ptr = 0;
    for(int i = 0; i < 4; i++){
        if(validChecker(input, lookup[ptr], row + i*delRow, col + i*delCol)){
            ptr++;
        }
        else{
            break;
        }
    }
    if(ptr == 4){
        occurences++;
    }
}

int checkOccurences(std::vector<std::string> &input, int row, int col){
    int occurences = 0;
    std::vector<int> rowPos = {0, 1, 0, -1, -1, 1, 1, -1};
    std::vector<int> colPos = {1, 0, -1, 0, 1, 1, -1, -1};
    for(int i = 0; i < 8; i++){
        xmasHelper(input, row, col, rowPos[i], colPos[i], occurences);
    }
    return occurences;
}

int xmasFinder(std::vector<std::string> &input, int n){
    int totalXMAS = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(input[i][j] == 'X'){
                totalXMAS += checkOccurences(input, i, j);
            }
        }
    }
    return totalXMAS;
}

int main(){
    std::ifstream f("input.txt");
    std::vector<std::string> input;
    std::string s;
    int n = 0;
    while(getline(f, s)){
        input.emplace_back(s);
        n += 1;
    }
    int result = xmasFinder(input, n);
    std::cout << "The total occurences of XMAS is " << result << std::endl;
    return 0;
}