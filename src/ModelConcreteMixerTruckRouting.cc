
#include "ModelConcreteMixerTruckRouting.h"
#include "Options.h"
#include "DataConcreteMixerTruckRouting.h"

ModelConcreteMixerTruckRouting::ModelConcreteMixerTruckRouting() : Model(){
    V = 0;
    K = 0;
    x = "x";
    y = "y";
}

ModelConcreteMixerTruckRouting::~ModelConcreteMixerTruckRouting() {
}

void ModelConcreteMixerTruckRouting::execute(const Data* data) {

    float startTime = Util::getTime();

    bool retry;    
    int tryNumber = 0;

    if (debug > 1) solver->printSolverName();
    createModel(data);

    do {
        tryNumber++;
        reserveSolutionSpace(data);
        assignWarmStart(data);
        setSolverParameters(0);

        solver->addInfoCallback(this);

        solve(data);

        retry = checkIfThereIsAnySubtourInTheSolution();
    } while (retry);

    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
} 

void ModelConcreteMixerTruckRouting::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        vector<string> route;
        int indexRoute;
        printf("\nSolution: \n");
        for (int k = 0; k < K; k++) {
            route.resize(V);
            std::fill(route.begin(), route.end(), "");
            indexRoute = 0;
            printf("Concrete Mixer Truck %d \n", k);
            for (int j = 0; j < V; j++) {
                printf("\t Xi%d", j);
            }
            printf("\n");
            for (int i = 0; i < V; i++) {
                printf("X%dj", i);
                for (int j = 0; j < V; j++) {
                    if(i == j)
                        printf("\t 0");
                    else
                        printf("\t %.0f", sol_x[k][i][j]);

                    if(sol_x[k][i][j] == 1) {
                        route[indexRoute] = "(" + lex(i) + ", " + lex(j) + ") "; 
                        indexRoute++;
                    }

                }
                printf("\n");
            }
            printf("\n");
            printf("Route (Concrete Mixer Truck %d): ", k);
            for (int i = 0; i < V; i++) {
                printf("%s", route[i].c_str());
            }
            printf("\n");
        }
        printf("\n");
        for (int k = 0; k < K; k++) {
            printf("y%d: %.0f\n", k, sol_y[k]);
        }
    }

}

void ModelConcreteMixerTruckRouting::reserveSolutionSpace(const Data* data) {
    sol_x.resize(K,vector<vector<double>>(V, vector<double>(V)));
    sol_y.resize(K);
}

void ModelConcreteMixerTruckRouting::readSolution(const Data* data) {
    totalNodes = solver->getNodeCount();
    solution->resetSolution();
    solution->setSolutionStatus(solver->solutionExists(), solver->isOptimal(),  solver->isInfeasible(), solver->isUnbounded());
    if (!solver->solutionExists()) {
        if (debug) printf("Solution does not exist\n");        
    } else {
        solution->setValue    (solver->getObjValue() );
        solution->setBestBound(solver->getBestBound());

        for (int k = 0; k < K; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (i == j)
                        sol_x[k][i][j] = 0;
                    else
                        sol_x[k][i][j] = solver->getColValue(x + lex(k) + UND + lex(i) + UND + lex(j));
                }
            }
        }

        for (int k = 0; k < K; k++) {
            sol_y[k] = solver->getColValue(y + lex(k));
        }
    }
}


void ModelConcreteMixerTruckRouting::createModel(const Data* data) {
    
    const DataConcreteMixerTruckRouting* dataCMR = dynamic_cast<const DataConcreteMixerTruckRouting*>(data);
    V = (dataCMR->getNumberOfConstructions()) + 1;
    K = dataCMR->getConcreteMixerTruckFleet();
    solver->changeObjectiveSense(0);

    // x variable
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j)
                    solver->addBinaryVariable(dataCMR->getDistance(i, j), x + lex(k) + UND + lex(i) + UND + lex(j));
            }
        }
    }

    // y variable
    for (int k = 0; k < K; k++)
        solver->addBinaryVariable(dataCMR->getFixedCost(), y + lex(k));


    vector<string> colNames;
    vector<double> elements;

    int indexAux;
    
    // at least one concrete mixer truck attends a client (1b and 1c)
    colNames.resize(K * V - K);
    elements.resize(K * V - K);
    for (int j = 1; j < V; j++) {
        indexAux = 0;
        for (int k = 0; k < K; k++) {
            for (int i = 0; i < V; i++) {
                if (j != i) {
                    colNames[indexAux] = x + lex(k) + UND + lex(i) + UND + lex(j);
                    elements[indexAux] = 1;
                    indexAux++;
                }
            }
        }
        solver->addRow(colNames, elements, 1, 'E', "constraint1b_" + lex(j));
    }

    colNames.resize(K * V - K);
    elements.resize(K * V - K);
    for (int i = 1; i < V; i++) {
        indexAux = 0;
        for (int k = 0; k < K; k++) {
            for (int j = 0; j < V; j++) {
                if (i != j) {
                    colNames[indexAux] = x + lex(k) + UND + lex(i) + UND + lex(j);
                    elements[indexAux] = 1;
                    indexAux++;
                }
            }
        }
        solver->addRow(colNames, elements, 1, 'E', "constraint1c_" + lex(i));
    }

    // relationship between x and y (1d)
    colNames.resize(V);
    elements.resize(V);
    for (int k = 0; k < K; k++) {
        indexAux = 0;

        for (int j = 1; j < V; j++) {
            colNames[indexAux] = x + lex(k) + UND + '0' + UND + lex(j);
            elements[indexAux] = 1;
            indexAux++;
        }

        colNames[indexAux] = y + lex(k);
        elements[indexAux] = -1;

        solver->addRow(colNames, elements, 0, 'L', "constraint1d_" + lex(k));
    }

    // truck sequence (truck queue) constraint (1e)
    colNames.resize(V + V - 2);
    elements.resize(V + V - 2);
    for (int k = 1; k < K; k++) {
        indexAux = 0;

        for (int j = 1; j < V; j++) {
            colNames[indexAux] = x + lex(k-1) + UND + '0' + UND + lex(j);
            elements[indexAux] = 1;
            indexAux++;
        }

        for (int j = 1; j < V; j++) {
            colNames[indexAux] = x + lex(k) + UND + '0' + UND + lex(j);
            elements[indexAux] = -1;
            indexAux++;
        }

        solver->addRow(colNames, elements, 0, 'G', "constraint1e_" + lex(k));
    }

    // enter and leave constraint (1f)
    colNames.resize((V - 1) + (V - 1));
    elements.resize((V - 1) + (V - 1));
    for (int k = 0; k < K; k++) {
        for (int h = 0; h < V; h++) {
            indexAux = 0;

            for (int i = 0; i < V; i++) {
                if (h != i) {
                    colNames[indexAux] = x + lex(k) + UND + lex(i) + UND + lex(h);
                    elements[indexAux] = 1;
                    indexAux++;
                }
            }

            for (int j = 0; j < V; j++) {
                if (h != j) {
                    colNames[indexAux] = x + lex(k) + UND + lex(h) + UND + lex(j);
                    elements[indexAux] = -1;
                    indexAux++;
                }
            }

            solver->addRow(colNames, elements, 0, 'E', "constraint1f_" + lex(k) + UND + lex(h));
        } 
    }

    // capacity constraint (1h)
    colNames.resize(V * V - V);
    elements.resize(V * V - V);
    for (int k = 0; k < K; k++) {
        indexAux = 0;

        for (int j = 0; j < V; j++) {
            for (int i = 0; i < V; i++) {
                if (i != j) {
                    colNames[indexAux] = x + lex(k) + UND + lex(i) + UND + lex(j);
                    elements[indexAux] = dataCMR->getDemand(j).quantity;
                    indexAux++;
                }
            }
        }

        solver->addRow(colNames, elements, dataCMR->getConcreteMixerTruckCapacity(), 'L', "constraint1h_" + lex(k));
    }

    // concrete type constraint (1k) 
    colNames.resize(1);
    elements.resize(1);
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j && dataCMR->getDemand(i).concreteTypeId != dataCMR->getDemand(j).concreteTypeId) {
                    colNames[0] = x + lex(k) + UND + lex(i) + UND + lex(j);
                    elements[0] = 1;
                    solver->addRow(colNames, elements, 0, 'E', "constraint1k_" + lex(k) + UND + lex(i) + UND + lex(j));
                }
            }
        }
    }
}

void ModelConcreteMixerTruckRouting::assignWarmStart(const Data* data) {
   
}

bool ModelConcreteMixerTruckRouting::checkIfThereIsAnySubtourInTheSolution() {
    
    bool isleavingTheDepot;
    bool isArrivingTheDepot;
    bool retry = false;

    if (solver->solutionExists() && !solver->isInfeasible() && !solver->isUnbounded()) {

        for (int k = 0; k < K; k++) {

            isleavingTheDepot = false;
            isArrivingTheDepot = false;

            for (int i = 1; i < V; i++) {
                if (sol_x[k][0][i] == 1)
                    isleavingTheDepot = true;

                if (sol_x[k][i][0] == 1)
                    isArrivingTheDepot = true;
            }

            if (!isleavingTheDepot || !isArrivingTheDepot) {
                vector<string> colNames;
                vector<double> elements;

                for (int i = 1; i < V; i++) {
                    for (int j = 1; j < V; j++) {
                        if (sol_x[k][i][j] == 1) {
                            colNames.push_back(x + lex(k) + UND + lex(i) + UND + lex(j));
                            elements.push_back(1);
                        }
                    }
                }

                if (colNames.size() > 1) {
                    solver->addRow(colNames, elements, colNames.size() - 1, 'L', "constraint1g_" + lex(k));
                    retry = true;
                }
            }
        }
    } 
    
    return retry;
}