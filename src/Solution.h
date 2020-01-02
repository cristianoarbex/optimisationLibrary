/**
 * Solution.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "Util.h"
#include "Data.h"


class Solution {

    private:
        
        double value;
        double bestBound;
        
        bool solutionExists;
        bool isOptimal;
        bool isInfeasible;
        bool isUnbounded;

        int debug;

    public:
   

        Solution();
        ~Solution();
      
        void setSolutionStatus(bool exists, bool optimal, bool infeasible, bool unbounded);
        void resetSolution();
        void print(int overrideDebug = -1);

        
        void setValue(double v)      { value     = v;  }
        void setBestBound(double bb) { bestBound = bb; }
        
        double getGap() {
            if (value == 0 && bestBound == 0) return -1;
            double max = value;
            if (bestBound > max) max = bestBound;
            return fabs(value - bestBound) / (fabs(max) + 1e-10);
        }

        double getValue()          {return value;         }
        double getBestBound()      {return bestBound;     }
        bool   isFeasible()        {return !isInfeasible; } 
        bool   isSolutionOptimal() {return isOptimal;     } 
        bool   doesSolutionExist() {return solutionExists;} 


};    

#endif 
