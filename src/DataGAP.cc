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

#include "DataGAP.h"
#include "Options.h"
#include <iostream>
#include <fstream>
#include <string>

DataGAP::DataGAP() : Data() {
    numVariables = 0;
    numTasks = 0;
}

DataGAP::~DataGAP() {
}


void DataGAP::readData() {
    
    if (debug) printf("Initialising data for the Generalised Assignment Problem\n\n");
    
    std::ifstream inputFile;
    
    // string file_path = Options::getInstance()->getInputFile();
    string file_path = Options::getInstance()->getStringOption("input");

    inputFile.open(file_path);
    if (inputFile.is_open()) {
      
        inputFile >> numVariables; 
        inputFile >> numTasks;
        
        agentBudget.resize(numVariables);
        profitMatrix.resize(numTasks);
        weightMatrix.resize(numTasks);
        for (int i = 0; i < numTasks; i++) {
            profitMatrix[i].resize(numVariables);
            weightMatrix[i].resize(numVariables);
        }
        
        for (int j = 0; j < numVariables; j++) {
            for (int i = 0; i < numTasks; i++) {
                inputFile >> profitMatrix[i][j];
            }
        }
        for (int j = 0; j < numVariables; j++) {
            for (int i = 0; i < numTasks; i++) {
                inputFile >> weightMatrix[i][j];   
            }
        }
        for (int j = 0; j < numVariables; j++) {
            inputFile >> agentBudget[j];
        }
    }
    else std::cout << "Unable to open file\n"; 
   
    inputFile.close();

}

void DataGAP::print() {
    if (debug) {
        printf("Num agents: %2d\n", numVariables);
        printf("Num tasks: %2d\n", numTasks);
    }
}


double DataGAP::getAgentBudget(int i) const {
    if (i >= numVariables) Util::throwInvalidArgument("Error: Out of range parameter i in getAgentBudget");
    return agentBudget[i];
}

double DataGAP::getProfitMatrix(int i, int j) const {
    if (i >= numTasks) {Util::throwInvalidArgument("Error: Out of range parameter i in getProfitMatrix");}
    else if (j >= numVariables) {Util::throwInvalidArgument("Error: Out of range parameter j in getProfitMatrix");}
    return profitMatrix[i][j];
}

double DataGAP::getWeightMatrix(int i, int j) const { 
    if (i >= numTasks) {Util::throwInvalidArgument("Error: Out of range parameter i in getWeightMatrix");}
    else if (j >= numVariables) {Util::throwInvalidArgument("Error: Out of range parameter j in getWeightMatrix");}
    return weightMatrix[i][j];
}






