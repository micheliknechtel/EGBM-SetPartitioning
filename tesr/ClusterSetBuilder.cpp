//
//  ClusterSetBuilder.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 18/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "ClusterSetBuilder.hpp"
#include "DataManager.hpp"
#include "PrintManager.hpp"

ClusterSetBuilder::ClusterSetBuilder()
{
    this->networkSize = DataManager::getDataManager()->getNetworSize();
}

void ClusterSetBuilder::generateSet()
{
    
    for (int i =-1; i <networkSize-1; ++i)
    {
        element.push_back(i+1);
        epsilon.insert(make_pair(i+1, vector<int>()));
    }
    
    for (int i = 0; i <networkSize; ++i)
    {
        generateSet(0, i);
    }
    
    epsilonAddClusterIndex(element);
    DataManager::getDataManager()->setClusterSets(clusterSets);
    DataManager::getDataManager()->setEpsilon(epsilon);
}


void ClusterSetBuilder::epsilonAddClusterIndex(const vector<int>& v)
{
    static int count = 0;
    clusterSets.insert(make_pair(count, v));
    
    for (int i = 0; i<v.size(); i++)
    {
        epsilon.at(v[i]).push_back(count);
    }
    ++count;
}

void ClusterSetBuilder::generateSet(int offset, int k)
{
    if (k == 0 && offset == 0 )
        return;
    
    if (k == 0)
    {
        epsilonAddClusterIndex(cluster);
        return;
    }
    
    for (int i = offset; i <= element.size() - k; ++i)
    {
        cluster.push_back(element[i]);
        generateSet(i+1, k-1);
        cluster.pop_back();
    }
}
