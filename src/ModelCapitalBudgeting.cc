/**
 * ModelCapitalBudgeting.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "ModelCapitalBudgeting.h"
#include "Options.h"
#include "DataCapitalBudgeting.h"

/**
 * INITIAL METHODS
 */

// If dataModelCapitalBudgeting was a reference
//ModelCapitalBudgeting::ModelCapitalBudgeting(DataModelCapitalBudgeting& i) : Model(), dataModelCapitalBudgeting(i) {
ModelCapitalBudgeting::ModelCapitalBudgeting() : Model(){
    V = 0;
    x = "x";
}

ModelCapitalBudgeting::~ModelCapitalBudgeting() {
}


void ModelCapitalBudgeting::execute(const Data* data) {

    float startTime = Util::getTime();
    
    if (debug > 1) solver->printSolverName();
    createModel(data);
    reserveSolutionSpace(data);
    assignWarmStart(data);
    setSolverParameters(1);

    solver->addInfoCallback(this);
    //solver->addLazyCallback(this);
    //solver->addUserCutCallback(this);

    solve(data);
    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
}  


void ModelCapitalBudgeting::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        printf("\nSolution: \n");
        for (int i = 0; i < V; i++) {
            printf("  x%d = %.0f\n", i, sol_x[i]);
    
        }
    }

}



void ModelCapitalBudgeting::reserveSolutionSpace(const Data* data) {
    sol_x.resize(V);
}




void ModelCapitalBudgeting::readSolution(const Data* data) {
    totalNodes = solver->getNodeCount();
    solution->resetSolution();
    solution->setSolutionStatus(solver->solutionExists(), solver->isOptimal(),  solver->isInfeasible(), solver->isUnbounded());
    if (!solver->solutionExists()) {
        if (debug) printf("Solution does not exist\n");        
    } else {
        solution->setValue    (solver->getObjValue() );
        solution->setBestBound(solver->getBestBound());

        for (int i = 0; i < V; i++) {
            sol_x[i] = solver->getColValue(x + lex(i));
        }

        // Para ler aresta 1-2
        //double xx = solver->getColValue(x + lex(1) + "_" lex(2));
    }
}


void ModelCapitalBudgeting::createModel(const Data* data) {
    
    const DataCapitalBudgeting* dataCB = dynamic_cast<const DataCapitalBudgeting*>(data);
    V = dataCB->getNumVariables();
    solver->changeObjectiveSense(1);

    for (int i = 0; i < V; i++)
        solver->addBinaryVariable(dataCB->getFutureValue(i), x + lex(i));

    vector<string> colNames;
    vector<double> elements;

    colNames.resize(V);
    elements.resize(V);
    for (int i = 0; i < V; i++) {
        colNames[i] = x + lex(i);
        elements[i] = dataCB->getInitialInvestment(i);
    }
    solver->addRow(colNames, elements, dataCB->getMaxInvestment(), 'L', "constraint");
    
    // x_2 + x_3 <= 1 (Restricoes podem ser 'G', 'E' ou 'L'
    //colNames.resize(2);
    //elements.resize(2);
    //colNames[0] = x + lex(2);
    //colNames[1] = x + lex(3);
    //elements[0] = 1;
    //elements[1] = 1;
    //solver->addRow(colNames, elements, 1, 'L', "eou2ou3");
    
    //x1 + 5*x2 <= 3
    //colNames.resize(2);
    //elements.resize(2);
    //colNames[0] = x + lex(1);            
    //colNames[1] = x + lex(2);
    //elements[0] = 1;
    //elements[1] = 5;
    //solver->addRow(colNames, elements, 3, 'L', "restricaoExemplo");

    // Suponha o lista de adjacencia:
    //vector<vector<int>>vvv;
    //0: 1 2
    //1: 2
    //2: 3       
    //3
    // Criar variavel para cada aresta:
    //for (int i  = 0; i < (int) vvv.size(); i++) {
    //    for (int j = 0; j < (int) vvv[i].size(); j++) {
    //        solver->addBinaryVariable(1, x + lex(i) + "_" + lex(vvv[i][j]);
    //    }
    //}



}


void ModelCapitalBudgeting::assignWarmStart(const Data* data) {
   
}




//////////////////////////////
//////////////////////////////
//////////////////////////////
//////////////////////////////
// Cutting plane

/*
vector<SolverCut> ModelCapitalBudgeting::separationAlgorithm(vector<double> sol) {

    

    vector<SolverCut> cuts;

    // Finding out whether the current solution is integer or not
    int isInteger = 1;
    for (unsigned i = 0; i < sol.size(); i++) {
        if (fabs(sol[i] - round(sol[i])) > TOLERANCE) {
            //printf("%.3f ", sol[i]);
            isInteger = 0;
            break;
        }
    }


    ///////
    // Cut example
    
    // Finding the value of a specific variable in the current linear relaxation
    //double ysol = sol[solver->getColIndex(y + lex(t) + "_" + lex(b))];
      
    // Creating and adding a cut y_{tb} >= -1 as an example
    //SolverCut cut;
    //cut.setSense('G');
    //cut.addCoef(solver->getColIndex(y + lex(t) + "_" + lex(b)), 1);
    //cut.setRHS(-1);
    //cuts.push_back(cut);



    return cuts;
}
*/
