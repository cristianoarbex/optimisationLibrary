/**
 * Solver.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "Util.h"

// Error checking
class SolverError {

    private:
        int code;

    public:
        SolverError(int code) : code(code) {}
        int getCode() const { return code; }
};



/**
 * Solver, superclass of cplex, gurobi, etc.
 */
class Solver {

    private:
       
        map<string, int> colIndices;


    protected:

        int status;
        vector<double> colSolution;

        // Map
        void addKey(string name, int index);
        
        // Called by the superclass, actually solves the problem
        virtual void doSolve(){}

    public:
        
        // Create and destroy
        Solver();
        virtual ~Solver();
        virtual void deleteAndRecreateProblem() {}
        virtual void readProblem(string filename) {}


        // Map
        int getColIndex(string name);
        string getColName (int index);
        double getColValue(string name);

        // Set data
        virtual void changeObjectiveSense(bool isMax){}
        virtual void addVariable(const double lower, const double upper, const double obj, string name){}
        virtual void addVariables(int numCols, const double lower, const double upper, const double* obj, string& name){}
        virtual void addBinaryVariable(const double obj, string name){}
        virtual void addBinaryVariables(int numCols, const double* obj, string& name){}
        virtual void addIntegerVariable(const double lower, const double upper, const double obj, string name){}
        virtual void addIntegerVariables(int numCols, double lb, double ub, const double* obj, string& name){}
        // SENSE
        // L - <=
        // E - ==
        // G - >=
        virtual void addRow(vector<string> colNames, vector<double> elements, double rhs, char sense, string name){}

        virtual void addLazyConstraint(vector<string> colNames, vector<double> elements, double rhs, char sense, string name){}
        virtual void addUserCut(vector<string> colNames, vector<double> elements, double rhs, char sense, string name){}
         
        virtual void setPriorityInBranching(vector<string> colNames, int priority){}
        virtual void setPriorityInBranching(vector<string> colNames, vector<int> priorities){}

        virtual void setVariablesWarmStart(vector<string> colNames, vector<double> values) {}
        virtual void setVariableWarmStart(string colName, double value) {}
        virtual void refineMIPStart() {}

        virtual void relax(){} 
        // Implemented in the superclass, class the subclass method
        void solve();

        // Get data
        virtual int getNumCols(){ return 0; }
        virtual int getNumRows(){ return 0; }
        virtual int getStatus(){ return 0; }
        virtual double getObjValue(){return 0;}
        virtual double getBestBound(){return 0;}
        virtual void getColSolution() {}
        
        virtual int getNodeCount() {return 0;}

        // Params
        virtual void setTimeLimit(double time) {}
        virtual void setNodeLimit(int lim) {}
        virtual void enablePresolve(bool enable = true) {}
        
        virtual void setLPMethod(int lp) {}
        virtual void setFeasibilityPump(int fp) {}
        virtual void setSolverRandomSeed(int fp) {}
        virtual void setLPTolerance(double tolerance) {}
        virtual void disableDefaultCuts(bool disable = true) {}
        virtual void setSolverCuts(int solverCuts = -2, int clique   = -2, int cover    = -2, int disj = -2, int landp  = -2, 
                                   int flowcover  = -2, int flowpath = -2, int gomory   = -2, int gub  = -2, int implbd = -2,
                                   int mir        = -2, int mcf      = -2, int zerohalf = -2) {}
        
        // 0 - balanced, 1 - feasibility, 2 - optimality
        virtual void setMIPEmphasis(int t) {}
        virtual void setMIPStrategy(int t) {}
        virtual void setSolverParallelism(int t, int m) {}
        virtual void setSolverLocalBranching(int t) {}
        virtual void setBranchingPolicy(int t) {}
        virtual void setNodeHeuristic(int t) {}
        virtual void setProbingLevel(int t) {}
        
        // Debug
        virtual void printSolverName();
        virtual void debugInformation(int debug){}
        virtual void debugLevel(int debugLevel){}
        virtual void exportModel(const char* filename){}

        // Status
        virtual bool solutionExists() {return false;}

        virtual bool isOptimal() {return false;}
        virtual bool isIntegerOptimal() {return false;}
        virtual bool isInfeasible() {return false;}
        virtual bool isInfeasibleDueToScaling() {return false;}
        virtual bool isUnbounded() {return false;}
        virtual bool isInfeasibleOrUnbounded() {return false;}
        virtual bool isSolutionLimit() {return false;} 
        virtual bool isTimeLimit() {return false;}
        virtual bool isMIPTimeLimitFeasible() {return false;}
        virtual bool isMIPTimeLimitInfeasible() {return false;}
        virtual bool isObjectiveLimitReached() {return false;}
        virtual bool isIterationLimitReached() {return false;}
        virtual bool isBestNumerical() {return false;}
        virtual bool isNumericalDifficulties() {return false;} 


        // Callbacks
        virtual void addLazyCallback     (void* userData) {}
        virtual void addUserCutCallback  (void* userData) {}
        virtual void addIncumbentCallback(void* userData) {}
        virtual void addNodeCallback     (void* userData) {}
        virtual void addSolveCallback    (void* userData) {}
        virtual void addInfoCallback     (void* userData) {}


};    

class SolverCut {
    
    private: 
        
        string name;
        vector<int> indices;
        vector<double> coefs;
        
        double rhs;
        
        // L - <=
        // E - ==
        // G - >=
        char sense;


    public:
    
        SolverCut() {
            sense = 0;
            rhs = 0;
        }

        ~SolverCut() {

        }

        int hasSameVariables(SolverCut cut) {
            if (cut.getNumIndices() != indices.size()) return 0;

            for (unsigned i = 0; i < indices.size(); i++) 
                if (indices[i] != cut.getIndex(i)) return 0;

            return 1;
        }
       
        double evaluate(const vector<double> & vars) {
            // TODO error checking?
            double lhs = 0;
            for (unsigned i = 0; i < indices.size(); i++) lhs += vars[indices[i]] * coefs[i];
            return lhs - rhs;
        }

        void addCoef(int index, double coef) {
            indices.push_back(index);
            coefs.push_back(coef);
        }

        void setName(string n) {
            name = n;
        }

        void addCoefs(vector<int> &index, vector<double> &coef) {
            indices.insert(indices.end(), index.begin(), index.end());
            coefs.insert(coefs.end(), coef.begin(), coef.end());
        }

        void changeLastIndex(int index) {
            if (indices.size() > 0) indices[indices.size()-1] = index;
        }

        void setRHS(double v) {
            rhs = v;
        }
 
        void setSense(char s) {
            if (s != 'L' && s != 'G' && s != 'E')
                Util::stop("Error in setSense: Invalid char %c (valid values are 'L', 'E' and 'G').", s);
            sense = s;
        }

        

        void print(Solver *solver, int digits = 5) {
            if (!name.empty()) {
                printf("%s: ", name.c_str());
            }
            for (unsigned i = 0; i < coefs.size(); i++) {
                string variableName = solver->getColName(indices[i]);
                if (i > 0 && coefs[i] > 0) printf("+ ");
                if (coefs[i] < 0) printf("- ");
                printf("%.*f %s", digits, coefs[i] < 0 ? -coefs[i] : coefs[i], variableName.c_str());
                if (i < coefs.size()-1) printf(" ");
            }
            printf(" %s %.8f\n", sense == 'L' ? " <= " : sense == 'E' ? " == " : " >= ", rhs);
        }

       
        string          getName() { return name;                      }
        int         getNumCoefs() { return (int)coefs.size();         }
        double           getRHS() { return rhs;                       }
        char           getSense() { return sense;                     }
        vector<double> getCoefs() { return coefs;                     }
        vector<int>  getIndices() { return indices;                   }
        unsigned  getNumIndices() { return indices.size();            }
        int       getIndex(int i) { return indices[i];                }
        double     getCoef(int i) { return coefs[i];                  }
        double      getLastCoef() { return coefs[coefs.size()-1];     }
        int        getLastIndex() { return indices[indices.size()-1]; }


};

#endif 


