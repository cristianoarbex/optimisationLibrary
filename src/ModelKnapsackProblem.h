
#ifndef MODELKNAPSACKPROBLEM_H
#define MODELKNAPSACKPROBLEM_H

#include "Model.h"
#include "Solution.h"

class ModelKnapsackProblem : public Model {

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
        
        ModelKnapsackProblem();

        virtual ~ModelKnapsackProblem();

        virtual void execute(const Data *data);


};    

#endif 


