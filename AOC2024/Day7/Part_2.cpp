#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

long concater(long op1, long op2){
    std::string resultS = "";
    resultS = std::to_string(op1) + std::to_string(op2);
    long result = std::stol(resultS);
    return result;
}

bool possibleEquationFinder(long long total, int idx, std::vector<long> operands, long long curSum, int n){
    if(idx >= n){
        return total == curSum;
    }
    bool mul = false, add = false, con = false;
    long long mulCurSum = 0;
    if(idx == 0){
        mulCurSum = operands[0];
    }
    else{
        mulCurSum = curSum*operands[idx];
    }
    mul = possibleEquationFinder(total, idx+1, operands, mulCurSum, n);
    long long addCurSum = curSum + operands[idx];
    add = possibleEquationFinder(total, idx+1, operands, addCurSum, n);
    if(idx > 0){
        long newVal = concater(curSum, operands[idx]);
        con = possibleEquationFinder(total, idx+1, operands, newVal, n);
    }

    return ((mul || add) || con);
}



long long possibleEquationCounter(std::vector<std::pair<long long, std::vector<long>>> &input){
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
        long long CurTarget = 0;
        bool check = possibleEquationFinder(total, 0, input[i].second, CurTarget, length);
        if(check){
            counter += total;
            // std::cout << "Value of the counter: " << counter << std::endl;
            // counter++;
        }
    }
    return counter;
}


int main(){
    // If using the test input
    std::ifstream f("input.txt");

    // Original input
    // std::ifstream f("input.txt");
    std::string s;
    std::vector<std::pair<long long, std::vector<long>>> input;
    while(getline(f, s)){
        // find the pointer for the first number ending which is the total
        int totalPtr = s.find(':');
        std::string totalString = s.substr(0, totalPtr);
        long long total = std::stol(s.substr(0, totalPtr)); // Fetches the total value

        // Seperates the vector string
        std::string VectorString(s.begin() + totalPtr+2, s.end()), tempS;
        // Puts the string in stringstream for seperating by ' '
        std::stringstream ss(VectorString);
        std::vector<long> temp;
        // Fetches numbers
        while(getline(ss, tempS, ' ')){
            temp.emplace_back(std::stol(tempS)); // Stores the vector
        }
        input.emplace_back(make_pair(total, temp)); // Push it back into the input string
    }
    long long totalPossibleEquations = possibleEquationCounter(input);
    std::cout << "The total number of equations which are possible are " << totalPossibleEquations << std::endl;
    return 0;
}