#ifndef DATAGAP_H
#define DATAGAP_H

#include "Util.h"
#include "Data.h"

class DataGAP : public Data {

    private:
        int numVariables;
        int numTasks;
        vector<vector<double> > profitMatrix;
        vector<vector<double> > weightMatrix;
        vector<double>          agentBudget ;
        
    public:

        DataGAP();
        virtual ~DataGAP();

        virtual void readData();
        virtual void print();

        int getNumVariables() const {return numVariables;}
        int getNumTasks() const {return numTasks;}
        double getAgentBudget(int i) const ;
        double getProfitMatrix(int i, int j) const ;
        double getWeightMatrix(int i, int j) const ;
};

#endif
