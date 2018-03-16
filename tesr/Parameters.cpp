//
//  SetParameters.cpp
//  GBlockModeling - current
//
//  Created by Micheli Knechtel on 02/09/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Parameters.hpp"
#include "DataManager.hpp"
#include "PrintManager.hpp"

void Parameters::loadingFromCommandLine(int argc, char **argv)
{
    for (int i = 0; i<argc; i++)
    {
        string strAux = argv[i];
        loadInput(strAux, argv, i);
    }
    
    checkInput();
    
}

void Parameters::loadInput(string strAux, char **argv, int i)
{
    if (strAux.compare("-directory")==0)
        directory = argv[++i];
   
    if (strAux.compare("-clusterFileName")==0)
        clusterFileName = argv[++i];
    
    if (strAux.compare("-networkSize")==0)
        networSize = atoi(argv[++i]);
}


void Parameters::checkInput()
{
    if (directory.compare("")==0)
    {
        cout << "Error: -directory not specified .."<<endl;
        exit(1);
    }
    else
        DataManager::getDataManager()->setDirectory(directory);
}

void Parameters::predefinedParameters()
{
    DataManager::getDataManager()->setDirectory("/Users/micheliknechtel/Documents/xCode/GGBMCG/");
    DataManager::getDataManager()->setClusterFileName("clusterSet.dat");
    DataManager::getDataManager()->setModelFileName("model.lp");
    DataManager::getDataManager()->setLog(log);
    DataManager::getDataManager()->setDecisionVariableType(ILOINTVAR);
    DataManager::getDataManager()->setDecisionVariableType(ILONUMVAR);

    DataManager::getDataManager()->setAdditionalConstraint(true);
    DataManager::getDataManager()->setRelationMatrixFileName("tesr/networks/binary/NW_RD_04");
    DataManager::getDataManager()->setMatrixDataType(BINARY);
    DataManager::getDataManager()->loadingRelationMatrix();
  
    PrintManager().inputData();
}


