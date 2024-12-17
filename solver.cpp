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
                                            {"r6c0","r6c1","r6c2","r6c3","r6c4","r6c5","r6c6","r6c7"},
                                            {"r7c0","r7c1","r7c2","r7c3","r7c4","r7c5","r7c6","r7c7"}};

    vector<vector<string>> possibleBlocks = {{"r7c3", "r7c4"}, {"r6c4", "r6c5", "r7c4", "r7c5"}};
    vector<vector<vector<int>>> possibleBlocksInt = vstr_to_vint(possibleBlocks);
    vector<vector<string>> blastTemplateCopy;
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

    vector<vector<vector<int>>>rslt = distance_vector(possibleBlocksInt);
    
    // make it so that block values are aligned correctly and iteratively through the table.
    vector<vector<int>> freeSlots = blastFreeSlots(blastTemplate);
    for(auto &block : rslt){
        int i = 0;
        blastTemplateCopy.assign(blastTemplate.begin(), blastTemplate.end());
        vector<vector<int>> freeSlots = blastFreeSlots(blastTemplate);
        for(auto &bvec : block){
            // cout << bvec[0] << "-" << bvec[1] << endl;
            for(int r=0; r<8; r++){
                for(int c=0; c<8; c++){
                    if(0 <= r+bvec[0] <= 7 && 0 <= c+bvec[1] <= 7){
                        vector<int> target = {r+bvec[0], c+bvec[1]};
                        if(find(freeSlots.begin(), freeSlots.end(), target) != freeSlots.end()){
                            if((i++)>=block.size()){
                                goto out;
                            }
                            cout << r << endl;
                            // cout << r+bvec[0] << "-" << c+bvec[1] << endl;
                            blastTemplateCopy[r+bvec[0]][c+bvec[1]] += 'o';
                            freeSlots = blastFreeSlots(blastTemplateCopy);                
                        }
                    }
                }
            }           
        }
        out:
        blastTemplate.assign(blastTemplateCopy.begin(), blastTemplateCopy.end());
        for(auto &row : blastTemplate){
            for(auto &val : row)
                cout << val << ' ';
            cout << '\n';
        }
        cout << "-----" << endl;
    }

    // for(auto &row : blastTemplate){
    //     for(auto &val : row)
    //         cout << val << ' ';
    //     cout << '\n';
    // }

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