
#ifndef DATAASSIGNMENTPROBLEM_H
#define DATAASSIGNMENTPROBLEM_H

#include "Util.h"
#include "Data.h"

class DataAssignmentProblem : public Data {

    private:
        
        // Assignment problem
        // min SUM(i)(SUM(j)(Cij * Xij))
        // s.t. 
        // SUM(j)(Xij) = 1
        // SUM(i)(Xij) = 1
        // Xij E {0, 1}, i = 1, ..., n, j = 1, ..., n
        int numVariables;
        vector<vector<double>> costs;

    public:

        DataAssignmentProblem();
        virtual ~DataAssignmentProblem();

        virtual void readData();
        virtual void print();

        int getNumVariables     (            ) const {return numVariables ;}
        double getCost          (int i, int j) const ;
};

#endif
