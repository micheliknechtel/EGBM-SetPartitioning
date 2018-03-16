//
//  SetPartitioningModel.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 21/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "SetPartitioningModel.hpp"
#include "DataManager.hpp"
#include "MultidimensionaIloArray.hpp"
#include "PrintManager.hpp"
#include "Definitions.h"

SetPartitioningModel::SetPartitioningModel(IloModel model,IloEnv env)
{
    this->env = env;
    this->model = model;
    
    x = MultidimensionaIloArray::IloIntVarArray1D(env, (int) DataManager::getDataManager()->getClusterSets().size(), 0, 1, "x");
    z = MultidimensionaIloArray::IloIntVarArray2D(env, (int) DataManager::getDataManager()->getClusterSets().size(), 0 , 1, "z");
    
    if (DataManager::getDataManager()->getDecisionVariableType() == ILONUMVAR)
    {
        model.add(IloConversion(env, x, ILOFLOAT));
        
        for(int i=0; i <(int) DataManager::getDataManager()->getClusterSets().size(); i++)
        {
            model.add(IloConversion(env, z[i], ILOFLOAT));
        }
    }
}

void SetPartitioningModel::ctr_sum_xk1_equals_one()
{
    for (int i = 0; i <DataManager::getDataManager()->getNetworSize(); i++)
    {
        IloExpr expr_01(env);
        
        for (int k1 = 0; k1<DataManager::getDataManager()->getEpsilon().at(i).size(); k1++)
        {
            expr_01 += x[DataManager::getDataManager()->getEpsilon().at(i).at(k1)];
            
        }
        string name = "x" + STR_P(i);
        IloConstraint constraint = (expr_01 == 1);
        constraint.setName(name.c_str());
        model.add(constraint);
        expr_01.end();
    }
}

void SetPartitioningModel::ctr_zk1k2_reinforcement_link()
{
    
    for (int k1 = 0; k1<DataManager::getDataManager()->getClusterSets().size(); k1++)
    {
        for (int k2 = k1+1; k2<DataManager::getDataManager()->getClusterSets().size(); k2++)
        {
            IloExpr expr_01(env);
            expr_01 += x[k1]+x[k2]-1;
            string name = "z" + STR_P(k1) + STR_P(k2);
            IloConstraint constraint = (z[k1][k2]>=expr_01 );
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
        }
    }
}

void SetPartitioningModel::ctr_xk2()
{
    for (int i = 0; i<DataManager::getDataManager()->getNetworSize(); i++)
    {
        vector<int> notIn;
        cout<<"not in epsilon ("<<i<<") = { ";
        
        
        for (int element = 0; element<DataManager::getDataManager()->getClusterSets().size(); element++)
        {
            if(find(i, element)==false)
            {
                cout<<element<<" ";
                notIn.push_back(element);
            }
            
        }
        cout<<"}"<<endl;
        
        
        for (int index_k2 = 0; index_k2<notIn.size(); index_k2++)
        {
            int k2 = notIn.at(index_k2);
            IloExpr expr_01(env);

            cout<<"sum:( ";
            
            for (int index_k1 = 0; index_k1<DataManager::getDataManager()->getEpsilon().at(i).size(); index_k1++)
            {
                bool flag = true;
                int k1 = DataManager::getDataManager()->getEpsilon().at(i).at(index_k1);
               
                if (k1<k2)
                {
                    cout<<"z("<<k1<<","<<k2<<") + ";
                    expr_01 += z[k1][k2];
                }
                if (k1>k2)
                {
                        expr_01 += z[k2][k1];
                        cout<<"z("<<k2<<","<<k1<<") + ";
                }

            }
            IloConstraint constraint = (expr_01 == x[k2]);
            string name = "xk" + STR_P(k2);
            constraint.setName(name.c_str());
            model.add(constraint);
            expr_01.end();
            cout<<") = x"<<k2<<endl;
        }
    }
    cout<<endl;
}

bool SetPartitioningModel::find(int i, int k)
{
    for (int h = 0; h<DataManager::getDataManager()->getEpsilon().at(i).size(); h++)
    {
        if (DataManager::getDataManager()->getEpsilon().at(i).at(h)==k)
        {
            return true;
        }
    }
    return false;
}

void SetPartitioningModel::criterionFunction()
{
    IloExpr expr_01(env);
    IloExpr expr_02(env);
    
    for (int k1 = 0; k1<DataManager::getDataManager()->getClusterSets().size(); k1++)
    {
        int error_k1_k1 = DataManager::getDataManager()->getE().at(make_pair(k1, k1)).error;
        
        expr_01 += error_k1_k1 * x[k1];
        
        for (int k2 = k1+1; k2<DataManager::getDataManager()->getClusterSets().size(); k2++)
        {
            int error_k1_k2 = DataManager::getDataManager()->getE().at(make_pair(k1, k2)).error;
            int error_k2_k1 = DataManager::getDataManager()->getE().at(make_pair(k2, k1)).error;
            
            expr_02 += ( error_k1_k2 + error_k2_k1 ) * z[k1][k2];
        }
    }
    
    IloObjective obj = IloMinimize(env, expr_01  +expr_02);
    model.add(obj);
}

void SetPartitioningModel::getSolution(IloCplex cplex)
{
    vector<int> choosendClusters;
    
    for (int i = 0; i<DataManager::getDataManager()->getClusterSets().size(); i++)
    {
        if (cplex.isExtracted(x[i]))
        {
            if(cplex.getValue(x[i])>0)
                choosendClusters.push_back(i);
        }
    }
    
    map<int,vector<int>> partition;
    
    for (int i = 0; i<choosendClusters.size(); i++)
    {
        vector<int> v = DataManager::getDataManager()->getClusterSets().at(choosendClusters.at(i));
        partition.insert(make_pair(choosendClusters.at(i), v));
    }
    
    PrintManager().printSolution(partition);
}

void SetPartitioningModel::getZ(IloCplex cplex)
{
    for (int k1 = 0; k1<DataManager::getDataManager()->getClusterSets().size(); k1++)
    {
        for (int k2 = k1+1; k2<DataManager::getDataManager()->getClusterSets().size(); k2++)
        {
            if (cplex.isExtracted(z[k1][k2]))
            {
                cout<<"z["<<k1<<"]["<<k2<<"]= "<<cplex.getValue(z[k1][k2])<<endl;
            }
        }
    }
}

void SetPartitioningModel::getX(IloCplex cplex)
{
    for (int i = 0; i<DataManager::getDataManager()->getClusterSets().size(); i++)
    {
        if (cplex.isExtracted(x[i]))
        {
            cout<<"x["<<i<<"] = "<<cplex.getValue(x[i])<<endl;
            
        }
    }
}

