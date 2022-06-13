
#ifndef MODELCONCRETEMIXERTRUCKROUTING_H
#define MODELCONCRETEMIXERTRUCKROUTING_H

#include "Model.h"
#include "Solution.h"

class ModelConcreteMixerTruckRouting : public Model {

    private:
    
        // Variable names
        string x;
        string y;
        
        // Solution values
        int V;
        int K;
        vector<vector<vector<double>>> sol_x;
        vector<double> sol_y;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution        (const Data* data);
        virtual void assignWarmStart     (const Data* data);
        virtual void createModel         (const Data* data);
        
        void printSolutionVariables(int digits = 5, int decimals = 2);
        bool checkIfThereIsAnySubtourInTheSolution();
        vector<SolverCut> separationAlgorithm(vector<double> sol);
        void traverse(int k, int i, vector<bool> visited);
        bool isConnected(int vehicleIndex);
        
    public:
        
        ModelConcreteMixerTruckRouting();

        virtual ~ModelConcreteMixerTruckRouting();

        virtual void execute(const Data *data);


};    

#endif 


