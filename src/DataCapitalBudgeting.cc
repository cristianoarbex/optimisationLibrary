/**
 * DataCapitalBudgeting.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "DataCapitalBudgeting.h"
#include "Options.h"


DataCapitalBudgeting::DataCapitalBudgeting() : Data(){
    numVariables  = 0;
    maxInvestment = 0;
}

DataCapitalBudgeting::~DataCapitalBudgeting() {
}

void DataCapitalBudgeting::readData() {
    if (debug) printf("Initialising data for capital budgeting problem\n\n");

    numVariables     =  4;
    maxInvestment    = 14;
    futureValue      .resize(numVariables);
    initialInvestment.resize(numVariables);

    futureValue      [0] =  8;
    futureValue      [1] = 11;
    futureValue      [2] =  6;
    futureValue      [3] =  3;

    initialInvestment[0] = 5;
    initialInvestment[1] = 7;
    initialInvestment[2] = 4;
    initialInvestment[3] = 3;

}

void DataCapitalBudgeting::print() {
    if (debug) {
        printf("Num variables : %2d\n", numVariables);
        printf("Max investment: %2d\n", maxInvestment);
        for (int i = 0; i < numVariables; i++) {
            printf(" Inv %2d: Cost %2d, Profit %2d\n", i, initialInvestment[i], futureValue[i]);
        }
    }

}


int DataCapitalBudgeting::getInitialInvestment(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getInitialInvestment");
    return initialInvestment[i];
}

int DataCapitalBudgeting::getFutureValue(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getFutureValue");
    return futureValue[i];
}
