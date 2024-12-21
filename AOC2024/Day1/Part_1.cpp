#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int stringToint(std::string &s){
    std::stringstream buf;
    int x = 0;
    buf << s;
    buf >> x;
    return x;
}

long long DiffBetweenLists(std::vector<int> input1, std::vector<int> input2){
    sort(input1.begin(), input1.end());
    sort(input2.begin(), input2.end());
    int n = input1.size();
    long long distance = 0;
    for(int i = 0; i < n; i++){
        int temp = abs(input1[i] - input2[i]);
        distance += temp;
    }
    return distance;
}


int main(){
    std::ifstream f("input.txt");

    std::string s;
    std::vector<int> input1, input2;
    while(getline(f, s)){
        std::stringstream buf;
        std::string temp;
        for(char it: s){
            if(it != ' ') temp.push_back(it);
            if(it == ' ' && temp.size() != 0){
                int x = stringToint(temp);
                input1.emplace_back(x);
                temp.clear();
            }
        }
        int x = stringToint(temp);
        input2.emplace_back(x);
    }
    f.close();
    long long distance = DiffBetweenLists(input1, input2); // Task 1
    std::cout << "The distance between the lists is " << distance << std::endl;
    return 0;
}