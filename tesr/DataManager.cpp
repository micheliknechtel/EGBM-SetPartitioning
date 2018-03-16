//
//  DataManager.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "DataManager.hpp"
#include <cstring>
#include <algorithm>
#include <string.h>
#include <stdio.h>
#include <fstream>

DataManager* DataManager::dataManager = NULL;

DataManager* DataManager::getDataManager()
{
    if(!dataManager)
    {
        dataManager = new DataManager;
    }
    return dataManager;
}

void DataManager::setDirectory(string directory)
{
    this->directory = directory;
}

void DataManager::setNetworSize(int networkSize)
{
    this->networkSize = networkSize;
}

void DataManager::setClusterFileName(string clusterFileName)
{
    this->clusterFileName = clusterFileName;
}

void DataManager::setLog(bool log)
{
    this->logLevel = log;
}

int DataManager::getNetworSize()
{
    return networkSize;
}

string DataManager::getRelationMatrixFileName()
{
    return directory + relationMatrixFileName;
}

string  DataManager::getModelFileName()
{
     return directory + modelFileName;
}

void DataManager::setModelFileName(string modelFileName)
{
    this->modelFileName = modelFileName;
}

void DataManager::readBinaryMatrix()
{
    string str = directory + relationMatrixFileName;
    const char * fin  = str.c_str();
    
    ifstream file(fin);
    
    if (file.is_open())
    {
        file>>networkSize;
        
        relationMatrix =  new int*[networkSize];
        
        for ( int i = 0; i < networkSize; i++ )
        {
            relationMatrix[i] =  new int[networkSize];
            
            for ( int j = 0; j < networkSize; j++ )
            {
                file>>relationMatrix[i][j];
            }
        }

    }
    else
    {
        cout<<"Could not find file "<<str;
        exit(1);
    }
    
}

void DataManager::setRelationMatrixFileName(string relationMatrixFileName)
{
    this->relationMatrixFileName = relationMatrixFileName;
}

void DataManager::loadingRelationMatrix()
{
    if(matrixDataType == BINARY)
        readBinaryMatrix();
}

void DataManager::setMatrixDataType(MatrixDataType type)
{
    matrixDataType = type;
}

int ** DataManager::getRelationMatrix()
{
    return relationMatrix;
    
}

void DataManager::setEpsilon(map<int,vector<int>> epsilon)
{
    this->epsilon = epsilon;
}

map<int,vector<int>> DataManager::getEpsilon()
{
    return this->epsilon;
}

void DataManager::setClusterSets(map<int,vector<int>> clusterSets)
{
    this->clusterSets = clusterSets;
}

map<int,vector<int>> DataManager::getClusterSets()
{
    return this->clusterSets;
}


void  DataManager::setE(map<pair<int, int>, fitness> E)
{
    this->E = E;
}

map<pair<int, int>, fitness>  DataManager::getE()
{
    return this->E;
}

void  DataManager::setDecisionVariableType(DecisionVariableType type)
{
    this->decisionVariableType = type;
}

DecisionVariableType  DataManager::getDecisionVariableType()
{
    return decisionVariableType;
}

bool DataManager::getAddicionalConstraint()
{
    return addicionalConstraint;
}

void DataManager::setAdditionalConstraint(bool addicionalConstraint)
{
    this->addicionalConstraint = addicionalConstraint;
}
