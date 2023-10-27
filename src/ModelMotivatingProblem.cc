
#include "ModelMotivatingProblem.h"
#include "Options.h"
#include "DataMotivatingProblem.h"
#include "Util.h"

/**
 * INITIAL METHODS
*/

ModelMotivatingProblem::ModelMotivatingProblem() : Model(){
    V = 0;
    x = "x";
}

ModelMotivatingProblem::~ModelMotivatingProblem() {
}

void ModelMotivatingProblem::execute(const Data* data) {

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

void ModelMotivatingProblem::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        printf("\nSolution: \n");
        for (int i = 0; i < V; i++) {
            printf("  x%d = %.0f\n", i, sol_x[i]);
    
        }
    }

}

void ModelMotivatingProblem::reserveSolutionSpace(const Data* data) {
    sol_x.resize(V);
}

void ModelMotivatingProblem::readSolution(const Data* data) {
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


void ModelMotivatingProblem::createModel(const Data* data) {
    
    const DataMotivatingProblem* dataMP = dynamic_cast<const DataMotivatingProblem*>(data);
    V = dataMP->getNumVariables();
    solver->changeObjectiveSense(1);

    // objective function
    for (int i = 0; i < V; i++)
        solver->addVariable(0, INFINITO_DOUBLE, dataMP->getObjectiveCoefficients(i), x + lex(i));

    vector<string> colNames;
    vector<double> elements;

    colNames.resize(V);
    elements.resize(V);

    // First constraint
    for (int i = 0; i < V; i++) {
        colNames[i] = x + lex(i);
        elements[i] = dataMP->getFirstConstraintCoefficients(i);
    }
    solver->addRow(colNames, elements, dataMP->getFirstConstraintMaxValue(), 'L', "constraint");
    

    // Second constraint
    for (int i = 0; i < V; i++) {
        colNames[i] = x + lex(i);
        elements[i] = dataMP->getSecondConstraintCoefficients(i);
    }
    solver->addRow(colNames, elements, dataMP->getSecondConstraintMaxValue(), 'L', "constraint");


    // Third constraint
    for (int i = 0; i < V; i++) {
        colNames[i] = x + lex(i);
        elements[i] = dataMP->getThirdConstraintCoefficients(i);
    }
    solver->addRow(colNames, elements, dataMP->getThirdConstraintMaxValue(), 'L', "constraint");
}


void ModelMotivatingProblem::assignWarmStart(const Data* data) {
   
}