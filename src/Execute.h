/**
 * Execute.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef Execute_H
#define Execute_H

#include "Data.h"
#include "Model.h"

class Execute {

    private:

        Data* data;

        Model* model;

        double totalTime;

    public:
   
        Execute();
        ~Execute();

        void execute();
};    

#endif 
