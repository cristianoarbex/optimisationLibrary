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

#ifndef MODELGAP_H
#define MODELGAP_H

#include "Model.h"
#include "Solution.h"


class ModelGAP : public Model {

    private:

        string x;

        int V;
        int T;
        vector<vector<double> > sol_x;

        virtual void reserveSolutionSpace(const Data* data);
        virtual void readSolution();
        virtual void assignWarmStart();
        virtual void createModel(const Data* data);

        void printSolutionVariables(int digits = 5, int decimals = 2);

    public:

        ModelGAP();

        virtual ~ModelGAP();

        virtual void execute(const Data* data);
};

#endif
