/**
 * Model.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "Model.h"
#include "CPLEX.h"
#include "Options.h"

/**
 * INITIAL METHODS
 *
 */

Model::Model() {
    string solverUsed = Options::getInstance()->getStringOption("solver");
    
    if (solverUsed.compare("cplex") == 0) {
        solver = new CPLEX();
    } else {
        solver = new Solver();
    }
    solution = new Solution();

    isMax = 1;

    numExportedSolverModels = 0;
    maxExportedSolverModels = 0;


    totalTime           = 0;
    solvingTime         = 0;
    callbackTime        = 0;

    callbackDataTime    = 0;
    callbackCutsTime    = 0;


    maxFlowTime         = 0;
    maxFlowsSolved      = 0;
    bfsTime             = 0;
    
    callbackCalls       = 0;
    maxFlowCalls        = 0;
    cutsAdded           = 0;

    bestSolutionTime  = 0;
    bestSolutionNodes = 0;
    bestSolutionSoFar = -10000000;   

    firstNodeTime     = 0;
    firstNodeBound    = 0;
    firstNodeSolved   = false;

    totalNodes        = 0;

    goodEnoughSolution = 0;
    
    counter = 0;
    debug = Options::getInstance()->getIntOption("debug");
    timeLimit = (double)Options::getInstance()->getIntOption("time_limit");

    captureCuts = 0;
}


Model::~Model() {
    delete(solver);
    delete(solution);
}

void Model::overrideDebug(int d) {
    debug = d;
}

void Model::solve(const Data* data) {

    solverStartTime = Util::getWallTime();
    //solver->relax();
    solver->solve();
    solvingTime = Util::getWallTime() - solverStartTime;

    if (debug > 1) printf("\n---------\n");
    if (debug > 1) printf("Model solved in %.2fs, status = %d\n", solvingTime, solver->getStatus());

    readSolution(data);

}  

void Model::setTimeLimit(double time) {
    timeLimit = time;
}
    
void Model::setCaptureCuts(int c) {
    captureCuts = c;
}

void Model::setSolverParameters(int isMaximisation, string modelFilename, string solverModelFile) {

    isMax = isMaximisation;
    solver->changeObjectiveSense(isMax);

    solverModelFilename = solverModelFile;        
    solver->debugInformation(debug);
    if (debug) solver->debugLevel(Options::getInstance()->getIntOption("solver_debug_level"));
    
    solver->enablePresolve(Options::getInstance()->getBoolOption("presolve"));
    solver->setMIPEmphasis(Options::getInstance()->getIntOption("mip_emphasis"));
    solver->setMIPStrategy(Options::getInstance()->getIntOption("mip_strategy"));
    solver->setSolverParallelism(Options::getInstance()->getIntOption("solver_threads"), Options::getInstance()->getIntOption("solver_parallelism"));
    solver->setNodeHeuristic(Options::getInstance()->getIntOption("node_heuristic"));
    solver->setSolverLocalBranching(Options::getInstance()->getBoolOption("solver_local_branching"));
    solver->setProbingLevel(Options::getInstance()->getIntOption("probing_level"));
    solver->setTimeLimit(timeLimit);
    
    int cuts      = Options::getInstance()->getIntOption("solver_cuts"   );
    int clique    = Options::getInstance()->getIntOption("clique_cuts"   );
    int cover     = Options::getInstance()->getIntOption("cover_cuts"    );
    int disj      = Options::getInstance()->getIntOption("disj_cuts"     );
    int landp     = Options::getInstance()->getIntOption("landp_cuts"    );
    int flowcover = Options::getInstance()->getIntOption("flowcover_cuts");
    int flowpath  = Options::getInstance()->getIntOption("flowpath_cuts" );
    int gomory    = Options::getInstance()->getIntOption("gomory_cuts"   );
    int gub       = Options::getInstance()->getIntOption("gub_cuts"      );
    int implbd    = Options::getInstance()->getIntOption("implbd_cuts"   );
    int mir       = Options::getInstance()->getIntOption("mir_cuts"      );
    int mcf       = Options::getInstance()->getIntOption("mcf_cuts"      );
    int zerohalf  = Options::getInstance()->getIntOption("zerohalf_cuts" );
    solver->setSolverCuts(cuts, clique, cover, disj, landp, flowcover, flowpath,
                          gomory, gub, implbd, mir, mcf, zerohalf);

    solver->setLPMethod(Options::getInstance()->getIntOption("lp_method"));
    solver->setFeasibilityPump(Options::getInstance()->getIntOption("feasibility_pump"));
    solver->setSolverRandomSeed(Options::getInstance()->getIntOption("solver_random_seed"));

    if (!captureCuts) {
        if (Options::getInstance()->getBoolOption("first_node_only")) solver->setNodeLimit(1);
        if ( Options::getInstance()->getBoolOption("export_model"))      solver->exportModel(modelFilename.c_str());
    
        maxExportedSolverModels = Options::getInstance()->getIntOption("export_cplex_cuts");
        if (maxExportedSolverModels) solver->addSolveCallback(this);
    } else {
        solver->setNodeLimit(1);
        modelFilename       = "temporaryModel1.lp";
        solverModelFilename = "temporaryModel2.lp";
        solver->exportModel(modelFilename.c_str());
        solver->addSolveCallback(this);
    }
}

int Model::shouldExportMoreSolverModels() {
    if (numExportedSolverModels < maxExportedSolverModels) return 1;
    return 0;
}

int Model::getCurrentSolverModel() {
    return numExportedSolverModels;
}
void Model::addExportedSolverModel() {
    numExportedSolverModels++;
}

int Model::isSolutionGoodEnough(double value) {
    if (goodEnoughSolution == 0) return 0;
    if ( isMax && value >= goodEnoughSolution - TOLERANCE) return 1;
    if (!isMax && value <= goodEnoughSolution + TOLERANCE) return 1;
    return 0;                    
}


void Model::bestSolutionValueCallbackFunction(double value) {
    if (bestSolutionSoFar == -10000000 || value > bestSolutionSoFar + TOLERANCE || value < bestSolutionSoFar - TOLERANCE) {
        bestSolutionSoFar = value;
        bestSolutionTime = Util::getWallTime() - solverStartTime;
    }
}

void Model::firstNodeBoundCallbackFunction(double bound) {
    if (firstNodeSolved) return;
    firstNodeTime = Util::getWallTime() - solverStartTime;
    firstNodeBound = bound;
    firstNodeSolved = true;
}

void Model::getExtraCuts(vector<SolverCut>& sc) {
    if (!captureCuts) Util::stop("This function can only be called if captureCuts = 1");
    sc.resize(0);

    string filename1 = "temporaryModel1.lp";
    string filename2 = "temporaryModel2.lp";
    
    vector<string> constraintsOriginal;
    
    // Reading original model
    std::ifstream file(filename1);
    if (file.is_open()) {
        string line;
        string delim = " ";
        int foundConstraints = 0;
        while (std::getline(file, line)) {
            vector<string> temp = Util::split(line, delim);

            if (temp.size() >= 1 && !Util::toLowerCase(temp[0]).compare("bounds")) foundConstraints = 0;
            if (foundConstraints && temp.size()) {
                if (temp[0].back() == ':') {
                    temp[0].pop_back();
                    constraintsOriginal.push_back(temp[0]);
                }
            }
            if (temp.size() >= 2 && !Util::toLowerCase(temp[0]).compare("subject") && !Util::toLowerCase(temp[1]).compare("to")) foundConstraints = 1;
        }
        file.close();
        remove(filename1.c_str());
    }

    // Reading augmented model
    std::ifstream file2(filename2);
    if (file2.is_open()) {
        string line;
        string delim = " ";
        int foundConstraints = 0;
        int foundBounds      = 0;
        int boundCounter     = 0;
        
        vector<string> newConstraint;
        string newConstraintName = "";
        
        while (std::getline(file2, line)) {
            vector<string> temp = Util::split(line, delim);
 
            if (foundBounds) {
                if (find(temp.begin(), temp.end(), "=") != temp.end() || find(temp.begin(), temp.end(), "==") != temp.end()) {
                    if (temp.size() == 3) {
                        if (!Util::isNumber(temp[2])) Util::stop("A bound is weird in getExtraCuts: %s\n", line.c_str());
                        SolverCut s;
                        s.setName("variableBound" + lex(boundCounter));
                        s.addCoef(solver->getColIndex(temp[0]), 1);
                        s.setSense('E');
                        s.setRHS(Util::stringToDouble(temp[2]));
                        sc.push_back(s);
                        boundCounter++;
                    } else {
                        Util::stop("A bound is weird in getExtraCuts: %s\n", line.c_str());
                    }
                }
            }

            if (temp.size() >= 1 && !Util::toLowerCase(temp[0]).compare("bounds")) {
                foundConstraints = 0;
                foundBounds = 1;
            }
            
            if (foundConstraints && temp.size()) {
                if (temp[0].back() == ':') {
                    
                    if (newConstraint.size()) sc.push_back(extractSolverCut(newConstraintName, newConstraint));

                    newConstraint.resize(0);
                    newConstraintName = temp[0];
                    newConstraintName.pop_back();
                    if (find(constraintsOriginal.begin(), constraintsOriginal.end(), newConstraintName) != constraintsOriginal.end()) 
                        newConstraintName = "";
                        
                    
                }
                if (!newConstraintName.empty()) {
                    for (int i = 0; i < (int) temp.size(); i++) {
                        if (i == 0 && temp[i].back() == ':') continue;
                        newConstraint.push_back(temp[i]);
                    }
                }
            }
            if (temp.size() >= 2 && !Util::toLowerCase(temp[0]).compare("subject") && !Util::toLowerCase(temp[1]).compare("to")) {
                if (newConstraint.size()) sc.push_back(extractSolverCut(newConstraintName, newConstraint));
                foundConstraints = 1;

            }
           
        }
        file2.close();
        remove(filename2.c_str());
    }
}

SolverCut Model::extractSolverCut(string name, vector<string> cons) {
    SolverCut sc;
    sc.setName(name); 

    double coef = 1;
    int foundRHS = 0;
    for (unsigned i = 0; i < cons.size(); i++) {
        if (Util::isEqual(cons[i], "-")) {
            coef = -coef;
        } else if (Util::isEqual(cons[i], "+")) {
            // Do nothing
        } else if (Util::isNumber(cons[i])) {
            double c = Util::stringToDouble(cons[i]);
            if (coef < 0) coef = -c;
            else          coef = c;
            foundRHS = 1;
        } else if (Util::isEqual(cons[i], "<=")) {
            sc.setSense('L');
        } else if (Util::isEqual(cons[i], ">=")) {
            sc.setSense('G');
        } else if (Util::isEqual(cons[i], "=") || Util::isEqual(cons[i], "==")) {
            sc.setSense('E');
        } else if (!cons[i].empty()) {
            sc.addCoef(solver->getColIndex(cons[i]), coef);
            coef = 1;
            foundRHS = 0;
        }
    }
    if (!foundRHS) Util::stop("When trying to read cuts from the solver model file, the RHS is missing.");
    sc.setRHS(coef);
    //sc.print(solver, 1);
    return sc;
}
