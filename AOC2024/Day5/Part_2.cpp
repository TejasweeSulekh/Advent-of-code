#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <sstream>

// Parses through the string to seperate comma seperated integers
std::vector<std::vector<int>> stringParser(std::vector<std::string> inputCommands){
    int n = inputCommands.size();
    std::vector<std::vector<int>> finalOutput;
    for(int i = 0; i < n; i++){
        std::vector<int> tempVec;
        std::stringstream ss(inputCommands[i]); // put the string in stringstream

        while(ss.good()){
            std::string substr;
            getline(ss, substr, ','); // fetches the substring that first occurs until ',' is encountered
            int tempInt = std::stoi(substr);
            tempVec.emplace_back(tempInt); // Store it in vector;
        }
        finalOutput.emplace_back(tempVec);
    }
    return finalOutput;
}

bool validityChecker(std::vector<int> &commandLine, std::unordered_map<int, std::vector<int>> conditionalMap, std::unordered_set<int> &PageSet){
    int n = commandLine.size();
    for(int i = 0; i < n; i++){
        int curr = commandLine[i];
        for(int num : conditionalMap[curr]){ // Check if the values it should be before have not been seen before
            if(PageSet.find(num) != PageSet.end()){
                PageSet.clear();
                return false;
            }
        }
        PageSet.insert(curr);
    }
    return true;
}

void validator(std::vector<int> &commandLine, std::unordered_map<int, std::vector<int>> conditionalMap, std::unordered_set<int> &PageSet){
    int n = commandLine.size();
    std::vector<int> correctPages(n, 0);
    std::unordered_map<int, int> priMap; //Stores the number and its conditional amount

    for(int num: commandLine){
        PageSet.insert(num);
        priMap[num] = 0;
    }

    for(int i = 0; i < n; i++){
        int curr = commandLine[i];
        for(int num: conditionalMap[curr]){
            if(PageSet.find(num) != PageSet.end()){
                priMap[curr]++;
            }
        }
    }
    for(const auto& pair: priMap){
        int val = pair.first;
        int index = n - pair.second - 1;
        correctPages[index] = val;
    }
    commandLine = correctPages;
    return;
}

int midCorrecterSummer(std::vector<std::vector<int>> inputCommands, std::unordered_map<int, std::vector<int>> conditionalMap){
    int Accum = 0;
    int n = inputCommands.size();
    for(int i = 0; i < n; i++){
        std::unordered_set<int> PageSet;
        if(!validityChecker(inputCommands[i], conditionalMap, PageSet)){ // If it is not valid
            validator(inputCommands[i], conditionalMap, PageSet);
            int lineSize = inputCommands[i].size();
            int middleIndex = lineSize/2;
            Accum += inputCommands[i][middleIndex];
        }
    }
    return Accum;
}

int main(){
    // Reading the input file
    std::ifstream f("input.txt");
    std::string s;
    std::unordered_map<int, std::vector<int>> conditionalMap;
    std::vector<std::string> inputCommands;

    while(getline(f, s)){
        if(s.size() == 0){
            break;
        }
        std::string Snum1(s.begin(), s.begin()+2), Snum2(s.begin()+3, s.begin()+5);
        int num1 = std::stoi(Snum1);
        int num2 = std::stoi(Snum2);
        conditionalMap[num1].emplace_back(num2);
    }
    while(getline(f, s)){
        inputCommands.emplace_back(s);
    }
    std::vector<std::vector<int>> commands;
    commands = stringParser(inputCommands);
    int newResult = midCorrecterSummer(commands, conditionalMap);
    std::cout << "The sum of the newly validated mid values is " << newResult << std::endl; // Part 2
    return 0;
}