#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>



int StringToInt(std::string &s){
    std::stringstream buf;
    int x = 0;
    buf << s;
    buf >> x;
    return x;
}

std::vector<int> convertToVector(std::string &s){
    std::vector<int> vec;
    std::string temp;
    for(char it:s){
        if(it != ' '){
            temp.push_back(it);
        }
        if(it == ' '){
            int val = StringToInt(temp);
            vec.emplace_back(val);
            temp.clear();
        }
    }
    int val = StringToInt(temp);
    vec.emplace_back(val);
    return vec;
}

bool validityChecker(std::vector<int> line, bool inc){
    int n = line.size();
    for(int i = 0; i < n-1; i++){
        if(inc){
            if((line[i] < line[i+1]) && ((line[i+1] - line[i]) <= 3)){
                continue;
            }
            else{
                return false;
            }
        }
        else{
            if((line[i] > line[i+1]) && (line[i] - line[i+1]) <= 3){
                continue;
            }
            else{
                return false;
            }
        }
    }
    return true;
}

int safetyChecker(std::vector<std::vector<int>> &input){
    int n = input.size();
    int numSafe = 0;
    for(int i = 0; i < n; i++){
        bool inc;
        if(input[i].size() <= 1){
            numSafe++;
            continue;
        }
        else{
            inc = input[i][0] < input[i][1];
        }
        // Comment toggle for part 1
        if(validityChecker(input[i], inc)){
            numSafe++;
        }
    }
    return numSafe;
}

int main(){
    std::ifstream f("input.txt");
    std::string s;
    std::vector<std::vector<int>> input;
    while(getline(f, s)){
        std::vector<int> temp = convertToVector(s);
        input.emplace_back(temp);
    }
    int result = safetyChecker(input);
    std::cout << "The number of safe nuclear reactors is " << result << std::endl;
    return 0;
}