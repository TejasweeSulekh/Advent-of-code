#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

int stringToint(std::string &s){
    std::stringstream buf;
    int x = 0;
    buf << s;
    buf >> x;
    return x;
}

long long similarityScoreFinder(std::vector<int> &input1, std::vector<int> &input2){
    long long similarityScore = 0;
    long temp = 0;
    int n = input1.size();
    std::unordered_map<int, int> mpp1, mpp2;
    std::unordered_set<int> stt;
    for(int i = 0; i < n; i++){
        // Making hash maps for the number of times a number appears in each list
        mpp1[input1[i]]++;
        mpp2[input2[i]]++;
        stt.insert(input1[i]);
    }
    for(auto &it: stt){
        temp = mpp1[it]*mpp2[it]*it;
        similarityScore += temp;
    }
    return similarityScore;
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
    long long simScore = similarityScoreFinder(input1, input2); // Task 2
    std::cout << "The similarity score of the list is " << simScore << std::endl;
    return 0;
}