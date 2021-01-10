/**
 * CPLEX.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef CPLEX_H
#define CPLEX_H

#include <ilcplex/ilocplex.h>
#include <ilcplex/cplex.h>
#include "Solver.h"


/**
 * CPLEX
 */
class CPLEX : public Solver {

    private:

        CPXENVptr env;
        CPXLPptr problem;

        static int CPXPUBLIC functionCallback(CPXCENVptr env, void* cbdata, int wherefrom, void* cbhandle, int* useraction_p);
        static int CPXPUBLIC incumbentCallback(CPXCENVptr env, void* cbdata, int wherefrom, void* cbhandle, double objval, 
                                               double *x, int *isfeas_p, int* useraction_p);
        static int CPXPUBLIC nodeCallback(CPXCENVptr env, void* cbdata, int wherefrom, void* cbhandle, int* nodeindex_p, int* useraction_p);
        static int CPXPUBLIC infoCallback(CPXCENVptr env, void* cbdata, int wherefrom, void* cbhandle);
        static int CPXPUBLIC solveCallback(CPXCENVptr env, void* cbdata, int wherefrom, void* cbhandle, int* useraction_p);



    public:
        
        // Create and destroy
        CPLEX();
        virtual ~CPLEX();
        virtual void deleteAndRecreateProblem();
        virtual void readProblem(string filename);
        

        // Set data
        virtual void changeObjectiveSense(bool isMax);
        virtual void addVariable(const double lower, const double upper, const double obj, string name);
        virtual void addVariables(int numCols, const double lower, const double upper, const double* obj, string& name);
        virtual void addBinaryVariable(const double obj, string name);
        virtual void addBinaryVariables(int numCols, const double* obj, string& name);
        virtual void addIntegerVariable(const double lower, const double upper, const double obj, string name);
        virtual void addIntegerVariables(int numCols, double lb, double ub, const double* obj, string& name);
        // SENSE
        // L - <=
        // E - ==
        // G - >=
        virtual void addRow(vector<string> colNames, vector<double> elements, double rhs, char sense, string name);

        virtual void addLazyConstraint(vector<string> colNames, vector<double> elements, double rhs, char sense, string name);
        virtual void addUserCut(vector<string> colNames, vector<double> elements, double rhs, char sense, string name);

        virtual void setPriorityInBranching(vector<string> colNames, int priority);
        virtual void setPriorityInBranching(vector<string> colNames, vector<int> priorities);

        virtual void setVariablesWarmStart(vector<string> colNames, vector<double> values);
        virtual void setVariableWarmStart(string colName, double value);
        virtual void refineMIPStart();

        virtual void relax();
        virtual void doSolve();
        
        // Get data
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
        virtual void disableDefaultCuts(bool disable = true);
        virtual void setSolverCuts(int solverCuts =  0, int clique   = -2, int cover    = -2, int disj = -2, int landp  = -2, 
                                   int flowcover  = -2, int flowpath = -2, int gomory   = -2, int gub  = -2, int implbd = -2,
                                   int mir        = -2, int mcf      = -2, int zerohalf = -2);
 
        
        // 0 - balanced, 1 - feasibility, 2 - optimality
        virtual void setMIPEmphasis(int t);
        virtual void setMIPStrategy(int t);
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
        virtual void addLazyCallback     (void* userData);
        virtual void addUserCutCallback  (void* userData);
        virtual void addIncumbentCallback(void* userData);
        virtual void addNodeCallback     (void* userData);
        virtual void addSolveCallback    (void* userData);
        virtual void addInfoCallback     (void* userData);
        
};    

#endif 


