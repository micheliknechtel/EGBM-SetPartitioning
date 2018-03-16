//
//  ClusterSetBuilder.hpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 18/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef ClusterSetBuilder_hpp
#define ClusterSetBuilder_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

class ClusterSetBuilder {
    int networkSize;
    vector<int> element;
    vector<int> cluster;
    map<int,vector<int>> clusterSets;
    map<int,vector<int>> epsilon;
   public:
    ClusterSetBuilder();
    void generateSet();
    void generateSet(int offset, int k);
    void epsilonAddClusterIndex(const vector<int>& v);
    void writeSet(const vector<int>& v);
};
#endif /* ClusterSetBuilder_hpp */
