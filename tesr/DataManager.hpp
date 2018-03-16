//
//  DataManager.hpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef DataManager_hpp
#define DataManager_hpp
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "Definitions.h"
#include "Definitions.h"


class DataManager
{
    static DataManager *dataManager;
    string directory;
    string clusterFileName;
    int networkSize;
    bool addicionalConstraint;
    bool logLevel = false;
    int ** relationMatrix;
    string relationMatrixFileName;
    MatrixDataType matrixDataType;
    map<int,vector<int>> epsilon;
    map<int,vector<int>> clusterSets;
    map<pair<int, int>, fitness> E;
    string modelFileName;
    DecisionVariableType decisionVariableType = ILOINTVAR;
public:
    static DataManager* getDataManager();
    map<int,map<int,int>> mapping;

    void readBinaryMatrix();
    void loadingRelationMatrix();
    void setDirectory(string directory);
    void setNetworSize(int networkSize);
    void setClusterFileName(string clusterFileName);
    void setLog(bool log);
    void setRelationMatrixFileName(string relationMatrixFileName);
    void setMatrixDataType(MatrixDataType type);
    void setEpsilon(map<int,vector<int>> epsilon);
    void setClusterSets( map<int,vector<int>> clusterSets);
    void setE(map<pair<int, int>, fitness> E);
    void setModelFileName(string modelFileName);
    void setDecisionVariableType(DecisionVariableType type);
    void setAdditionalConstraint(bool addicionalConstraint);
    
    map<int,vector<int>> getEpsilon();
    map<int,vector<int>> getClusterSets();
    map<pair<int, int>, fitness> getE();
    
    DecisionVariableType getDecisionVariableType();
    
    string getModelFileName();
    string getDirectory();
    string getRelationMatrixFileName();
    string getClusterFileName();
    int ** getRelationMatrix();
    int getNetworSize();
    bool getLog();
    bool getAddicionalConstraint();

};

#endif /* DataManager_hpp */
