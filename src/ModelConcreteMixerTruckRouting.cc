
#include "ModelConcreteMixerTruckRouting.h"
#include "Options.h"
#include "DataConcreteMixerTruckRouting.h"

ModelConcreteMixerTruckRouting::ModelConcreteMixerTruckRouting() : Model(){
    V = 0;
    K = 0;
    x = "x";
    y = "y";
    z = "z";
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
    solver->addLazyCallback(this);

    solve(data);

    totalTime = Util::getTime() - startTime;
    printSolutionVariables();
} 

void ModelConcreteMixerTruckRouting::printSolutionVariables(int digits, int decimals) {
    if (debug) {
        if (solver->solutionExists() && !solver->isInfeasible() && !solver->isUnbounded()) {
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
                        if(i == j || round(sol_x[k][i][j]) == -0)
                            printf("\t 0");
                        else
                            printf("\t %.0f", round(sol_x[k][i][j]));

                        if(round(sol_x[k][i][j]) == 1) {
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
                printf("\n\n");
            }
            printf("\n");
            for (int k = 0; k < K; k++) {
                if (round(sol_y[k]) == -0)
                    printf("y%d: 0\n", k);
                else
                    printf("y%d: %.0f\n", k, round(sol_y[k]));
            }
            printf("\n");
            for (int k = 0; k < K; k++) {
                for (int j = 1; j < V; j++) {
                    printf("z%d%d: %f\n", k, j, sol_z[k][j]);
                }
            }
        }
    }

}

void ModelConcreteMixerTruckRouting::reserveSolutionSpace(const Data* data) {
    sol_x.resize(K,vector<vector<double>>(V, vector<double>(V)));
    sol_y.resize(K);
    sol_z.resize(K, vector<double>(V));
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

        for (int k = 0; k < K; k++) {
            for (int j = 1; j < V; j++) {
                sol_z[k][j] = solver->getColValue(z + lex(k) + UND  + lex(j));
            }
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

    // z variable
    for (int k = 0; k < K; k++) {
        for (int j = 1; j < V; j++) {
            solver->addVariable(0, 1, 1, z + lex(k) + UND + lex(j));
        }
    }

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
        solver->addRow(colNames, elements, 1, 'G', "constraint1b_" + lex(j));
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
        solver->addRow(colNames, elements, 1, 'G', "constraint1c_" + lex(i));
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
    colNames.resize(V - 1);
    elements.resize(V - 1);
    for (int k = 0; k < K; k++) {
        indexAux = 0;

        for (int j = 1; j < V; j++) {
            colNames[indexAux] = z + lex(k) + UND + lex(j);
            elements[indexAux] = dataCMR->getDemand(j).getQuantity(dataCMR->getDemand(j).constructionId);
            indexAux++;
        }

        solver->addRow(colNames, elements, dataCMR->getConcreteMixerTruckCapacity(), 'L', "constraint1h_" + lex(k));
    }

    // total percentage constraint (1i)
    colNames.resize(K);
    elements.resize(K);
    for (int j = 1; j < V; j++) {
        indexAux = 0;

        for (int k = 0; k < K; k++) {
            colNames[indexAux] = z + lex(k) + UND + lex(j);
            elements[indexAux] = 1;
            indexAux++;
        }

        solver->addRow(colNames, elements, 1, 'E', "constraint1i_" + lex(j));
    }

    // relationship between x and z (1j)
    colNames.resize(V);
    elements.resize(V);
    for (int k = 0; k < K; k++) {
        for (int j = 1; j < V; j++) {
            indexAux = 0;

            for (int i = 0; i < V; i++) {
                if (i != j) {
                    colNames[indexAux] = x + lex(k) + UND + lex(i) + UND + lex(j);
                    elements[indexAux] = 1;
                    indexAux++;
                }
            }

            colNames[indexAux] = z + lex(k) + UND + lex(j);
            elements[indexAux] = -1;

            solver->addRow(colNames, elements, 0, 'G', "constraint1j_" + lex(k) + UND + lex(j));
        }
    }

    // concrete type constraint (1l) 
    colNames.resize(1);
    elements.resize(1);
    for (int k = 0; k < K; k++) {
        for (int i = 1; i < V; i++) {
            for (int j = 1; j < V; j++) {
                if (i != j && dataCMR->getDemand(i).getConcreteTypeId(dataCMR->getDemand(i).constructionId) != dataCMR->getDemand(j).getConcreteTypeId(dataCMR->getDemand(j).constructionId)) {
                    colNames[0] = x + lex(k) + UND + lex(i) + UND + lex(j);
                    elements[0] = 1;
                    solver->addRow(colNames, elements, 0, 'E', "constraint1l_" + lex(k) + UND + lex(i) + UND + lex(j));
                }
            }
        }
    }
}

void ModelConcreteMixerTruckRouting::assignWarmStart(const Data* data) { }

// Cutting planes
vector<SolverCut> ModelConcreteMixerTruckRouting::separationAlgorithm(vector<double> sol) {
    vector<SolverCut> cuts;
    connectivityCuts(sol, cuts);
    return cuts;
}

void ModelConcreteMixerTruckRouting::connectivityCuts(const vector<double> &sol, vector<SolverCut> &cuts) {

    vector<int> newIndicesToOld; // mapeamento do grafo novo para o original (dados do grafo original)
    vector<int> oldIndicesToNew(V); // mapeamento do grafo original para o novo (dados do grafo novo)
    newIndicesToOld.reserve(V);

    vector<vector<double>> sol_x_red; // solucões de x avaliadas
    vector<vector<int> >   graph_red; // índices avaliados
    sol_x_red.reserve(V);
    graph_red.reserve(V);
    
    for (int k = 0; k < K; k++) {
        int addCuts = 0;
        
        //////////////////////////////////////////////////////////////////////////////
        // Creating subgraph containing only visited vertices and visited edges
        //
        // Reduce graph to contain only those vertices and edges with values on them
        // Map original indices to new
        // Map new indices to original
        // Create list of vertices in sol_y or something
        // Create graph (edges)
        // Create capacity graph (sol_x or something)
        double tempTime = Util::getWallTime();
        int currentIndex = 0;
        sol_x_red.clear();
        graph_red.clear();
        newIndicesToOld.clear();
        std::fill(oldIndicesToNew.begin(), oldIndicesToNew.end(), -1);

        // criação da estrutura do novo grafo
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (i != j) {
                    double x_temp = sol[solver->getColIndex(x + lex(k) + UND + lex(i) + UND + lex(j))];
                    if (round(x_temp) == 1) {
                        newIndicesToOld.push_back(i);
                        sol_x_red.push_back(vector<double>());
                        graph_red.push_back(vector<int>());
                        sol_x_red[currentIndex].reserve(V);
                        graph_red[currentIndex].reserve(V);
                        oldIndicesToNew[i] = currentIndex;
                        currentIndex++;
                    }
                }
            }
        }
        // preenchimento do novo grafo
        for (unsigned i = 0; i < sol_x_red.size(); i++) {
            int ii = newIndicesToOld[i];
            for (int j = 0; j < (int)newIndicesToOld.size(); j++) {
                int jj = newIndicesToOld[j];
                if (oldIndicesToNew[jj] != -1 && ii != jj) {
                    double x_temp = sol[solver->getColIndex(x + lex(k) + UND + lex(ii) + UND + lex(jj))];
                    if (round(x_temp) == 1) {
                        graph_red[i].push_back(oldIndicesToNew[jj]); 
                        sol_x_red[i].push_back(x_temp);
                    }
                }
            }
        }
        // END OF Creating subgraph containing only visited vertices and visited edges
        //////////////////////////////////////////////////////////////////////////////

        vector<vector<int>> verticesInCut(1);
        
        if (graph_red.size() == 0) {
            continue;
        }

        // Check if cut is connected
        tempTime = Util::getWallTime();

        if (!addCuts) {
            // verificação se o novo grafo possui o índice zero, ou seja, se passa pelo depósito
            if (std::find(std::begin(newIndicesToOld), std::end(newIndicesToOld), 0) == std::end(newIndicesToOld)) {
                addCuts = 1;
                for (int i = 0; i < (int)oldIndicesToNew.size(); i++) {
                    if (oldIndicesToNew[i] != -1)
                        verticesInCut[0].push_back(oldIndicesToNew[i]);
                }
            }
            // verificação se o novo grafo é conectado
            else {
                // retorna listas de vertices que não estão conectados ao primeiro grupo de vertices (encontra uma lista de vertices desconectados)
                addCuts = !isConnected(graph_red, sol_x_red, verticesInCut[0]);
                if (addCuts) {
                    vector<vector<int>> verticesInCut2;
                    // retorna listas de vertices que não foram visitados partindo do 0 (encontra tadas as listas de vertices desconectados)
                    addCuts = disconnectedComponents(graph_red, sol_x_red, verticesInCut2);
                    if (verticesInCut2.size() > 1) {
                        verticesInCut.resize(verticesInCut2.size()+1);
                        for (unsigned k = 1; k < verticesInCut.size(); k++) verticesInCut[k] = verticesInCut2[k-1];
                    }
                }
            }
        }

        if (addCuts) {
            // criação dos cutting planes
            for (int i = 0; i < (int)verticesInCut.size(); i++) {
                SolverCut cut;
                for (int j = 1; j < (int)verticesInCut[i].size(); j++) {
                    if (newIndicesToOld[verticesInCut[i][j - 1]] != newIndicesToOld[verticesInCut[i][j]]) {
                        // x_(j-1)_j
                        int jj = solver->getColIndex(x + lex(k) + UND + lex(newIndicesToOld[verticesInCut[i][j - 1]]) + UND + lex(newIndicesToOld[verticesInCut[i][j]]));
                        if (round(sol[jj]) == 1)
                            cut.addCoef(jj, 1);

                        // x_j_(j-1)
                        jj = solver->getColIndex(x + lex(k) + UND + lex(newIndicesToOld[verticesInCut[i][j]]) + UND + lex(newIndicesToOld[verticesInCut[i][j - 1]]));
                        if (round(sol[jj]) == 1)
                            cut.addCoef(jj, 1);
                    }
                }

                if (cut.getCoefs().size() > 0) {
                    cut.setName("cut1g_" + lex(k));
                    cut.setSense('L');
                    cut.setRHS(cut.getCoefs().size() - 1);
                    cuts.push_back(cut);
                }
            }
        }
        
        bfsTime += (Util::getWallTime() - tempTime);
    }
}

int ModelConcreteMixerTruckRouting::isConnected(const vector<vector<int>> &graph, const vector<vector<double>> &distance, vector<int> &notConnected) { 
    notConnected.resize(graph.size());
    std::fill(notConnected.begin(), notConnected.end(), 1);
    vector<int> visitQueue(1);
    visitQueue[0] = 0;
    notConnected[0] = 0;

    while (visitQueue.size() > 0) {
        int i = visitQueue[0];
        for (int j = 0; j < (int)graph[i].size(); j++) {
            int jj = graph[i][j];
            if (round(distance[i][j]) == 1) {
                 if (notConnected[jj] == 1) {
                    visitQueue.push_back(jj);
                    notConnected[jj] = 0;
                 }
            }
        }
        visitQueue.erase(visitQueue.begin());
    }

    int numDisconnected = 0;
    
    for (unsigned i = 0; i < notConnected.size(); i++) {
        if (notConnected[i] == 1) {
            notConnected[numDisconnected] = i;
            numDisconnected++;
        }
    }

    notConnected.resize(numDisconnected);
    return numDisconnected == 0;
}

int ModelConcreteMixerTruckRouting::disconnectedComponents(const vector<vector<int>> &graph, const vector<vector<double>> &distance, vector<vector<int>> &components) { 
    if (graph.size() == 0) return 0;        

    components.resize(1);
    vector<int> visited(graph.size());
    std::fill(visited.begin()+1, visited.end(), 0);

    int verticesLeft = (int) graph.size();
    int minIndexLeft = 0;
    int currentComponent = 0;

    while (minIndexLeft != -1) {
        components[currentComponent].reserve(verticesLeft);
        vector<int> visitQueue(1);

        visitQueue[0] = minIndexLeft;
        components[currentComponent].push_back(minIndexLeft);
        visited[minIndexLeft] = 1;
        verticesLeft--;
 
        while (visitQueue.size() > 0) {
            int i = visitQueue[0];
            for (int j = 0; j < (int)graph[i].size(); j++) {
                int jj = graph[i][j];
                if (visited[jj] == 0) {
                    visitQueue.push_back(jj);
                    components[currentComponent].push_back(jj);
                    visited[jj] = 1;
                    verticesLeft--;
                }
            }
            visitQueue.erase(visitQueue.begin());
        }
       
        int found = 0;
        for (unsigned i = minIndexLeft + 1; i < graph.size(); i++) {
            if (visited[i] == 0) {
                minIndexLeft = i;
                found = 1;
                break;
            }
        }
        if (!found) {
            minIndexLeft = -1;
        } else {
            currentComponent++;
            components.resize(components.size()+1);
        }

    }

    components.erase(components.begin());
    return components.size();
}
