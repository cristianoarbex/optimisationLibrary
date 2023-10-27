
#ifndef MODELCONCRETEMIXERTRUCKROUTING_H
#define MODELCONCRETEMIXERTRUCKROUTING_H

#include "Model.h"
#include "Solution.h"

class ModelConcreteMixerTruckRouting : public Model {

    private:
    
        // Variable names
        string x;
        string y;
        string z;
        
        // Solution values
        int V;
        int K;
        vector<vector<vector<double>>> sol_x;
        vector<double> sol_y;
        vector<vector<double>> sol_z;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution        (const Data* data);
        virtual void assignWarmStart     (const Data* data);
        virtual void createModel         (const Data* data);
        
        void printSolutionVariables(int digits = 5, int decimals = 2);
        vector<SolverCut> separationAlgorithm(vector<double> sol);
        void connectivityCuts(const vector<double> &sol, vector<SolverCut> &cuts);
        int disconnectedComponents(const vector<vector<int>> &graph, const vector<vector<double>> &distance, vector<vector<int>> &components);
        int isConnected(const vector<vector<int>> &graph, const vector<vector<double>> &distance, vector<int> &notConnected);
        
    public:
        
        ModelConcreteMixerTruckRouting();

        virtual ~ModelConcreteMixerTruckRouting();

        virtual void execute(const Data *data);


};    

#endif 


