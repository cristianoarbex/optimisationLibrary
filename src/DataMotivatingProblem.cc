
#include "DataMotivatingProblem.h"
#include "Options.h"


DataMotivatingProblem::DataMotivatingProblem() : Data(){
    numVariables  = 0;
    firstConstraintMaxValue = 0;
    secondConstraintMaxValue = 0;
    thirdConstraintMaxValue = 0;
}

DataMotivatingProblem::~DataMotivatingProblem() {
}

void DataMotivatingProblem::readData() {
    if (debug) printf("Initialising data for motivating problem problem\n\n");

    numVariables                = 2;
    objectiveCoefficients       .resize(numVariables);
    firstConstraintCoefficients .resize(numVariables);
    secondConstraintCoefficients.resize(numVariables);
    thirdConstraintCoefficients .resize(numVariables);

    objectiveCoefficients       [0] = 1;
    objectiveCoefficients       [1] = 2;

    firstConstraintCoefficients [0] = 1;
    firstConstraintCoefficients [1] = 1;

    firstConstraintMaxValue         = 4;

    secondConstraintCoefficients[0] = 1;
    secondConstraintCoefficients[1] = 0;

    secondConstraintMaxValue        = 2;

    thirdConstraintCoefficients [0] = 0;
    thirdConstraintCoefficients [1] = 1;

    thirdConstraintMaxValue         = 3;
}

void DataMotivatingProblem::print() {
    if (debug) {
        printf("Num variables : %2d\n", numVariables);
        printf("Model: \n");

        // Objective function
        for (int i = 0; i < numVariables; i++) {
            if(i == 0){
                printf("max %2d x%d + ", objectiveCoefficients[i], i+1);
            } else if (i == numVariables - 1) {
                printf("%2d x%d \n", objectiveCoefficients[i], i+1);
            } else {
                printf("%2d x%d + ", objectiveCoefficients[i], i+1);
            }
        }

        // Constraints
        printf("s.t. \n");

        // First constraint
        for (int i = 0; i < numVariables; i++) {
            if (i == numVariables - 1) {
                printf("%2d x%d <= %2d \n", firstConstraintCoefficients[i], i+1, firstConstraintMaxValue);
            } else {
                printf("%2d x%d + ", firstConstraintCoefficients[i], i+1);
            }
        }

        // Second constraint
        for (int i = 0; i < numVariables; i++) {
            if (i == numVariables - 1) {
                printf("%2d x%d <= %2d \n", secondConstraintCoefficients[i], i+1, secondConstraintMaxValue);
            } else {
                printf("%2d x%d + ", secondConstraintCoefficients[i], i+1);
            }
        }

        // Third constraint
        for (int i = 0; i < numVariables; i++) {
            if (i == numVariables - 1) {
                printf("%2d x%d <= %2d \n", thirdConstraintCoefficients[i], i+1, thirdConstraintMaxValue);
            } else {
                printf("%2d x%d + ", thirdConstraintCoefficients[i], i+1);
            }
        }
    }

}

int DataMotivatingProblem::getFirstConstraintCoefficients(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getFirstConstraintCoefficients");
    return firstConstraintCoefficients[i];
}

int DataMotivatingProblem::getSecondConstraintCoefficients(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getSecondConstraintCoefficients");
    return secondConstraintCoefficients[i];
}

int DataMotivatingProblem::getThirdConstraintCoefficients(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getThirdConstraintCoefficients");
    return thirdConstraintCoefficients[i];
}

int DataMotivatingProblem::getObjectiveCoefficients(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getObjectiveCoefficients");
    return objectiveCoefficients[i];
}
