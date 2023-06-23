
#include "DataKnapsackProblem.h"
#include "Options.h"


DataKnapsackProblem::DataKnapsackProblem() : Data(){
    numVariables  = 0;
    capacity = 0;
}

DataKnapsackProblem::~DataKnapsackProblem() {
}

void DataKnapsackProblem::readData() {
    if (debug) printf("Initialising data for knapsack problem\n\n");

    numVariables     = 10;
    capacity         = 10;
    returnValues    .resize(numVariables);
    costs           .resize(numVariables);

    returnValues    [0] =  132;
    returnValues    [1] =  94;
    returnValues    [2] =  110;
    returnValues    [3] =  190;
    returnValues    [4] =  120;
    returnValues    [5] =  175;
    returnValues    [6] =  90;
    returnValues    [7] =  80;
    returnValues    [8] =  115;
    returnValues    [9] =  160;

    costs           [0] =  2.6;
    costs           [1] =  1.8;
    costs           [2] =  2;
    costs           [3] =  3.5;
    costs           [4] =  2.3;
    costs           [5] =  3;
    costs           [6] =  1.6;
    costs           [7] =  1.4;
    costs           [8] =  2.2;
    costs           [9] =  2.7;
}

void DataKnapsackProblem::print() {
    if (debug) {
        printf("Num variables : %2d\n", numVariables);
        printf("Capacity: %f\n", capacity);
        for (int i = 0; i < numVariables; i++) {
            printf("Item %2d: Cost %f, Return value %f\n", i, costs[i], returnValues[i]);
        }
    }
}

double DataKnapsackProblem::getReturnValue(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getReturnValue");
    return returnValues[i];
}

double DataKnapsackProblem::getCost(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getCost");
    return costs[i];
}
