/**
 * Execute.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "Execute.h"
#include "Options.h"
#include "DataCapitalBudgeting.h"
#include "ModelCapitalBudgeting.h"
#include "DataMotivatingProblem.h"
#include "ModelMotivatingProblem.h"
#include "DataKnapsackProblem.h"
#include "ModelKnapsackProblem.h"
#include "DataAssignmentProblem.h"
#include "ModelAssignmentProblem.h"

Execute::Execute() {
    totalTime = 0;
    model = NULL;
    data  = NULL;

}

Execute::~Execute() {
    delete(model);
    delete(data);
}

void Execute::execute() {
    float startTime = Util::getTime();
     
    if (Options::getInstance()->getStringOption("model").compare("toy") == 0) {
        data  = new DataCapitalBudgeting();
        model = new ModelCapitalBudgeting();
    } else if (Options::getInstance()->getStringOption("model").compare("motivating") == 0) {
        data  = new DataMotivatingProblem();
        model = new ModelMotivatingProblem();
    } else if (Options::getInstance()->getStringOption("model").compare("knapsackProblem") == 0) {
        data  = new DataKnapsackProblem();
        model = new ModelKnapsackProblem();
    } else if (Options::getInstance()->getStringOption("model").compare("assignmentProblem") == 0) {
        data  = new DataAssignmentProblem();
        model = new ModelAssignmentProblem();
    } else {
        data  = new Data();
        model = new Model();
    }
    
    data->readData();
    data->print();

    model->execute(data);
    model->printSolution();
     
    totalTime = Util::getTime() - startTime;
    
    /*
    if (Options::getInstance()->getIntOption("debug")) {
        printf("\n");
        printf("Solution value:           %8.2f\n",   model->getSolution().getValue());
        printf("Final lower bound:        %8.2f\n",   model->getSolution().getBestBound());
        printf("Gap:                      %8.2f%%\n", model->getSolution().getGap()*100);
        printf("Bound at first node:      %8.2f\n\n", model->getFirstNodeBound());
        printf("Number of nodes solved:   %8d\n",     model->getTotalNodes());
        if (model->getCallbackCalls() > 0) {
            printf("Callback time              %7.3fs (%d calls)\n", model->getCallbackTime(), model->getCallbackCalls());
            printf("   Adding cuts             %7.3fs (%d cuts added)\n", model->getCallbackCutsTime(), model->getCutsAdded());
            printf("   Data processing         %7.3fs\n", model->getCallbackDataTime());
            printf("   Max flow                %7.3fs (%d calls, %d solved)\n",model->getMaxFlowTime(),model->getMaxFlowCalls(),model->getMaxFlowsSolved());
            printf("   BFS                     %7.3fs\n", model->getBfsTime());
        }
        printf("Solver time:               %7.3fs\n",   model->getSolvingTime());
        printf("   First node solved in    %7.3fs\n",   model->getFirstNodeTime());
        printf("   Best solution time      %7.3fs\n",   model->getBestSolutionTime());
        printf("BC time:                   %7.3fs\n",   model->getTotalTime());
        printf("\nEverything finalised in:   %7.3fs\n", totalTime);
    }
    */
}
