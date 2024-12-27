#include <iostream>
#include <fstream>
#include <string>
#include <vector>


long long FilesProcessor(std::vector<int> &input){
    long long totalVal = 0;
    // Size of the input
    int size = input.size();
    // The ptr for the last ID being brought in the front
    int lastPtr = size - 1;
    // The place which we are currently looking/filling
    int place = 0;
    // The ID of the last file
    int lastID = (size)/2;
    int lastSize = input[lastPtr];
    int curID = 0;
    // A loop over all the files and vacant space
    for(int i = 0; i < size; i++){
        if(i%2 == 0){
            if(i > lastPtr){
                break;
            }
            // File Space
            for(int j = 0; j < input[i]; j++){
                totalVal += curID*place;
                if(i == lastPtr){
                    lastSize--;
                    if(lastSize <= 0){
                        return totalVal;
                    }
                }
                place++;
            }
            curID++;
        }
        else{
            // Filling the vacant place with the lastID file
            for(int j = 0; j < input[i]; j++){
                if(lastSize <= 0 && lastPtr > 0){
                    // Update for the index
                    lastPtr -= 2;
                    if(lastPtr < i){
                        return totalVal;
                    }
                    // Update the ID of the last file
                    lastID--;
                    // Update the number of files we have
                    lastSize = input[lastPtr];
                }
                totalVal += lastID*place;
                lastSize--;
                place++;
            }
        }
    }

    return totalVal;
}



int main(){
    std::ifstream f("input.txt");
    // std::ifstream f("misc/testInput.txt");
    std::string s;
    std::string stringInput;
    int size;
    while(getline(f, s)){
        stringInput = s;
        size = s.size();
    }
    std::vector<int> input;
    for(int i = 0; i < size; i++){
        std::string temp = stringInput.substr(i,1);
        int num = std::stoi(temp);
        input.emplace_back(num);
    }
    long long answer = FilesProcessor(input);
    std::cout << answer << std::endl;
    return 0;
}