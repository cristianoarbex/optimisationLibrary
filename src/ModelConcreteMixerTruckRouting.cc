
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

void ModelConcreteMixerTruckRouting::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        vector<string> route;
        int indexRoute;
        printf("\nSolution: \n");
        for (int k = 0; k < K; k++) {
            route.resize(V);
            indexRoute = 0;
            printf("Concrete Mixer Truck %d \n", k);
            for (int j = 0; j < V; j++) {
                printf("\t Xi%d", j);
            }
            printf("\n");
            for (int i = 0; i < V; i++) {
                printf("X%dj", i);
                for (int j = 0; j < V; j++) {
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
                    sol_x[k][i][j] = solver->getColValue(x + lex(k) + lex(i) + lex(j));
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
                solver->addBinaryVariable(dataCMR->getDistance(i, j), x + lex(k) + lex(i) + lex(j));
            }
        }
    }

    // y variable
    for (int k = 0; k < K; k++)
        solver->addBinaryVariable(dataCMR->getFixedCost(), y + lex(k));


    vector<vector<vector<string>>> colNamesX;
    vector<vector<vector<double>>> elementsX;

    vector<string> colNamesY;
    vector<double> elementsY;

    vector<string> colNamesAux;
    vector<double> elementsAux;

    colNamesX   .resize(K,vector<vector<string>>(V, vector<string>(V)));
    elementsX   .resize(K,vector<vector<double>>(V, vector<double>(V)));
    colNamesY   .resize(K                                             );
    elementsY   .resize(K                                             );

    int indexAux;
    
    // constraint 1c
    colNamesAux.resize(V);
    elementsAux.resize(V);
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < V; i++) {
            indexAux = 0;

            for (int j = 0; j < V; j++) {
                colNamesX[k][i][j] = x + lex(k) + lex(i) + lex(j);
                elementsX[k][i][j] = 1;
                colNamesAux[indexAux] = colNamesX[k][i][j];
                elementsAux[indexAux] = elementsX[k][i][j];
                indexAux++;
            }
            solver->addRow(colNamesX[k][i], elementsX[k][i], 1, 'E', "constraint");
        }
    }

    // constraint 1b
    for (int k = 0; k < K; k++) {
        vector<vector<string>> transposedColNames = Util::transposeStringMatrix(colNamesX[k], V, V);
        vector<vector<double>> transposedElements = Util::transposeDoubleMatrix(elementsX[k], V, V);

        for (int j = 0; j < V; j++) {
            solver->addRow(transposedColNames[j], transposedElements[j], 1, 'E', "constraint");
        }
    }

    // constraint 1d - testar mais
    colNamesAux.resize(V + 1);
    elementsAux.resize(V + 1);
    for (int k = 0; k < K; k++) {
        indexAux = 0;

        for (int j = 0; j < V; j++) {
            colNamesX[k][0][j] = x + lex(k) + '0' + lex(j);
            elementsX[k][0][j] = 1;
            colNamesAux[indexAux] = colNamesX[k][0][j];
            elementsAux[indexAux] = elementsX[k][0][j];
            indexAux++;
        }

        colNamesY[k] = y + lex(k);
        elementsY[k] = -1;
        
        colNamesAux[indexAux] = colNamesY[k];
        elementsAux[indexAux] = elementsY[k];

        solver->addRow(colNamesAux, elementsAux, 0, 'L', "constraint");
    }

    // constraint ie - testar
    colNamesAux.resize(V + V);
    elementsAux.resize(V + V);
    for (int k = 1; k < K; k++) {
        indexAux = 0;

        for (int j = 0; j < V; j++) {
            colNamesX[k-1][0][j] = x + lex(k) + '0' + lex(j);
            elementsX[k-1][0][j] = 1;
            colNamesAux[indexAux] = colNamesX[k-1][0][j];
            elementsAux[indexAux] = elementsX[k-1][0][j];
            indexAux++;
        }

        for (int j = 0; j < V; j++) {
            colNamesX[k][0][j] = x + lex(k) + '0' + lex(j);
            elementsX[k][0][j] = -1;
            colNamesAux[indexAux] = colNamesX[k][0][j];
            elementsAux[indexAux] = elementsX[k][0][j];
            indexAux++;
        }

        solver->addRow(colNamesAux, elementsAux, 0, 'G', "constraint");
    }

    // constraint 1f - testar
    colNamesAux.resize((V - 1) + (V - 1));
    elementsAux.resize((V - 1) + (V - 1));
    for (int k = 0; k < K; k++) {
        for (int h = 0; h < V; h++) {
            indexAux = 0;

            for (int i = 0; i < V; i++) {
                if (h != i) {
                    colNamesX[k][i][h] = x + lex(k) + lex(i) + lex(h);
                    elementsX[k][i][h] = 1;
                    colNamesAux[indexAux] = colNamesX[k][i][h];
                    elementsAux[indexAux] = elementsX[k][i][h];
                    indexAux++;
                }
            }

            for (int j = 0; j < V; j++) {
                if (h != j) {
                    colNamesX[k][h][j] = x + lex(k) + lex(h) + lex(j);
                    elementsX[k][h][j] = -1;
                    colNamesAux[indexAux] = colNamesX[k][h][j];
                    elementsAux[indexAux] = elementsX[k][h][j];
                    indexAux++;
                }
            }

            solver->addRow(colNamesAux, elementsAux, 0, 'E', "constraint");
        } 
    }

    // constraint 1h - verificar
    colNamesAux.resize(V * V);
    elementsAux.resize(V * V);
    for (int k = 0; k < K; k++) {
        indexAux = 0;
        for (int j = 0; j < V; j++) {
            for (int i = 0; i < V; i++) {
                colNamesX[k][i][j] = x + lex(k) + lex(i) + lex(j);
                elementsX[k][i][j] = dataCMR->getDemand(j).quantity;
                // adicionar condição caso o cliente peça mais que cabe na betoneira
                colNamesAux[indexAux] = colNamesX[k][i][j];
                elementsAux[indexAux] = elementsX[k][i][j];
                indexAux++;
            }
        }
        solver->addRow(colNamesAux, elementsAux, dataCMR->getConcreteMixerTruckCapacity(), 'L', "constraint");
    }

    // constraint 1j and 1k
    colNamesAux.resize(1);
    elementsAux.resize(1);
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i == j || (i != j && dataCMR->getDemand(i).concreteTypeId != dataCMR->getDemand(j).concreteTypeId)) {
                    colNamesX[k][i][j] = x + lex(k) + lex(i) + lex(j);
                    elementsX[k][i][j] = 1;
                    colNamesAux[0] = colNamesX[k][i][j];
                    elementsAux[0] = elementsX[k][i][j];
                    solver->addRow(colNamesAux, elementsAux, 0, 'E', "constraint");
                }
            }
        }
    }
}

void ModelConcreteMixerTruckRouting::assignWarmStart(const Data* data) {
   
}