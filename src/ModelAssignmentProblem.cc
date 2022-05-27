
#include "ModelAssignmentProblem.h"
#include "Options.h"
#include "DataAssignmentProblem.h"

ModelAssignmentProblem::ModelAssignmentProblem() : Model(){
    V = 0;
    x = "x";
}

ModelAssignmentProblem::~ModelAssignmentProblem() {
}


void ModelAssignmentProblem::execute(const Data* data) {

    float startTime = Util::getTime();
    
    if (debug > 1) solver->printSolverName();
    createModel(data);
    reserveSolutionSpace(data);
    assignWarmStart(data);
    setSolverParameters(0);

    solver->addInfoCallback(this);

    solve(data);
    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
}  


void ModelAssignmentProblem::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        printf("\nSolution: \n");
        for (int i = 0; i < V; i++) {
            printf("\t Xi%d", i);
        }
        printf("\n");
        for (int i = 0; i < V; i++) {
            printf("X%dj", i);
            for (int j = 0; j < V; j++) {
                printf("\t %.0f", sol_x[i][j]);
            }
            printf("\n");
        }
    }

}

void ModelAssignmentProblem::reserveSolutionSpace(const Data* data) {
    sol_x.resize(V, vector<double>(V));
}

void ModelAssignmentProblem::readSolution(const Data* data) {
    totalNodes = solver->getNodeCount();
    solution->resetSolution();
    solution->setSolutionStatus(solver->solutionExists(), solver->isOptimal(),  solver->isInfeasible(), solver->isUnbounded());
    if (!solver->solutionExists()) {
        if (debug) printf("Solution does not exist\n");        
    } else {
        solution->setValue    (solver->getObjValue() );
        solution->setBestBound(solver->getBestBound());

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                sol_x[i][j] = solver->getColValue(x + lex(i) + lex(j));
            }
        }
    }
}

void ModelAssignmentProblem::createModel(const Data* data) {
    
    const DataAssignmentProblem* dataAP = dynamic_cast<const DataAssignmentProblem*>(data);
    V = dataAP->getNumVariables();
    solver->changeObjectiveSense(0);

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            solver->addBinaryVariable(dataAP->getCost(i, j), x + lex(i) + lex(j));
        }
    }

    vector<vector<string>> colNames;
    vector<vector<double>> elements;

    colNames.resize(V, vector<string>(V));
    elements.resize(V, vector<double>(V));

    // first constraint 
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            colNames[i][j] = x + lex(i) + lex(j);
            elements[i][j] = 1;
        }
        solver->addRow(colNames[i], elements[i], 1, 'E', "constraint");
    }

    vector<vector<string>> transposedColNames = Util::transposeStringMatrix(colNames, V, V);
    vector<vector<double>> transposedElements = Util::transposeDoubleMatrix(elements, V, V);

    // second constraint 
    for (int j = 0; j < V; j++) {
        solver->addRow(transposedColNames[j], transposedElements[j], 1, 'E', "constraint");
    }
}

void ModelAssignmentProblem::assignWarmStart(const Data* data) {
   
}
