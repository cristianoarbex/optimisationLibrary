/**
 * Model.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef MODEL_H
#define MODEL_H

#include "Solver.h"
#include "Data.h"
#include "Solution.h"

/**
 * Model, superclass of ssd, etc.
 */
class Model {

    protected:
        
       Solver* solver;
       Solution* solution;
      
       vector<string> warmStartNames;
       vector<double> warmStartValues;

       string solverModelFilename;

       double goodEnoughSolution;

       double timeLimit;
       int isMax;

       // Whether this model is only intended to capture cuts added by the solver
       // If this is set to 1 then only the first LP relaxation will be soved and the
       // cuts added by the solver will be read into the function getExtraCuts below
       int captureCuts;
       SolverCut extractSolverCut(string name, vector<string> cons);

       // General times
       double totalTime;
       double solvingTime;
       double callbackTime;
       double callbackDataTime;
       double callbackCutsTime;

       // Algorithms
       double maxFlowTime;
       double bfsTime;
        
       // Counters
       int maxFlowCalls;
       int maxFlowsSolved;
       int callbackCalls;
       int cutsAdded;

       // Inner optimisation data
       double bestSolutionTime;
       double firstNodeTime;
       double firstNodeBound;
       bool   firstNodeSolved;
       double bestSolutionSoFar;
 
       // Nodes
       int totalNodes;
       // TODO do bestSolutionNodes
       // Look for CPX_CALLBACK_INFO_NODE_COUNT in 
       int bestSolutionNodes;
       
       // Just so I can measure the bestSolutionTime by hand
       double solverStartTime;

       int debug;
       int counter;
       
       // Solve callback, export CPLEX cuts
       int maxExportedSolverModels;
       int numExportedSolverModels;

       void setSolverParameters(int isMaximisation, string modelFilename = "bc_model.lp", string solverModelFile = "cplexModel");
      
       virtual void reserveSolutionSpace(const Data* data) {}
       virtual void readSolution        (const Data* data) {}
       virtual void assignWarmStart     (const Data* data) {}
       virtual void createModel         (const Data* data) {}
       virtual void solve               (const Data* data);

    public:
        
        // Create and destroy
        Model();
        virtual ~Model();

        virtual void execute(const Data* data) {}

        Solution* getSolution()  { return solution;  }
        void printSolution()     { solution->print(); }


        virtual vector<SolverCut> separationAlgorithm(vector<double> sol) {
            vector<SolverCut> sc;
            return sc;
        }
        virtual void incumbentCallbackFunction(const double& objval, const double* sol) {}
        virtual void bestSolutionValueCallbackFunction(double value);
        virtual void firstNodeBoundCallbackFunction(double bound);
        virtual int  isSolutionGoodEnough(double value);

        string getSolverModelFilename () {return solverModelFilename;}

        Solver* getSolver           () {return solver;             }
        double getTotalTime         () {return totalTime;          }
        double getSolvingTime       () {return solvingTime;        }
 
        double getCallbackTime      () {return callbackTime;       }
        double getMaxFlowTime       () {return maxFlowTime;        }
        double getBfsTime           () {return bfsTime;            }
        
        double getCallbackDataTime  () {return callbackDataTime;   }
        double getCallbackCutsTime  () {return callbackCutsTime;   }
        
        int getMaxFlowCalls         () {return maxFlowCalls;       }
        int getMaxFlowsSolved       () {return maxFlowsSolved;     }
        int getCallbackCalls        () {return callbackCalls;      }
        int getCutsAdded            () {return cutsAdded;          }
 
        double getBestSolutionTime  () {return bestSolutionTime;   }
        double getFirstNodeTime     () {return firstNodeTime;      }
        double getFirstNodeBound    () {return firstNodeBound;     }

        int getTotalNodes           () {return totalNodes;         }
        int getBestSolutionNodes    () {return bestSolutionNodes;  }
       
        int getCounter              () {return counter++;          }

        int  shouldExportMoreSolverModels(); 
        void addExportedSolverModel(); 
        int  getCurrentSolverModel(); 

        void setTimeLimit(double time);

        void overrideDebug(int d);

        void setCaptureCuts(int c);
        int shouldCaptureCuts() {return captureCuts;};

        void getExtraCuts(vector<SolverCut>& sc);
};    

#endif 


