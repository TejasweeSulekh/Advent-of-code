#include <iostream>
#include <fstream>
#include <string>
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

bool xmasHelper(std::vector<std::string> &input, int row, int col, int delRow, int delCol, int &occurrences, int cnt
                , std::vector<char> &lookup){
    int ptr = 0;
    for(int i = 0; i < cnt; i++){
        if(validChecker(input, lookup[ptr], row + i*delRow, col + i*delCol)){
            ptr++;
        }
        else{
            break;
        }
    }
    if(ptr == cnt){
        occurrences++;
        return true;
    }
    return false;
}

int checkoccurrences(std::vector<std::string> &input, int row, int col){
    int occurrences = 0;
    std::vector<int> rowPos = {0, 1, 0, -1, -1, 1, 1, -1};
    std::vector<int> colPos = {1, 0, -1, 0, 1, 1, -1, -1};
    std::vector<char> lookup = {'X', 'M', 'A', 'S'}; // For part 1
    int cnt = 4;

    for(int i = 0; i < 8; i++){
        bool temp = xmasHelper(input, row, col, rowPos[i], colPos[i], occurrences, cnt, lookup);
    }
    return occurrences;
}

int xmasFinder(std::vector<std::string> &input, int n){
    int totalXMAS = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(input[i][j] == 'X'){
                totalXMAS += checkoccurrences(input, i, j);
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
    std::cout << "The total occurrences of XMAS is " << result << std::endl; // Part 1
    return 0;
}