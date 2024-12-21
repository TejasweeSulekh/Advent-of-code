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

std::pair<int, bool> validityChecker(std::vector<int> line, bool inc){
    int n = line.size();
    for(int i = 0; i < n-1; i++){
        if(inc){
            if((line[i] < line[i+1]) && ((line[i+1] - line[i]) <= 3)){
                continue;
            }
            else{
                return {i, false};
            }
        }
        else{
            if((line[i] > line[i+1]) && (line[i] - line[i+1]) <= 3){
                continue;
            }
            else{
                return {i, false};
            }
        }
    }
    return {-1, true};
}

bool validityWithDampChecker(std::vector<int> line, bool inc, int damp, int row){
    std::pair<int, bool> check;
    std::vector<int> oldLine = line;
    for(int i = damp; i >= 0; i--){
        if(line.size() <= 2){
            return true;
        }
        check = validityChecker(line, inc);
        if(check.second){
            // std::cout << "Row: " << row << " is Safe"<< std::endl;
            return true;
        }
        else{
            int temp = check.first;
            std::vector<int> lineTemp = line;
            lineTemp.erase(lineTemp.begin()+temp+1);
            bool tempInc = lineTemp[0] < lineTemp[1];
            if(validityChecker(lineTemp, tempInc).second){
                line = lineTemp;
                inc = tempInc;
            }
            else{
                line.erase(line.begin()+temp);
                inc = line[0] < line[1];
            }
        }
    }
    // last try for first edge case
    oldLine.erase(oldLine.begin());
    inc = oldLine[0] < oldLine[1];
    if(validityChecker(oldLine, inc).second){
        return true;
    }
    return false;

}

int safetyChecker(std::vector<std::vector<int>> &input, int damp){
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
        // my optimal for part 2        
        if(validityWithDampChecker(input[i], inc, damp, i)){
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
    int damp = 1; // the number of levels that are allowed to be damped
    int result = safetyChecker(input, damp);
    std::cout << "The number of safe nuclear reactors is " << result << std::endl;
    return 0;
}