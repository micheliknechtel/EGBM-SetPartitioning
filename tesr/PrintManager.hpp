//
//  PrintManager.hpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef PrintManager_hpp
#define PrintManager_hpp

#include <stdio.h>
#include <map>
#include <vector>
#include "DataManager.hpp"

using namespace std;

class PrintManager {
    bool logLevel = false;
    int **relationMatrix = DataManager::getDataManager()->getRelationMatrix();
public:
    void printPartition(map<int,vector<int>>partition);
    void printMatrixBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    void errorHeader(int error);
    void newLine();
    void inputData();
    void printRelationMatrix();
    void printTime( time_t currentTime);
    void printEpsilon();
    void printAllClusterSet();
    void printBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition);
    void printE();
    void printCplexResults(bool status, double objValue, double MIPRelativeGap, int nodes, double elapsedTime);
    void buildMatrix(map<int, vector<int>> partition);
    void printSolution(map<int, vector<int>> partition);
    map<string,clusterGroup> buildGroup(map<int, vector<int>> partition);
};

#endif /* PrintManager_hpp */
