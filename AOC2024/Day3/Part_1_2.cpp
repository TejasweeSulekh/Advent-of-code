#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <sstream>
#include <vector>

int stringToInt(std::string &s){
    std::stringstream buf;
    int val = 0;
    buf << s;
    buf >> val;
    return val;
}

void fetchNumber(std::string &s, int &ptr, std::string &tempNum){
    for(int i = 0; i < 3; i++){
        if(s[ptr] >= '0' && s[ptr] <= '9'){
            tempNum += s[ptr];
            ptr++;
        }
        else{
            break;
        }
    }
    return;
}

bool checkValidity(std::string &s, int ptr, std::pair<int, int> &mulPair){
    int tempNum1 = 0;
    int tempNum2 = 0;
    if(s[ptr] == '('){
        ptr++;
        std::string tempNum;
        fetchNumber(s, ptr, tempNum);
        if(!tempNum.empty()){
            tempNum1 = stringToInt(tempNum);
            tempNum.clear();
            // ptr++;
            if(s[ptr] == ','){
                ptr++;
                fetchNumber(s, ptr, tempNum);
                if(!tempNum.empty()){
                    tempNum2 = stringToInt(tempNum);
                    tempNum.clear();
                    if(s[ptr] == ')'){
                        mulPair.first = tempNum1;
                        mulPair.second = tempNum2;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

long long multiplier(std::string &s, bool& enabled){
    std::vector<char> lookup = {'m', 'u', 'l'};//look for a instance of mull occurance
    std::vector<char> doLookup = {'d', 'o', '(', ')'};
    std::vector<char> dontLookup = {'d', 'o', 'n', '\'', 't', '(', ')'}; // for storing special characters use backslash '\'
    int n = s.size();
    int counter = 0;
    int Enabler = 0, Disabler = 0;
    // bool enabled = true;
    long long accumulater = 0;
    std::pair<int, int> mulPair;
    for(int i = 0; i < n; i++){
        char c = s[i];
        if(c == doLookup[Enabler]){
            Enabler++;
        }
        else{
            Enabler = 0;
        }
        if(c == dontLookup[Disabler]){
            Disabler++;
        }
        else{
            Disabler = 0;
        }
        if(Enabler == 4){ 
            enabled = true;
        }
        if(Disabler == 7){ 
            enabled = false;
        }
        if(c == lookup[counter]){
            counter++;
        }
        else{
            counter = 0;
        }
        if(counter == 3){
            counter = 0;
            if(checkValidity(s, i+1, mulPair)){
                if(enabled){
                    accumulater += mulPair.first * mulPair.second;
                }
            }
        }
    }
    return accumulater;

}


int main(){
    std::ifstream f("input.txt");
    std::string s, input;
    long long result = 0;
    bool enabled = true;
    while(getline(f, s)){
        // std::cout << s << std::endl;
        result += multiplier(s, enabled);
    }
    std::cout << "from the valid mul instructions the answer is " << result << std::endl;
    return 0;
}