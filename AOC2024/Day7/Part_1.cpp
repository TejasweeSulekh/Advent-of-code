#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

int possibleEquationCounter(){
    return -1;
}


int main(){
    std::ifstream f("misc/testInput.txt");
    std::string s;
    std::stringstream ss;
    std::vector<std::pair<int, std::vector<int>>> input;
    while(getline(f, s)){
        // std::cout << s.find(':') << std::endl;
        int totalPtr = s.find(':');
        int total = std::stoi(s.substr(0, totalPtr)); // Fetches the total value
        std::string VectorString(s.begin() + totalPtr+1, s.end());

    }
    return 0;
}