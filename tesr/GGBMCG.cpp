//
//  GGBMCG.cpp
//  GGBMCG
//
//  Created by Micheli Knechtel on 17/07/2017.
//  Copyright © 2017 Micheli Knechtel. All rights reserved.
//

#include "GGBMCG.hpp"
#include <stdio.h>
#include <string.h>
#include "Definitions.h"
#include "Parameters.hpp"
#include "ClusterSetBuilder.hpp"
#include "DesviationMesuare.hpp"
#include "PrintManager.hpp"
#include "SetPartitioning.hpp"

int main (int argc, char **argv)
{
    Parameters * parameters = new Parameters();
    parameters->predefinedParameters();
    
    ClusterSetBuilder *clusterSet = new ClusterSetBuilder();
    clusterSet->generateSet();
    
    PrintManager().printAllClusterSet();
    PrintManager().printEpsilon();
    
    DesviationMesuare *desviationMesuare = new  DesviationMesuare();
    desviationMesuare->calculate();
    
    SetPartitioning * setPartitioning = new SetPartitioning();
    setPartitioning->solveCplexModel();
}
