//
//  SetPartitioningModel.hpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 21/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#ifndef SetPartitioningModel_hpp
#define SetPartitioningModel_hpp
#include "Definitions.h"
#include <stdio.h>
#include <map>

class SetPartitioningModel {
    IloModel model;
    IloEnv env;
    IloIntVarArray x;
    IloIntVarArray2 z;
    
public:
    SetPartitioningModel(IloModel model,IloEnv env);
    void criterionFunction();
    void ctr_sum_xk1_equals_one();
    void ctr_zk1k2_equals_and_bigger_than_zero();
    void ctr_zk1k2_reinforcement_link();
    void ctr_xk2();
    bool find(int i, int k);
    void getSolution(IloCplex cplex);
    void getZ(IloCplex cplex);
    void getX(IloCplex cplex);
};
#endif /* SetPartitioningModel_hpp */
