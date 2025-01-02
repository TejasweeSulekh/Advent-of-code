#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Node
{
    public:
    long long data;
    Node *next;
};

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

long RuleApplier(Node* head, int iter){
    long totalSize = 0;
    Node* tempHead = head;

    for(int i = 0; i < iter; i++){
        // Starting from initial position
        tempHead = head;
        while(tempHead){
            // A loop until we reach the end
            long long value = tempHead->data; 
            // Priority 1
            if(value == 0){
                tempHead->data = 1;
            }
            // Priority 2
            else if(isEvenDigit(value)){
                // Getting the new size
                int newDigits = DigitsCounter(value)/2;
                long long val1, val2;
                long long temp = pow(10, newDigits);
                val1 = value / temp;
                val2 = value % temp;
                tempHead->data = val1;
                
                Node* nextNode = tempHead->next;
                
                Node* newNode = new Node();
                newNode->data = val2;
                tempHead->next = newNode;
                newNode->next = nextNode;
                tempHead = newNode;
            }
            else{
                tempHead->data = value*2024;
            }
            tempHead = tempHead->next;
        }
    }

    tempHead = head;

    while(tempHead){
        totalSize++;
        tempHead = tempHead->next;
    }

    return totalSize;
}


int main(){
    // std::ifstream f("misc/testInput.txt");
    std::ifstream f("input.txt");
    
    // Initializing the head for linkedlist
    Node* head = new Node();
    head->next = NULL;
    Node* tempHead = head;

    std::string s;
        
    while(getline(f, s)){
        int size = s.size();
        int ptr = 0;
        for(int i = 0; i < size; i++){
            if(s[i] == ' '){
                std::string temp = s.substr(ptr, (i-ptr));
                ptr = i+1;
                long long stoneNum = std::stoll(temp);
                // Storing the value
                tempHead->data = stoneNum;
                // Creating a new node to prepare for next iteration
                Node* newNode = new Node();
                tempHead->next = newNode;
                // Update the pointer
                tempHead = newNode;
            }
        }
        std::string temp = s.substr(ptr, (size-ptr));
        long long lastStoneNum = std::stoll(temp);
        tempHead->data = lastStoneNum;
    }

    long numberOfStones = RuleApplier(head, 25); // For 25 iteration

    std::cout << "After 25 iteration the number of stones found was " << numberOfStones << std::endl;

    return 0;
}