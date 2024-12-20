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

bool xmasHelper(std::vector<std::string> &input, int row, int col, int delRow, int delCol, int &occurences, int cnt
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
        occurences++;
        return true;
    }
    return false;
}

int checkOccurences(std::vector<std::string> &input, int row, int col){
    int occurences = 0;
    std::vector<int> rowPos = {0, 1, 0, -1, -1, 1, 1, -1};
    std::vector<int> colPos = {1, 0, -1, 0, 1, 1, -1, -1};
    std::vector<char> lookup = {'X', 'M', 'A', 'S'}; // For part 1
    int cnt = 4;

    for(int i = 0; i < 8; i++){
        bool temp = xmasHelper(input, row, col, rowPos[i], colPos[i], occurences, cnt, lookup);
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

void setOrient(int &rowDiff, int &colDiff, int &rowLim, int &rowStart, int &colLim, int &colStart, bool forwards, bool horizontal){
    if(horizontal){
        rowDiff = 2;
        if(forwards){
            rowStart = 0;
            colStart = 0;
            rowLim = 2;
            colLim = 2;
        }
        else{
            rowStart = 0;
            colStart = 2;
            rowLim = 2;
            colLim = 0;
        }
    }
    else{
        colDiff = 2;
        if(forwards){
            rowStart = 0;
            colStart = 0;
            rowLim = 2;
            colLim = 2;
        }
        else{
            rowStart = 2;
            colStart = 0;
            rowLim = 0;
            colLim = 2;
        }
    }
}

void XmasHelper2(std::vector<std::string> &input, int &occurences, std::vector<char> &lookup, std::vector<int> &directions, bool horizontal, bool forwards){
    int maxRow = input.size(), maxCol = input[0].size();
    int cnt = 3; // The amount of words we are looking for
    int dummyCount = 0;
    int rowDiff = 0, colDiff = 0, rowLim = 2, colLim = 2, rowStart = 0, colStart = 0;
    setOrient(rowDiff, colDiff, rowLim, rowStart, colLim, colStart, forwards, horizontal);
    for(int row = rowStart; row < maxRow-rowLim; row++){
        for(int col = colStart; col < maxCol-colLim; col++){
            // Check for the occurece of one MAS {1, 1} (direction)
            bool X_MAS = xmasHelper(input, row, col, directions[0], directions[1], dummyCount, cnt, lookup);
            X_MAS &= xmasHelper(input, row + rowDiff, col + colDiff, directions[2], directions[3], dummyCount, cnt, lookup); // Checks for the presence of the second MAS
            if(X_MAS){
                occurences++;
            }
        }
    }
}


int XmasPart2(std::vector<std::string> &input, int n){
    int totalXmas = 0;
    std::vector<char> lookup = {'M', 'A', 'S'}; // For part 2
    
    // Checking in horizontal direction
    bool horizontal = true;
    bool forwards = true; // The nature of movement
    //Check horizontally
    std::vector<int> directions = {1, 1, -1, 1}; // {delRow1, delCol1, delRow2, delCol2}
    XmasHelper2(input, totalXmas, lookup, directions, horizontal, forwards); 

    //Check backwards
    forwards = false;
    directions = {1, -1, -1, -1};
    XmasHelper2(input, totalXmas, lookup, directions, horizontal, forwards);

    // Checking in vertical direction
    horizontal = false;
    forwards = true;
    //Check downwards
    directions = {1, 1, 1, -1};
    XmasHelper2(input, totalXmas, lookup, directions, horizontal, forwards);

    //Check upwards
    forwards = false;
    directions = {-1, 1, -1, -1};
    XmasHelper2(input, totalXmas, lookup, directions, horizontal, forwards);
    
    // Return the total X-MAS found
    return totalXmas;
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
    std::cout << "The total occurences of XMAS is " << result << std::endl; // Part 1
    int x_mas = XmasPart2(input, n);
    std::cout << "The total occurences of X-MAS is " << x_mas << std::endl; // Part 2
    return 0;
}