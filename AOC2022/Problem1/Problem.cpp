// #include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <numeric>

using namespace std;

long maxVal(vector<vector<int>> & input){
    long maxVal = 0;
    for(auto &it: input){
        long n = it.size();
        long tempSum = accumulate(it.begin(), it.end(), 0);
        maxVal = max(maxVal, tempSum);
    }
    return maxVal;
}



int  main(){
    ifstream f("input.txt");

    if(!f.is_open()){
        cerr << "Error in opening the file!";
        return 1;
    }

    string s;
    vector<int> buffer;
    vector<vector<int>> input;
    while(getline(f, s)){
        if(s == ""){
            input.emplace_back(buffer);
            buffer.clear();
        }
        else{
            int temp = 0;
            stringstream buf;
            buf << s;
            buf >> temp;
            buffer.emplace_back(temp);
        }
    }

    f.close();

    long result;

    result = maxVal(input);

    cout << "The elf carrying the most calories has " << result << " calories on him" << endl;

    return 0;
}