//
//  DesviationMesuare.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 20/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "DesviationMesuare.hpp"
#include "DataManager.hpp"
#include "BlockError.hpp"
#include "PrintManager.hpp"

DesviationMesuare::DesviationMesuare()
{
    loadIdealBlocks();
}

void DesviationMesuare::calculate()
{
    int size = (int) DataManager::getDataManager()->getClusterSets().size();
    
    for (int k1 = 0; k1<size; k1++)
    {
        for (int k2 = 0; k2<size; k2++)
        {
            int size_k1 = (int) DataManager::getDataManager()->getClusterSets().at(k1).size();
            int size_k2 = (int) DataManager::getDataManager()->getClusterSets().at(k2).size();
            int error = size_k1 * size_k2;
           
            fitness fit;

            if (k1==k2)
            {
                error = (BlockError().*idealBlockSetupVector.at(0))(k1, k2, DataManager::getDataManager()->getClusterSets());
                fit.error = error;
                fit.blockType = 0;
            }
            else
            {
                error = (BlockError().*idealBlockSetupVector.at(1))(k1, k2, DataManager::getDataManager()->getClusterSets());
                fit.error = error;
                fit.blockType = 1;
            }

            E.insert(make_pair(pair<int, int>(k1, k2),fit));
        }
    }
    DataManager::getDataManager()->setE(E);
}

void DesviationMesuare::loadIdealBlocks()
{
    idealBlockSetupVector.push_back(&BlockError::completeBlock);
    idealBlockSetupVector.push_back(&BlockError::nullBlock);
    
//    idealBlockSetupVector.push_back(&BlockError::rowDominant);
//    idealBlockSetupVector.push_back(&BlockError::colDominant);
//    idealBlockSetupVector.push_back(&BlockError::colFunctional);
//    idealBlockSetupVector.push_back(&BlockError::rowFunctional);
//    idealBlockSetupVector.push_back(&BlockError::rowRegular);
//    idealBlockSetupVector.push_back(&BlockError::colRegular);
//    idealBlockSetupVector.push_back(&BlockError::regularBlock);
}



