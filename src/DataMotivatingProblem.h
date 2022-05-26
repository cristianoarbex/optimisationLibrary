
#ifndef DATAMOTIVATINGPROBLEM_H
#define DATAMOTIVATINGPROBLEM_H

#include "Util.h"
#include "Data.h"

class DataMotivatingProblem : public Data {

    private:
        
        // max  x1 + 2x2
        // s.t. 
        //  x1 + x2 <= 4
        //  x1 <= 2
        //  x2 <= 3
        // x1 >= 0
        // x2 >= 0
        int numVariables;
        vector<int> objectiveCoefficients;
        vector<int> firstConstraintCoefficients;
        int firstConstraintMaxValue;
        vector<int> secondConstraintCoefficients;
        int secondConstraintMaxValue;
        vector<int> thirdConstraintCoefficients;
        int thirdConstraintMaxValue;


    public:

        DataMotivatingProblem();
        virtual ~DataMotivatingProblem();

        virtual void readData();
        virtual void print();

        int getNumVariables                 (     ) const {return numVariables ;}
        int getObjectiveCoefficients        (int i) const ;
        int getFirstConstraintMaxValue      (     ) const {return firstConstraintMaxValue ;}
        int getFirstConstraintCoefficients  (int i) const ;
        int getSecondConstraintMaxValue     (     ) const {return secondConstraintMaxValue ;}
        int getSecondConstraintCoefficients (int i) const ;
        int getThirdConstraintMaxValue      (     ) const {return thirdConstraintMaxValue ;}
        int getThirdConstraintCoefficients  (int i) const ;
};

#endif
