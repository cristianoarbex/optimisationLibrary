/*
 * GLPK.cc
 *
 * Copyright 2020 Arthur Moreira
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
 * */


#pragma once

#include <glpk.h>
#include "Solver.h"



class GLPK : public Solver {

    private:
        //int env;
        glp_prob *problem;
        glp_iocp parm;

    public:
        GLPK();
        virtual ~GLPK();
        virtual void deleteAndRecreateProblem();

        //set data
        virtual void changeObjectiveSense(bool isMax);
        virtual void addVariable(const double lower, const double upper, const double obj, string name);
        virtual void addVariables(int numCols, const double lower, const double upper, const double* obj, string& name);
        virtual void addBinaryVariable(const double obj, string name);
        virtual void addBinaryVariables(int numCols, const double* obj, string& name);
        virtual void addIntegerVariable(const double lower, const double upper, const double obj, string name);
        virtual void addIntegerVariables(int numCols, double lb, double ub, const double* obj, string& name);
        //SENSE
        //L - <=
        //E - ==
        //G - >=
        virtual void addRow(vector<string> colNames, vector<double> elements, double rhs, char sense, string name);
        virtual void setPriorityInBranching(vector<string> colNames, int priority);
        virtual void setPriorityInBranching(vector<string> colNames, vector<int> priorities);
        
        virtual void setVariablesWarmStart(vector<string> colNames, vector<double> values);
        virtual void setVariableWarmStart(string colName, double value);
        virtual void refineMIPStart();

        virtual void relax();
        virtual void doSolve();

        //Get data
        virtual int getNumCols();
        virtual int getNumRows();
        virtual int getStatus();
        virtual double getObjValue();
        virtual double getBestBound();
        virtual void getColSolution();

        virtual int getNodeCount();

        // Params
        virtual void setTimeLimit(double time);
        virtual void setNodeLimit(int lim);
        virtual void enablePresolve(bool enable = true);

        virtual void setLPMethod(int lp);
        virtual void setLPTolerance(double tolerance);
        virtual void setMIPTolerances(double tolerance);
        virtual void setRandomSeed(int seed);
        virtual void setNumericalEmphasis(int value);
        virtual void disableDefaultCuts(bool disable = true);
        virtual void setSolverCuts(int solverCuts =  0, int clique   = -2, int cover    = -2, int disj = -2, int landp  = -2,
                                   int flowcover  = -2, int flowpath = -2, int gomory   = -2, int gub  = -2, int implbd = -2,
                                   int mir        = -2, int mcf      = -2, int zerohalf = -2);


        // 0 - balanced, 1 - feasibility, 2 - optimality
        virtual void setMIPEmphasis(int t);
        virtual void setSolverParallelism(int t, int m);
        virtual void setSolverLocalBranching(int t);
        virtual void setBranchingPolicy(int t);
        virtual void setNodeHeuristic(int t);
        virtual void setProbingLevel(int t);


        // Debug
        virtual void printSolverName();
        virtual void debugInformation(int debug);
        virtual void debugLevel(int debugLevel);
        virtual void exportModel(const char* filename);

        // Status
        virtual bool solutionExists();

        virtual bool isOptimal               ();
        virtual bool isIntegerOptimal        ();
        virtual bool isInfeasible            ();
        virtual bool isInfeasibleDueToScaling();
        virtual bool isUnbounded             ();
        virtual bool isInfeasibleOrUnbounded ();
        virtual bool isSolutionLimit         ();
        virtual bool isTimeLimit             ();
        virtual bool isMIPTimeLimitFeasible  ();
        virtual bool isMIPTimeLimitInfeasible();
        virtual bool isObjectiveLimitReached ();
        virtual bool isIterationLimitReached ();
        virtual bool isBestNumerical         ();
        virtual bool isNumericalDifficulties ();

        // Callbacks
        /*
        virtual void addLazyCallback     (void* userData);
        virtual void addUserCutCallback  (void* userData);
        virtual void addIncumbentCallback(void* userData);
        virtual void addNodeCallback     (void* userData);
        virtual void addSolveCallback    (void* userData);
        virtual void addInfoCallback     (void* userData);
        */
};
