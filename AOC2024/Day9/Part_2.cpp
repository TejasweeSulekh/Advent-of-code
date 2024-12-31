#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>

int getPlace(std::vector<int> &input, std::vector<int> &tempInput, int firstPtr){
    // Basically find the place at which we are adding the files to
    int newPlace = std::accumulate(input.begin(), input.begin()+firstPtr, 0); // Sum up all the spaces before
    // Check if something is already added to that place
    if(input[firstPtr] != tempInput[firstPtr]){
        newPlace += input[firstPtr] - tempInput[firstPtr];
    }
    return newPlace;
}


long long FilesProcessor(std::vector<int> &input){
    long long totalVal = 0;
    // Size of the input
    int size = input.size();
    std::vector<int> tempInput = input;
    // The ptr for the last ID being brought in the front
    int lastPtr = size - 1;
    // The most recent free space we have
    int firstPtr = 1;
    // The place which we are currently looking/filling
    int place = 0;
    // The ID of the last file
    int lastID = (size)/2;
    int lastSize = input[lastPtr];
    int curID = 0;

    for(int i = lastPtr; i >= 0; i -= 2){
        lastSize = input[i];
        lastID = i/2;
        for(int j = firstPtr; j < i; j+=2){
            // Enough space to accomodate the whole file
            if(lastSize <= tempInput[j]){
                place = getPlace(input, tempInput, j);
                for(int k = 0; k < lastSize; k++){
                    totalVal += place*lastID;
                    place++;
                    // Updating the empty space left
                    tempInput[j]--;
                    // Updating the array for final calculations
                    tempInput[i]--;
                }
                break;
            }
        }
    }
    curID = 0;
    for(int i = 0; i < size; i += 2){
        if(tempInput[i]){
            place = std::accumulate(input.begin(), input.begin()+i, 0); // Sum up all the spaces before it
            for(int j = 0; j < tempInput[i]; j++){
                totalVal += place*curID;
                place++;
            }
        }
        curID++;
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