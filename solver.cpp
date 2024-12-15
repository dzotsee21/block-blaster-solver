#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

int main(){
    vector<vector<string>> blastTemplate = {{"r0c0","r0c1","r0c2","r0c3","r0c4","r0c5","r0c6","r0c7"},
                                            {"r1c0","r1c1","r1c2","r1c3","r1c4","r1c5","r1c6","r1c7"},
                                            {"r2c0","r2c1","r2c2","r2c3","r2c4","r2c5","r2c6","r2c7"},
                                            {"r3c0","r3c1","r3c2","r3c3","r3c4","r3c5","r3c6","r3c7"},
                                            {"r4c0","r4c1","r4c2","r4c3","r4c4","r4c5","r4c6","r4c7"},
                                            {"r5c0","r5c1","r5c2","r5c3","r5c4","r5c5","r5c6","r5c7"},
                                            {"r6c0","r6c1","r6c2","r6c3","r6c4","r6c5","r6c6","r6c7"},
                                            {"r7c0","r7c1","r7c2","r7c3","r7c4","r7c5","r7c6","r7c7"}};

    vector<vector<string>> possibleBlocks = {{"r2c3", "r2c5", "r2c4", "r3c5", "r4c5"}};
    vector<vector<int>> possibleBlocksInt;
    vector<vector<string>> blastTemplateCopy;
    while(true){
        string inpt;
        std::cout << "Specify occupied slots >> ";
        std::cin >> inpt;
        size_t ridx = 0;
        if(inpt == "exit")
            break;
        for(auto &row : blastTemplate){
            size_t cidx = 0;
            for(auto &col : row){
                if(col == inpt){
                    blastTemplate[ridx][cidx] += 'o';
                }
                cidx++;
            }
            ridx++;
        }
    }
    for(const auto &block : possibleBlocks){
        for(const auto &val : block){
            int valRowNum = val[1] - '0'; // get number value of block table row
            int valColNum = val[3] - '0'; // get number value of block table row
            possibleBlocksInt.push_back({valRowNum, valColNum});
        }
    }

    vector<int> previousVector = {-1, -1};
    size_t dridx = 0;
    size_t dcidx = 0;
    size_t idx = 0;
    for(size_t ridx=0;ridx<8;ridx++){
        for(size_t cidx=0;cidx<8;cidx++){
            const auto &val = blastTemplate[ridx][cidx];
            if(val.find('o') != std::string::npos || val.find('p') != std::string::npos){
                continue;
            }
            if(blastTemplateCopy.empty())
                blastTemplateCopy.assign(blastTemplate.begin(), blastTemplate.end());            

            for(const auto &blockVector : possibleBlocksInt){
                if(idx != 0){
                    // all the possible positions
                    if((blockVector[0] > previousVector[0] ) && (blockVector[1] > previousVector[1])){
                        dridx = ridx+(blockVector[0]-previousVector[0]);
                        dcidx = cidx+(blockVector[1]-previousVector[1]);
                    }
                    else if((blockVector[0] < previousVector[0] ) && (blockVector[1] > previousVector[1])){
                        dridx = ridx-(previousVector[0]-blockVector[0]);
                        dcidx = cidx+(blockVector[1]-previousVector[1]);
                    }
                    else if((blockVector[0] < previousVector[0] ) && (blockVector[1] < previousVector[1])){
                        dridx = ridx-(previousVector[0]-blockVector[0]);
                        dcidx = cidx-(previousVector[1]-blockVector[1]);
                    }
                    else if((blockVector[0] > previousVector[0] ) && (blockVector[1] < previousVector[1])){
                        dridx = ridx+(blockVector[0]-previousVector[0]);
                        dcidx = cidx-(previousVector[1]-blockVector[1]);
                    }
                    else if((blockVector[0] == previousVector[0] ) && (blockVector[1] > previousVector[1])){
                        dridx = ridx;
                        dcidx = cidx+(blockVector[1]-previousVector[1]);
                    }
                    else if((blockVector[0] == previousVector[0] ) && (blockVector[1] < previousVector[1])){
                        dridx = ridx;
                        dcidx = cidx-(previousVector[1]-blockVector[1]);
                    }
                    else if((blockVector[0] > previousVector[0] ) && (blockVector[1] == previousVector[1])){
                        dridx = ridx+(blockVector[0]-previousVector[0]);
                        dcidx = cidx;
                    }
                    else if((blockVector[0] < previousVector[0] ) && (blockVector[1] == previousVector[1])){
                        dridx = ridx-(previousVector[0]-blockVector[0]);
                        dcidx = cidx;
                    }
                }
                // appending
                if (dridx < blastTemplate.size() && dcidx < blastTemplate[dridx].size()){
                    if((blastTemplate[dridx][dcidx].find('p') == std::string::npos) && (blastTemplate[dridx][dcidx].find('o') == std::string::npos)){
                        blastTemplate[dridx][dcidx] += 'p';
                        possibleBlocksInt.erase(possibleBlocksInt.begin());
                        break;                        
                    }

                }
            previousVector = blockVector;    
            }
            idx++;
        }
    }        

    // for(auto vector : possibleBlocksInt){
    //     for(auto val : vector)
    //         cout << val << ", ";
    //     cout << endl;
    // }

    for(auto row : blastTemplate){
        for(auto val : row)
            cout << val << ' ';
        cout << '\n';
    }
    
    cout << "HELLOZX";

    return 0;
}