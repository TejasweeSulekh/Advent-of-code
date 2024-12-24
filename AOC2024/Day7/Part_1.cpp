#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

bool possibleEquationFinder(long long total, int idx, std::vector<int> &operands, long long &curSum, int n){
    if(idx >= n){
        return total == curSum;
    }
    bool mul = false, add = false;
    long long mulCurSum = 0;
    mulCurSum = curSum*operands[idx];
    mul = possibleEquationFinder(total, idx+1, operands, mulCurSum, n);
    long long addCurSum = curSum + operands[idx];
    add = possibleEquationFinder(total, idx+1, operands, addCurSum, n);

    return mul || add;
}

long long possibleEquationCounter(std::vector<std::pair<long long, std::vector<int>>> &input){
    int n = input.size();
    long long counter = 0;
    for(int i = 0; i < n; i++){
        // if(counter < 0){
        //     std::cout << "Overflow observed" <<std::endl;
        // }
        // The target value
        long long total = input[i].first;
        // The length of operands
        int length = input[i].second.size();
        long long CurTarget = input[i].second[0];
        bool check = possibleEquationFinder(total, 1, input[i].second, CurTarget, length);
        if(check){
            counter += total;
            // std::cout << "Value of the counter: " << counter << std::endl;
            // counter++;
        }
    }
    return counter;
}


int main(){
    std::ifstream f("input.txt");
    std::string s;
    std::vector<std::pair<long long, std::vector<int>>> input;
    while(getline(f, s)){
        // find the pointer for the first number ending which is the total
        int totalPtr = s.find(':');
        std::string totalString = s.substr(0, totalPtr);
        long long total = std::stol(s.substr(0, totalPtr)); // Fetches the total value

        // Seperates the vector string
        std::string VectorString(s.begin() + totalPtr+2, s.end()), tempS;
        // Puts the string in stringstream for seperating by ' '
        std::stringstream ss(VectorString);
        std::vector<int> temp;
        // Fetches numbers
        while(getline(ss, tempS, ' ')){
            temp.emplace_back(std::stoi(tempS)); // Stores the vector
        }
        input.emplace_back(make_pair(total, temp)); // Push it back into the input string
    }
    long long totalPossibleEquations = possibleEquationCounter(input);
    std::cout << "The total number of equations which are possible are " << totalPossibleEquations << std::endl;
    return 0;
}