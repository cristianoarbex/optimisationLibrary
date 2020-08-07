/*
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
 */


#include "Solution.h"
#include "Options.h"

Solution::Solution() {
    
    resetSolution();
    debug = Options::getInstance()->getIntOption("debug");
    
}

Solution::~Solution() {
}

void Solution::resetSolution() {
    solutionExists = false;
    isOptimal      = false;
    isInfeasible   = false;
    isUnbounded    = false;

    value          = 0;
    bestBound      = 0;

}

void Solution::setSolutionStatus(bool exists, bool optimal, bool infeasible, bool unbounded) {
    solutionExists = exists;
    isOptimal      = optimal;
    isInfeasible   = infeasible;
    isUnbounded    = unbounded;
}


void Solution::print(int overrideDebug) {
        
    int ddebug = overrideDebug == -1 ? debug : overrideDebug;
    if (!debug) return;

    printf("\n------\nSolution:\n\n");
    if (!solutionExists) {
         if (isInfeasible)     printf("Model is infeasible\n");
         else if (isUnbounded) printf("Model is unbounded\n");
         else                  printf("Solution does not exist\n");
    } else {
        
        printf("Solution %s (gap: %.2f%%)\n", isOptimal ? "is optimal" : "is not optimal", getGap()*100);
        printf("Obj   = %.5f\n", value);
        if (ddebug > 1) printf("Bound = %.5f\n", bestBound);
    }
    printf("-----\n");
 
}


