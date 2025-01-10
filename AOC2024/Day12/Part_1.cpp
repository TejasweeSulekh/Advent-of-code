#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

class DisjointSetUnion{
private:
    // Vector initialization for storing the nodes rank and their parent
    std::vector<int> rank, parent;
public:
    DisjointSetUnion(int n){
        // Reserving space for the vectors
        rank.reserve(n+1);
        parent.reserve(n+1);
        for(int i = 0; i <= n; i++){
            // Initally all the nodes are disjoint so rank will be 0
            rank.emplace_back(0);
            // Where they are their own parent 
            parent.emplace_back(i);
        }
    }

    int findUnionParent(int node){
        if(parent[node] == node){
            return node;
        }
        return parent[node] = findUnionParent(parent[node]);
    }

    void unionByRank(int node1, int node2){
        // Fetching the parents of the node to know their unions name
        int node1Parent = findUnionParent(node1);
        int node2Parent = findUnionParent(node2);

        if(node1Parent == node2Parent){
            //Belong to the same set
            return;
        }
        // else
        if(rank[node1Parent] > rank[node2Parent]){
            // Updating the parent according to the bigger union
            parent[node2Parent] = node1Parent;
        }
        else if(rank[node1Parent] < rank[node2Parent]){
            parent[node1Parent] = node2Parent;
        }
        else{
            // Unions of same size
            parent[node1Parent] = node2Parent;
            rank[node2Parent]++;
        }
    }
};



int checkParameter(std::vector<std::string> &input, char currentCharacter, int row, int col){
    int rowSize = input.size(), colSize = input[0].size();
    std::vector<int> delRow = {1, 0, -1, 0};
    std::vector<int> delCol = {0, -1, 0, 1};
    int counter = 0;

    for(int i = 0; i < 4; i++){
        int newRow = row + delRow[i];
        int newCol = col + delCol[i];
        bool inGarden = newRow >= 0 && newRow < rowSize && newCol >= 0 && newCol < colSize;
        bool isValid = true;
        if(inGarden){
            isValid = currentCharacter != input[newRow][newCol];
        }
        
        if(isValid){
            counter++;
        }
    }
    return counter;
}

void UpdateUnion(std::vector<std::string> &input, char currentCharacter, int row, int col, DisjointSetUnion &DSU){
    // Checks in all four directions and update the union if it finds the character connected to another same character
    int rowSize = input.size(), colSize = input[0].size();
    std::vector<int> delRow = {1, 0, -1, 0};
    std::vector<int> delCol = {0, -1, 0, 1};
    int counter = 0;

    for(int i = 0; i < 4; i++){
        int newRow = row + delRow[i];
        int newCol = col + delCol[i];
        bool inGarden = newRow >= 0 && newRow < rowSize && newCol >= 0 && newCol < colSize;
        if(inGarden){
            if(input[newRow][newCol] == currentCharacter){
                // These should be in one union
                int index1 = row*colSize + col;
                int index2 = newRow*colSize + newCol;
                DSU.unionByRank(index1, index2);
            }
        }
    }
}

long scoreCalculator(std::vector<std::string> &input, std::unordered_set<char> &Characters){
    long Score = 0;
    int rowSize = input.size(), colSize = input[0].size();
    int totalSize = rowSize*colSize;
    for(char Character: Characters){
        // stores all the values;
        DisjointSetUnion DSU(totalSize);
        // Here the index for a value with row and col values will be row*colSize + col
        // This DSU will be looking for all the character unions present in the input
        for(int row = 0; row < rowSize; row++){
            for(int col = 0; col < colSize; col++){
                if(input[row][col] == Character){
                    UpdateUnion(input, Character, row, col, DSU);
                }
            }
        }

        // Another parse to find all the regions which are connected
        std::unordered_set<int> regions;
        for(int row = 0; row < rowSize; row++){
            for(int col = 0; col < colSize; col++){
                if(input[row][col] == Character){
                    int index = row*colSize + col;
                    int tempParent = DSU.findUnionParent(index);
                    // Storing all the unions present for the given character;
                    regions.insert(tempParent);
                }
            }
        }
        
        // Now parsing through the garden looking for the region by region
        for(int region: regions){
            int area = 0;
            int fence = 0;
            for(int row = 0; row < rowSize; row++){
                for(int col = 0; col < colSize; col++){
                    if(input[row][col] == Character){
                        int index = row*colSize + col;
                        int tempParent = DSU.findUnionParent(index);
                        if(tempParent == region){
                            // Belongs to the same region as the one we are looking for
                            area++;
                            fence += checkParameter(input, Character, row, col);
                        }
                    }
                }
            }
            Score += area * fence;
        }
    }
    return Score;
}

int main(){
    // std::ifstream f("misc/testInput.txt");
    std::ifstream f("input.txt");
    std::string s;
    std::vector<std::string> input; 
    std::unordered_set<char> Characters;

    // Reading the input
    while(getline(f, s)){
        input.emplace_back(s);
        for(char c: s){
            Characters.insert(c);
        }
    }

    long score = scoreCalculator(input, Characters);
    
    std::cout << "The score for the current garden is " << score << std::endl;
    return 0;
}