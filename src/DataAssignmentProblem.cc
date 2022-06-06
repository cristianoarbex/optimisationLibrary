
#include "DataAssignmentProblem.h"
#include "Options.h"


DataAssignmentProblem::DataAssignmentProblem() : Data(){
    numVariables  = 0;
}

DataAssignmentProblem::~DataAssignmentProblem() {
}

void DataAssignmentProblem::readData() {
    if (debug) printf("Initialising data for Assignment problem\n\n");

    numVariables    =  6;
    costs           .resize(numVariables, vector<double>(numVariables));

    costs           [0][0] = 108;
    costs           [0][1] = 312;
    costs           [0][2] = 144;
    costs           [0][3] = 270;
    costs           [0][4] = 160;
    costs           [0][5] = 300;

    costs           [1][0] = 108;
    costs           [1][1] = 208;
    costs           [1][2] = 144;
    costs           [1][3] = 360;
    costs           [1][4] = 180;
    costs           [1][5] = 270;

    costs           [2][0] = 108;
    costs           [2][1] = 234;
    costs           [2][2] = 180;
    costs           [2][3] = 240;
    costs           [2][4] = 180;
    costs           [2][5] = 300;

    costs           [3][0] = 144;
    costs           [3][1] = 286;
    costs           [3][2] = 180;
    costs           [3][3] = 330;
    costs           [3][4] = 240;
    costs           [3][5] = 300;

    costs           [4][0] = 132;
    costs           [4][1] = 286;
    costs           [4][2] = 144;
    costs           [4][3] = 330;
    costs           [4][4] = 180;
    costs           [4][5] = 270;

    costs           [5][0] = 120;
    costs           [5][1] = 312;
    costs           [5][2] = 144;
    costs           [5][3] = 270;
    costs           [5][4] = 220;
    costs           [5][5] = 300;
}

void DataAssignmentProblem::print() {
    if (debug) {
        printf("Num variables : %2d\n", numVariables);
        for (int i = 0; i < numVariables; i++) {
            printf("\t Xi%d", i);
        }
        printf("\n");
        for (int i = 0; i < numVariables; i++) {
            printf("X%dj", i);
            for (int j = 0; j < numVariables; j++) {
                printf("\t %.2f", costs[i][j]);
            }
            printf("\n");
        }
    }

}


double DataAssignmentProblem::getCost(int i, int j) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getCost");
    if (j >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter j in getCost");
    return costs[i][j];
}