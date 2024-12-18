#include <iostream>
#include <bits/stdc++.h>
#include <vector>
using namespace std;


vector<vector<int>> blastFreeSlots(vector<vector<string>> blastTemplate);
vector<vector<vector<int>>> vstr_to_vint(vector<vector<string>> possibleBlocks);
vector<vector<vector<int>>> distance_vector(vector<vector<vector<int>>> possibleBlocksInt);

int main(){
    vector<vector<string>> blastTemplate = {{"r0c0","r0c1","r0c2","r0c3","r0c4","r0c5","r0c6","r0c7"},
                                            {"r1c0","r1c1","r1c2","r1c3","r1c4","r1c5","r1c6","r1c7"},
                                            {"r2c0","r2c1","r2c2","r2c3","r2c4","r2c5","r2c6","r2c7"},
                                            {"r3c0","r3c1","r3c2","r3c3","r3c4","r3c5","r3c6","r3c7"},
                                            {"r4c0","r4c1","r4c2","r4c3","r4c4","r4c5","r4c6","r4c7"},
                                            {"r5c0","r5c1","r5c2","r5c3","r5c4","r5c5","r5c6","r5c7"},
                                            {"r6c0","r6c1o","r6c2o","r6c3o","r6c4o","r6c5o","r6c6o","r6c7o"},
                                            {"r7c0","r7c1o","r7c2o","r7c3o","r7c4o","r7c5o","r7c6o","r7c7o"}};

    vector<vector<string>> possibleBlocks = {{"r7c0", "r6c0", "r6c1", "r7c1"}, {"r7c2", "r7c3", "r7c4"}, {"r7c6", "r6c6"}};
    vector<vector<vector<int>>> possibleBlocksInt = vstr_to_vint(possibleBlocks);
    vector<vector<string>> blastTemplateCopy;
    vector<vector<string>> blastTemplateTemp;
    vector<vector<string>> bestTemplate;
    int possibleBlocksSize = 0;
    for(auto vector : possibleBlocks){
        possibleBlocksSize += vector.size();
    }
    cout << possibleBlocksSize << endl; 

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

    // make an algorithm that adds block(s) to the table and iterates over other block(s) to find the best possible combination of blocks

    int prevBestPoint = 0;
    for(auto &blocks : possibleBlocksInt){
       vector<vector<vector<int>>> rslt = distance_vector({blocks});
        for(auto &block : rslt){
            vector<vector<int>> freeSlots = blastFreeSlots(blastTemplate);
            for(auto &freeVec : freeSlots){
                blastTemplateCopy.assign(blastTemplate.begin(), blastTemplate.end());
                bool err = false;
                for(auto &bvec : block){
                    if((freeVec[0]+bvec[0] >= 0 && freeVec[0]+bvec[0] < 8) && (freeVec[1]+bvec[1] >= 0 && freeVec[1]+bvec[1] < 8)){
                        if(blastTemplateCopy[freeVec[0]+bvec[0]][freeVec[1]+bvec[1]].find('o') == string::npos)
                            blastTemplateCopy[freeVec[0]+bvec[0]][freeVec[1]+bvec[1]] += 'o';
                        else
                            err = true;                        
                    } else{
                        err = true;                 
                    }
                }
                if(!err){
                    int point = 0;
                    for(int r=0; r<8;r++){
                        bool allContainO = true;
                        for(int c=0; c<8;c++)
                            if(blastTemplateCopy[r][c].find('o') == string::npos){
                                allContainO = false;
                                break;
                            }
                        if(allContainO){
                            point++;
                        }
                    }
                    for(int c=0; c<8;c++){
                        bool allContainO = true;
                        for(int r=0; r<8;r++)
                            if(blastTemplateCopy[r][c].find('o') == string::npos){
                                allContainO = false;
                                break;
                            }
                        if(allContainO)
                            point++;
                    }
                    if(point>prevBestPoint){
                        prevBestPoint = point;
                            bestTemplate.assign(blastTemplateCopy.begin(), blastTemplateCopy.end());
                    }
                }
            }
        }       
    }

    for(auto &row : bestTemplate){
        for(auto &val : row)
            cout << val << ' ';
        cout << '\n';
    }

    return 0;
}

// Functions
vector<vector<int>> blastFreeSlots(vector<vector<string>> blastTemplate){
    vector<vector<int>> freeSlots;
    for(int ridx=0; ridx<8;ridx++){
        for(int cidx=0; cidx<8; cidx++){
            if(blastTemplate[ridx][cidx].find('o') == string::npos)
                freeSlots.push_back({ridx, cidx});
        }
    }
    return freeSlots;
}

vector<vector<vector<int>>> vstr_to_vint(vector<vector<string>> possibleBlocks){
    vector<vector<vector<int>>> possibleBlocksInt;
    for(const auto &block : possibleBlocks){
        vector<vector<int>> blockVals;
        for(const auto &val : block){
            int valRowNum = val[1] - '0'; // get number value of block table row
            int valColNum = val[3] - '0'; // get number value of block table row
            blockVals.push_back({valRowNum, valColNum});
        }
        possibleBlocksInt.push_back({blockVals});
    }
    return possibleBlocksInt;
}

vector<vector<vector<int>>> distance_vector(vector<vector<vector<int>>> possibleBlocksInt){
    int idx = 0;
    int dridx = 0;
    int dcidx = 0;
    vector<int> previousVector = {-1, -1};
    vector<vector<vector<int>>> rslt;

    for(const auto &block : possibleBlocksInt){
        vector<vector<int>> blockVals;
        for(const auto &blockVector : block){
            if(idx != 0){
                // all the possible positions
                dridx += blockVector[0] - previousVector[0];
                dcidx += blockVector[1] - previousVector[1];
                blockVals.push_back({dridx, dcidx});
            }
            if(idx == 0){
                blockVals.push_back({dridx, dcidx});
            }
            previousVector.assign(blockVector.begin(), blockVector.end());
            idx++;
        }
        rslt.push_back({blockVals});
    }
    return rslt;
}
