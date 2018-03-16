//
//  SetPartitioning.cpp
//  GBlockModeling
//
//  Created by Micheli  Knechtel on 16/06/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "SetPartitioning.hpp"
#include "DataManager.hpp"
#include <time.h>
#include "Definitions.h"
#include "PrintManager.hpp"
#include "SetPartitioningModel.hpp"

void SetPartitioning::solveCplexModel()
{
    IloEnv env;
    
    try
    {
        IloModel model(env);
        IloCplex cplex(model);
        IloTimer timer(env);        

        const IloNum startTime = cplex.getCplexTime();
        
        SetPartitioningModel *setPartitioningModel = new SetPartitioningModel(model,env);
        setPartitioningModel->criterionFunction();
        setPartitioningModel->ctr_sum_xk1_equals_one();
        setPartitioningModel->ctr_zk1k2_reinforcement_link();
        
        if (DataManager::getDataManager()->getAddicionalConstraint())
            setPartitioningModel->ctr_xk2();
        
        cplex.exportModel(DataManager::getDataManager()->getModelFileName().c_str());
        
        if(!cplex.solve())
        {
            env.error() << "Failed to optimize LP" << endl;
            throw(-1);
        }
       
        timer.stop();
        const IloNum endTime = cplex.getCplexTime();
        
        PrintManager().printCplexResults(cplex.getStatus(),
                                         cplex.getObjValue(),
                                         cplex.getMIPRelativeGap(),
                                         (int) cplex.getNnodes(),
                                         endTime - startTime );
        
        setPartitioningModel->getSolution(cplex);
    }
    catch (IloException& e)
    {
        cerr << "Error: " << e << endl;
    }
    catch (...)
    {
        cerr << "Unknown exception caught" << endl;
    }
    env.end();
}

