#include "ModelGAP.h"
#include "Options.h"
#include "DataGAP.h"
#include <iostream>

ModelGAP::ModelGAP() : Model() {
    //number of agents (V) and tasks (T)
    V = 0;
    T = 0;
    x = "x";
}


ModelGAP::~ModelGAP() {
}


void ModelGAP::execute(const Data* data) {
    
    float startTime = Util::getTime();

    if (debug > 1) solver->printSolverName();
    
    
    createModel(data);
    reserveSolutionSpace(data);
    assignWarmStart();
    setSolverParameters(1); // 1 = maximization
    
    solver->addInfoCallback(this);
    
    solve(data);
    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
}


void ModelGAP::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        printf("\nSolution: \n");
        for (int i = 0; i < T; i++) {
            for (int j = 0; j < V; j++) {
                printf("  x_%d_%d = %.0f\n", i, j, sol_x[i][j]);
            }
        }
    }
}


void ModelGAP::reserveSolutionSpace(const Data* data) {
    sol_x.resize(T, vector<double> (V,0));
}

void ModelGAP::readSolution() {
    totalNodes = solver->getNodeCount();
    solution->resetSolution();
    solution->setSolutionStatus(solver->solutionExists(), solver->isOptimal(), solver->isInfeasible(), solver->isUnbounded());
    if (!solver->solutionExists()) {
        if (debug) printf("Solution does not exist\n");
    }
    else {
        solution->setValue    (solver->getObjValue() );
        solution->setBestBound(solver->getBestBound());

        for (int i = 0; i < T; i++) {
            for (int j = 0; j < V; j++) {
                sol_x[i][j] = solver->getColValue(x + lex(i) + lex(j));
            }
        }
    }
}


void ModelGAP::createModel(const Data* data) {
    
    const DataGAP* dataG = dynamic_cast<const DataGAP*>(data);
    V = dataG->getNumVariables();
    T = dataG->getNumTasks();
    
    //1 = maximisation problem, 0 = minimisation problem
    solver->changeObjectiveSense(1);

    
    
    //objective function data
    for (int j = 0; j < V; j++) {
        for (int i = 0; i < T; i++) {
            solver->addBinaryVariable(dataG->getProfitMatrix(i,j), x + lex(i) + lex(j));
        }
    } 
    
    
    //constraints data 
    vector<vector<string> > colNames;
    vector<vector<string> > colNames2;

    vector<vector<double> > weights;
    vector<double> ones_array;
    
    colNames.resize(T, vector<string> (V, " "));
    colNames2.resize(V, vector<string> (T, " "));

    weights.resize(V, vector<double> (T, 0));
    ones_array.resize(V, 1);
    
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < V; j++) {
            colNames[i][j] = x + lex(i) + lex(j);
            colNames2[j][i] = x + lex(i) + lex(j);
        }
    }


    //a matrix weights eh transposta
    //pois addRow() recebe vetores coluna    
    for (int i = 0; i < T; i++) {
        for (int j = 0; j < V; j++) {
            weights[j][i] = dataG->getWeightMatrix(i,j);
        }
    }
        
    for (int j = 0; j < V; j++) {
        solver->addRow(colNames2[j], weights[j], dataG->getAgentBudget(j), 'L', "Agent " + lex(j) + " Budget");
    } 

    //'each task to exactly one agent' constraint
    for (int i = 0; i < T; i++) {
        solver->addRow(colNames[i], ones_array, 1, 'E', "each task to one agent");
    }



}

void ModelGAP::assignWarmStart() {

}
