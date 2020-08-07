/**
 * Model.cc
 *
 * Copyright(c) 2018
 *  Cristiano Arbex Valle
 *  Arthur Moreira
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * opw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#include "Model.h"
#include "CPLEX.h"
#include "GLPK.h"
#include "Options.h"


/**
 * INITIAL METHODS
 *
 */

Model::Model() {
    string solverUsed = Options::getInstance()->getStringOption("solver");
    
    if (solverUsed.compare("cplex") == 0) {
        solver = new CPLEX();
    } else if (solverUsed.compare("glpk") == 0) {
        solver = new GLPK();
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
    
    counter = 0;
    debug = Options::getInstance()->getIntOption("debug");
    timeLimit = (double)Options::getInstance()->getIntOption("time_limit");
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
    if (Options::getInstance()->getBoolOption("first_node_only")) solver->setNodeLimit(1);

    if ( Options::getInstance()->getBoolOption("export_model"))      solver->exportModel(modelFilename.c_str());
    
    maxExportedSolverModels = Options::getInstance()->getIntOption("export_cplex_cuts");
    if (maxExportedSolverModels) solver->addSolveCallback(this);



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

