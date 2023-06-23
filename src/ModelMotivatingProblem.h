
#ifndef MODELMOTIVATINGPROBLEM_H
#define MODELMOTIVATINGPROBLEM_H

#include "Model.h"
#include "Solution.h"

/**
 * Branch and cut with formulation for incomplete graph
 */
class ModelMotivatingProblem : public Model {

    private:
    
        // Variable names
        string x;
        
        // Solution values
        int V;
        vector<double> sol_x;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution        (const Data* data);
        virtual void assignWarmStart     (const Data* data);
        virtual void createModel         (const Data* data);
        
        void printSolutionVariables(int digits = 5, int decimals = 2);
        
    public:
        
        ModelMotivatingProblem();

        virtual ~ModelMotivatingProblem();

        virtual void execute(const Data *data);
};    

#endif 


