/**
 * DataCapitalBudgeting.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef DATACAPITALBUDGETING_H
#define DATACAPITALBUDGETING_H

#include "Util.h"
#include "Data.h"

class DataCapitalBudgeting : public Data {

    private:
        
        // CapitalBudgeting problem is capital budgeting
        // max  8x1 + 11x2 + 6x3 + 4x4
        // s.t. 5x1 +  7x2 + 4x3 + 3x4 <= 14
        // xj E {0, 1}, j = 1, ..., 4
        int numVariables;
        vector<int> futureValue;
        vector<int> initialInvestment;
        int maxInvestment;

    public:

        DataCapitalBudgeting();
        virtual ~DataCapitalBudgeting();

        virtual void readData();
        virtual void print();

        int getNumVariables     (     ) const {return numVariables ;}
        int getMaxInvestment    (     ) const {return maxInvestment;}
        int getInitialInvestment(int i) const ;
        int getFutureValue      (int i) const ;
};

#endif
