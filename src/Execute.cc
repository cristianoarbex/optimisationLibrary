/**
 * Execute.cc
 *
 * Copyright(c) 2018
 *  Cristiano Arbex Valle
 *  Arthur Moreira
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * opw is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */


#include "Execute.h"
#include "Options.h"
#include "DataCapitalBudgeting.h"
#include "ModelCapitalBudgeting.h"
#include "DataGAP.h"
#include "ModelGAP.h"


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
     
    if (Options::getInstance()->getStringOption("model").compare("cbp") == 0) {
        data  = new DataCapitalBudgeting();
        model = new ModelCapitalBudgeting();
    } else if (Options::getInstance()->getStringOption("model").compare("gap") == 0) {
        data  = new DataGAP();
        model = new ModelGAP();
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
