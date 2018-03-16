//
//  Definitions.h
//  tesr
//
//  Created by Micheli  Knechtel on 18/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#ifndef Definitions_h
#define Definitions_h

#include <ilcplex/ilocplex.h>
#include <iostream>

using namespace std;

#define STR( x ) static_cast<ostringstream >( \
( ostringstream() << dec  << x ) ).str()

#define STR_C( x ) static_cast< std::ostringstream >( \
( std::ostringstream() << std::dec << "[" << x << "]") ).str()

#define STR_P( x ) static_cast< std::ostringstream >( \
( std::ostringstream() << std::dec << "(" << x << ")") ).str()



#if LOGLEVEL > 0
#define LOG(name) cout<<name<<endl;
#else
#define LOG(name)
#endif

struct clusterGroup
{
    int *elements;
    int size;
};


enum IdealBlock
{
    NBDZ,
    CBDO,
    RRB,
    CRB,
    RB,
    RDDO,
    CDDO,
    CF,
    RF
};

enum DecisionVariableType
{
    ILOINTVAR,
    ILONUMVAR
};

struct fitness {
    int error;
    int blockType;
};

ILOSTLBEGIN

IloIntVar
typedef IloIntVar;
typedef IloArray<IloIntVarArray> IloIntVarArray2;
typedef IloArray<IloIntVarArray2> IloIntVarArray3;
typedef IloArray<IloIntVarArray3> IloIntVarArray4;

typedef IloArray<IloBoolVarArray> IloBoolVarArray2;
typedef IloArray<IloBoolVarArray2> IloBoolVarArray3;
typedef IloArray<IloBoolVarArray3> IloBoolVarArray4;

typedef IloArray<IloBoolArray> IloBoolArray2;

typedef IloArray<IloNumVarArray> IloNumVarMatrix;
typedef IloArray<IloNumArray> IloNumMatrix;

//mudança ...

typedef IloArray<IloNumVarArray> IloNumVarArray2;
typedef IloArray<IloNumVarArray2> IloNumVarArray3;
typedef IloArray<IloNumVarArray3> IloNumVarArray4;

enum MatrixDataType
{
    BINARY,
    EDGES,
    XML,
    LABEL,
    UNKNOW
};

#endif /* Definitions_h */
