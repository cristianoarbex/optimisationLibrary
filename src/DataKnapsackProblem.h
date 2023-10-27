
#ifndef DATAKNAPSACKPROBLEM_H
#define DATAKNAPSACKPROBLEM_H

#include "Util.h"
#include "Data.h"

class DataKnapsackProblem : public Data {

    private:
        
        // Knapsack problem
        // max  SUM(pj * xj)
        // s.t. SUM(aj * xj) <= b
        // xj E {0, 1}, j = 1, ..., n
        int numVariables;
        vector<double> returnValues;
        vector<double> costs;
        double capacity;

    public:

        DataKnapsackProblem();
        virtual ~DataKnapsackProblem();

        virtual void readData();
        virtual void print();

        int getNumVariables    (     ) const {return numVariables ;}
        double getCapacity     (     ) const {return capacity ;}
        double getReturnValue  (int i) const ;
        double getCost         (int i) const ;
};

#endif
