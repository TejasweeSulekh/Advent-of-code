#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <unordered_map>

int DigitsCounter(long long value){
    int counter = 0;
    while(value){
        counter++;
        value = value/10;
    }
    return counter;
}

bool isEvenDigit(long long value){
    int counter = DigitsCounter(value);
    
    if(counter%2 == 0){
        return true;
    }
    else{
        return false;
    }
}

long RecurRuleApplier(long stone, int blinks, std::unordered_map<std::string, long long> &MemoisationTable){
    long long totalCount = 0;

    std::string key = std::to_string(stone) + '-' + std::to_string(blinks);

    if(blinks == 0){
        return 1;
    }

    if(MemoisationTable.find(key) != MemoisationTable.end()){
        // Check if the stone has already been processed for the given iter
        return MemoisationTable[key];
    }

    if(stone == 0){
        totalCount = RecurRuleApplier(1, blinks-1, MemoisationTable);
    }
    else if(isEvenDigit(stone)){
        long newDigits = DigitsCounter(stone)/2;
        long stone1, stone2, temp;
        temp = pow(10, newDigits);
        // Left half
        stone1 = stone / temp;
        // Right half
        stone2 = stone % temp;
        // Processing the new two stones created
        totalCount = RecurRuleApplier(stone1, blinks-1, MemoisationTable) + RecurRuleApplier(stone2, blinks - 1, MemoisationTable);
    }
    else{
        totalCount = RecurRuleApplier(stone*2024, blinks-1, MemoisationTable);
    }

    // Memoising newly processed stone count
    MemoisationTable[key] = totalCount;

    return totalCount;

}

long long finalStonesCounter(std::vector<long> stones, int blinks, std::unordered_map<std::string, long long> &MemoisationTable){
    long long FinalCount = 0;
    int size = stones.size();

    for(int i = 0; i < size; i++){
        FinalCount += RecurRuleApplier(stones[i], blinks, MemoisationTable);
    }

    return FinalCount;
}


int main(){
    // std::ifstream f("misc/testInput.txt");
    std::ifstream f("input.txt");
    
    std::vector<long> stones;

    std::string s;
        
    while(getline(f, s)){
        int size = s.size();
        int ptr = 0;
        for(int i = 0; i < size; i++){
            if(s[i] == ' '){
                std::string temp = s.substr(ptr, (i-ptr));
                ptr = i+1;
                long stoneNum = std::stol(temp);
                // Storing the value
                stones.emplace_back(stoneNum);
            }
        }
        std::string temp = s.substr(ptr, (size-ptr));
        long lastStoneNum = std::stol(temp);
        stones.emplace_back(lastStoneNum);
    }

    // The table which holds the stone number to counter value along with the amount of stones it will create
    std::unordered_map<std::string, long long> MemoisationTable; 


    int blinks = 75;
    long long numberOfStones = finalStonesCounter(stones, blinks, MemoisationTable); // Process each stones for all the blinks

    std::cout << "After " << blinks << " blinks the number of stones found was " << numberOfStones << std::endl;

    return 0;
}