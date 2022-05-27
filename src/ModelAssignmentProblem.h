
#ifndef MODELASSIGNMENTPROBLEM_H
#define MODELASSIGNMENTPROBLEM_H

#include "Model.h"
#include "Solution.h"
#include "Util.h"

class ModelAssignmentProblem : public Model {

    private:
    
        // Variable names
        string x;
        
        // Solution values
        int V;
        vector<vector<int>> sol_x;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution        (const Data* data);
        virtual void assignWarmStart     (const Data* data);
        virtual void createModel         (const Data* data);
        
        void printSolutionVariables(int digits = 5, int decimals = 2);
        
    public:
        
        ModelAssignmentProblem();

        virtual ~ModelAssignmentProblem();

        virtual void execute(const Data *data);


};    

#endif 


