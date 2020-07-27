#ifndef MODELGAP_H
#define MODELGAP_H

#include "Model.h"
#include "Solution.h"


class ModelGAP : public Model {

    private:

        string x;

        int V;
        int T;
        vector<vector<double> > sol_x;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution();
        virtual void assignWarmStart();
        virtual void createModel(const Data* data);

        void printSolutionVariables(int digits = 5, int decimals = 2);

    public:

        ModelGAP();

        virtual ~ModelGAP();

        virtual void execute(const Data* data);
};

#endif
