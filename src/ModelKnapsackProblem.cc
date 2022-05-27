
#include "ModelKnapsackProblem.h"
#include "Options.h"
#include "DataKnapsackProblem.h"

/**
 * INITIAL METHODS
 */

ModelKnapsackProblem::ModelKnapsackProblem() : Model(){
    V = 0;
    x = "x";
}

ModelKnapsackProblem::~ModelKnapsackProblem() {
}

void ModelKnapsackProblem::execute(const Data* data) {

    float startTime = Util::getTime();
    
    if (debug > 1) solver->printSolverName();
    createModel(data);
    reserveSolutionSpace(data);
    assignWarmStart(data);
    setSolverParameters(1);

    solver->addInfoCallback(this);

    solve(data);
    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
}  

void ModelKnapsackProblem::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        printf("\nSolution: \n");
        for (int i = 0; i < V; i++) {
            printf("  x%d = %.0f\n", i, sol_x[i]);
    
        }
    }

}

void ModelKnapsackProblem::reserveSolutionSpace(const Data* data) {
    sol_x.resize(V);
}

void ModelKnapsackProblem::readSolution(const Data* data) {
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
    }
}

void ModelKnapsackProblem::createModel(const Data* data) {
    
    const DataKnapsackProblem* dataKP = dynamic_cast<const DataKnapsackProblem*>(data);
    V = dataKP->getNumVariables();
    solver->changeObjectiveSense(1);

    for (int i = 0; i < V; i++)
        solver->addBinaryVariable(dataKP->getReturnValue(i), x + lex(i));

    vector<string> colNames;
    vector<double> elements;

    colNames.resize(V);
    elements.resize(V);

    for (int i = 0; i < V; i++) {
        colNames[i] = x + lex(i);
        elements[i] = dataKP->getCost(i);
    }
    
    solver->addRow(colNames, elements, dataKP->getCapacity(), 'L', "constraint");
}

void ModelKnapsackProblem::assignWarmStart(const Data* data) {
   
}