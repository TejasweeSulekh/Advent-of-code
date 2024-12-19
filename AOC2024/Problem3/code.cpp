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
        
        // for(int i = 0; i < 3; i++){
        //     if(s[ptr] >= '0' && s[ptr] <= '9'){
        //         tempNum += s[ptr];
        //         ptr++;
        //     }
        //     else{
        //         break;
        //     }
        // }
        if(!tempNum.empty()){
            tempNum1 = stringToInt(tempNum);
            tempNum.clear();
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

int multiplier(std::string &s){
    std::vector<char> lookup = {'m', 'u', 'l'};//look for a instance of mull occurance
    int n = s.size();
    int counter = 0;
    int accumulater = 0;
    std::pair<int, int> mulPair;
    for(int i = 0; i < n; i++){
        char c = s[i];
        if(c == lookup[counter]){
            counter++;
        }
        else{
            counter = 0;
        }
        if(counter == 3){
            counter = 0;
            if(checkValidity(s, i, mulPair)){
                accumulater += mulPair.first * mulPair.second;
            }
        }
    }
    return accumulater;

}


int main(){
    std::ifstream f("testInput.txt");
    std::string s, input;
    while(getline(f, s)){
        input += s;
    }
    int result = 0;
    result = multiplier(s);
    std::cout << "from the valid mul instructions the answer is " << result << std::endl;
    return 0;
}