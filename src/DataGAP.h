/*
 * Copyright 2020 Arthur Moreira
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

#ifndef DATAGAP_H
#define DATAGAP_H

#include "Util.h"
#include "Data.h"

class DataGAP : public Data {

    private:
        int numVariables;
        int numTasks;
        vector<vector<double> > profitMatrix;
        vector<vector<double> > weightMatrix;
        vector<double>          agentBudget ;
        
    public:

        DataGAP();
        virtual ~DataGAP();

        virtual void readData();
        virtual void print();

        int getNumVariables() const {return numVariables;}
        int getNumTasks() const {return numTasks;}
        double getAgentBudget(int i) const ;
        double getProfitMatrix(int i, int j) const ;
        double getWeightMatrix(int i, int j) const ;
};

#endif
