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

    vector<vector<string>> possibleBlocks = {{"r6c2", "r7c2", "r6c3", "r7c3"}, {"r6c2", "r7c2"}};
    vector<vector<int>> possibleBlocksInt;
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

    int idx = 0;
    int dridx = 0;
    int dcidx = 0;
    vector<int> previousVector = {-1, -1};
    vector<vector<int>> rslt;

    for(const auto &block : possibleBlocks){
        for(const auto &val : block){
            int valRowNum = val[1] - '0'; // get number value of block table row
            int valColNum = val[3] - '0'; // get number value of block table row
            possibleBlocksInt.push_back({valRowNum, valColNum});
        }
    }

    for(const auto &blockVector : possibleBlocksInt){
        if(idx != 0){
            // all the possible positions
            dridx += blockVector[0] - previousVector[0];
            dcidx += blockVector[1] - previousVector[1];
            rslt.push_back({dridx, dcidx});
        }
        if(idx == 0){
            rslt.push_back({dridx, dcidx});
        }
        previousVector.assign(blockVector.begin(), blockVector.end());
        idx++;
    }
    for(auto v : rslt)
        cout << v[0] << " - " << v[1] << endl;

    for(size_t ridx=0;ridx<8;ridx++){
        for(size_t cidx=0;cidx<8;cidx++){
            // const auto &val = blastTemplate[ridx][cidx];
            // if(val.find('o') != std::string::npos || val.find('p') != std::string::npos){
            //     continue;
            // }
            blastTemplateCopy.assign(blastTemplate.begin(), blastTemplate.end());

            // appending
            bool err = false;
            if(rslt.size() == 0){
                for(auto row : blastTemplate){
                    for(auto val : row)
                        cout << val << ' ';
                    cout << '\n';
                }
                exit(0);
            }
            for(auto &v : rslt){
                if((ridx+v[0] < blastTemplateCopy.size()) && (cidx+v[1] < blastTemplateCopy[ridx+v[0]].size())){
                    // cout << v[0] << " - " << v[1] << endl;
                    if((blastTemplateCopy[ridx+v[0]][cidx+v[1]].find('p') == string::npos) && (blastTemplateCopy[ridx+v[0]][cidx+v[1]].find('o') == string::npos)){
                        blastTemplateCopy[ridx+v[0]][cidx+v[1]] += 'p';
                        int pcount = 0;
                        for(auto row : blastTemplate){
                            for(auto val : row){
                                if(val.find('p') != string::npos)
                                    pcount++;                                
                            }
                        }
                        if(pcount >= possibleBlocksSize)
                            goto printvals;
                    }
                } else{
                    err = true;
                    break;
                }
            }
            if(!err){
                blastTemplate = blastTemplateCopy;
                rslt.erase(rslt.begin());
                break;
            }
        }
    }

    // for(auto vector : possibleBlocksInt){
    //     for(auto val : vector)
    //         cout << val << ", ";
    //     cout << endl;
    // }

    printvals:
        for(auto row : blastTemplate){
            for(auto val : row)
                cout << val << ' ';
            cout << '\n';
        }
    
    cout << "=!";

    return 0;
}