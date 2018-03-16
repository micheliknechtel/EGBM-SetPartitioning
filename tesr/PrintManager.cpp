//
//  PrintManager.cpp
//  GGBM HEURISTIC
//
//  Created by Micheli Knechtel on 03/02/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "PrintManager.hpp"
#include "Definitions.h"

using namespace std;

void PrintManager::printPartition(map<int,vector<int>> partition)
{
//    if(logLevel)
    {
   
        for (map<int,vector<int>> ::iterator it = partition.begin();it!= partition.end(); it++)
        {
            cout<<"C"<<it->first<<" = { ";
            for (int i = 0; i<it->second.size(); i++)
            {
                if(i==it->second.size()-1)
                    cout<<it->second.at(i);
                else
                    cout<<it->second.at(i)<<" , ";
            }
            cout<<" }"<<endl;
        }
    }
}

void PrintManager::printMatrixBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    for (int i = 0; i < C1.size(); i++)
    {
        for (int j = 0; j < C2.size(); j++)
            cout << relationMatrix[C1[i]][C2[j]]<<" ";
        cout<<endl;
    }
    
}


void PrintManager::errorHeader(int error)
{
    if(logLevel)
    {
        cout<<endl<<"----------------------------------------------------"<<endl<<endl;
        cout<<"TOTAL ERROR == "<<error<<endl<<endl;
    }
}

void PrintManager::printTime( time_t startTime)
{
    time_t endTime = time(&endTime);
    double currentTime = difftime(endTime, startTime );
    cout<<"ElapsedTime      = "<<currentTime<<" (in seconds)"<<endl;
}


void PrintManager::newLine()
{
    cout<<endl<<endl;
}

void PrintManager::inputData()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"RelationMatrix:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    printRelationMatrix();
}


void PrintManager::printRelationMatrix()
{
    int totalOne=0;
    int sumOneLine =0;
    int sumOneColumn=0;
    int totalOneDiagonal = 0;
    int networkSize = DataManager::getDataManager()->getNetworSize();
    relationMatrix = DataManager::getDataManager()->getRelationMatrix();
    
    for ( int i = 0; i < networkSize; i++ )
    {
        for ( int j = 0; j < networkSize; j++ )
        {
            if (relationMatrix[i][j]==1)
            {
                sumOneLine++;
                totalOne++;
            }
            
            if (relationMatrix[j][i]==1)
            {
                sumOneColumn++;
            }
            
            if (relationMatrix[i][j]==1 && i==j)
            {
                totalOneDiagonal++;
            }
            cout<<" "<<relationMatrix[i][j];
        }
        cout<<" | line = ";
        cout.fill( ' ' );
        cout.width( 5 );
        cout << sumOneLine;
        cout<<" | colum = ";
        cout.fill( ' ' );
        cout.width( 5 );
        cout<<sumOneColumn;
        cout<<endl;
        sumOneLine = 0;
        sumOneColumn = 0;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Aditional information: "<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Number of one's in diagonal   = ["<<totalOneDiagonal<<"]"<<endl;
    cout<<"Number of one's in the matrix = ["<<totalOne<<"]"<<endl;
    cout<<"Matrix size                   = ["<<networkSize<<"]"<<endl;
}


void PrintManager::printEpsilon()
{

    cout<<"----------------------------------------------------"<<endl;
    cout<<"epsilon (i): such that i in {1,...,"<<DataManager::getDataManager()->getNetworSize()<<"}"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    for (int i = 0; i <DataManager::getDataManager()->getNetworSize(); ++i)
    {
        cout<<"epsilon ("<< i<<") = { ";
        for (int j = 0; j<DataManager::getDataManager()->getEpsilon().at(i).size(); ++j)
            cout<<DataManager::getDataManager()->getEpsilon().at(i).at(j)<<" ";
        cout<<"}"<<endl;
    }
    cout<<"----------------------------------------------------"<<endl;

}

void PrintManager::printAllClusterSet()
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Cluster Set's:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    for (int i = 0; i <  DataManager::getDataManager()->getClusterSets().size(); ++i)
    {
        cout << "C" << (i) << " = { ";

        int size = (int) DataManager::getDataManager()->getClusterSets().at(i).size();
        for (int j = 0; j<size; j++)
        {
            if(j == size-1)
                cout << DataManager::getDataManager()->getClusterSets().at(i).at(j) << " ";
            else
                cout <<DataManager::getDataManager()->getClusterSets().at(i).at(j)<< " , ";
        }
        cout << "} " << endl;

    
    }
   
}

void PrintManager::printBlock(int cluster_k, int cluster_l,  map<int,vector<int>>partition)
{
    vector<int> C1 = partition.at(cluster_k);
    vector<int> C2 = partition.at(cluster_l);
    string strC1 = "\nC" + STR(cluster_k) + " = { ";
    string strC2 = "C" + STR(cluster_l) + " = { ";
    for (int i = 0; i < C1.size(); i++)
    {
        if (i!=C1.size()-1)
            strC1+= STR(C1[i]) + " , ";
        else
            strC1+= STR(C1[i]);
    }
    strC1+=" }";
    for (int j = 0; j < C2.size(); j++)
    {
        if (j!=C2.size()-1)
            strC2+= STR(C2[j]) + " , ";
        else
            strC2+= STR(C2[j]);
    }
    strC2+=" }";
    cout<<strC1<<endl;
    cout<<strC2<<endl;
    
}

void PrintManager::printE()
{
    int size = DataManager::getDataManager()->getE().size();
    
    map<pair<int, int>, fitness> aux =  DataManager::getDataManager()->getE();
    map<pair<int, int>, fitness>::iterator it = aux.begin();
    
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Error:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    
    for (;it!= aux.end(); ++it)
    {
        int k1 = it->first.first;
        int k2 = it->first.second;
        cout<<"----------------------------------------------------"<<endl;

        cout<< "E("<<k1<< ","<<k2<<") = " <<it->second.error<<endl<<"blocktype = "<<it->second.blockType;
        PrintManager().printBlock(k1, k2, DataManager::getDataManager()->getClusterSets());
        cout<<"Matrix"<<endl;
        PrintManager().printMatrixBlock(k1, k2, DataManager::getDataManager()->getClusterSets());
        cout<<"----------------------------------------------------"<<endl;

    }
}

void PrintManager::printCplexResults(bool status, double objValue, double MIPRelativeGap,int nodes, double elapsedTime)
{
    cout<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Resolution information:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Solution status                  = " << status << endl;
    cout<<"Minimal Objective Function Value = " << objValue << endl;
    cout<<"Gap                              = " << MIPRelativeGap<<endl;
    cout<<"Nodes                            = " << nodes <<endl;
    cout<<"Elapsed wall clock time          = " << elapsedTime << " seconds" << endl;
    cout<<"Relation Matrix                  = " << DataManager::getDataManager()->getRelationMatrixFileName() <<endl;
    cout<<"Decision variable type (x,z)     = " << (DataManager::getDataManager()->getDecisionVariableType() == ILOINTVAR ?"IlointVar":"IloNumVar")<<endl;
}



void PrintManager::buildMatrix(map<int, vector<int>> partition)
{
    map<string,clusterGroup> group = buildGroup(partition);
    map<string,clusterGroup>::iterator it = group.begin();
    std::map<string,clusterGroup>::iterator itAux = group.begin();
    int networkSize = DataManager::getDataManager()->getNetworSize();
    string blockMatriz  = "\n   ";
    
    for (it=group.begin(); it!=group.end(); ++it)
    {
        clusterGroup g = it->second;
        
        if (g.size == 0)
            blockMatriz +="E ";
        else
        {
            for (int i = 0; i<g.size; i++)
            {
                blockMatriz +=STR(g.elements[i]);
                
                if (g.size-1==i)
                    blockMatriz+=" ";
            }
        }
    }
    
    blockMatriz+="\n";
    
    for (it=group.begin(); it!=group.end(); ++it)
    {
        clusterGroup g = it->second;
        for (int i = 0; i<g.size; i++)
        {
            itAux = group.begin();
            
            blockMatriz += " " +STR(g.elements[i]);
            
            for(int k = 0; k<partition.size(); k++)
            {
                if (networkSize!=1)
                    blockMatriz+=" ";
                
                clusterGroup gAux = itAux->second;
                
                if (gAux.size ==0)
                    blockMatriz += "-";
                
                for (int l = 0; l<gAux.size; l++)
                {
                    if (networkSize==1 && l == 0)
                        blockMatriz+=" ";
                    
                    blockMatriz += STR(DataManager::getDataManager()->getRelationMatrix()[g.elements[i]][gAux.elements[l]]);
                }
                if (networkSize==1)
                    blockMatriz+="\n";
                itAux++;
            }
            if (g.size-1!=i && networkSize!=1)
                blockMatriz+="\n";
        }
        if (networkSize!=1)
            blockMatriz+="\n\n";
    }
    cout<<blockMatriz;
}



map<string,clusterGroup>  PrintManager::buildGroup(map<int, vector<int>> partition)
{
    map<string,clusterGroup> group;
    
    int networkSize = DataManager::getDataManager()->getNetworSize();
    int i=0;
    for (map<int,vector<int>> ::iterator it = partition.begin();it!= partition.end(); it++)
    {
        string clusterName= "C" + STR(i);
        int *elements = (int *) malloc(networkSize*sizeof(int));
        
        for (int j = 0; j<DataManager::getDataManager()->getClusterSets().at(it->first).size(); j++)
        {
            elements[j] = DataManager::getDataManager()->getClusterSets().at(it->first).at(j);
        }
        clusterGroup g;
        g.elements = elements;
        g.size = (int) DataManager::getDataManager()->getClusterSets().at(it->first).size();
        group.insert(pair<string, clusterGroup>(clusterName,g));
        i++;
    }
    return group;
}

void PrintManager::printSolution(map<int, vector<int>> partition)
{
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Partition relation matrix:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    PrintManager().buildMatrix(partition);
    cout<<"----------------------------------------------------"<<endl;
    cout<<"Choosen clusters:"<<endl;
    cout<<"----------------------------------------------------"<<endl;
    PrintManager().printPartition(partition);
    cout<<"----------------------------------------------------"<<endl;
}
