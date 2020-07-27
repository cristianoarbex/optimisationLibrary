#include "DataGAP.h"
#include "Options.h"
#include <iostream>
#include <fstream>

DataGAP::DataGAP() : Data() {
    numVariables = 0;
    numTasks = 0;
}

DataGAP::~DataGAP() {
}


void DataGAP::readData() {
    if (debug) printf("Initialising data for the Generalised Assignment Problem\n\n");

    
    // reading from file
    // info http://people.brunel.ac.uk/~mastjjb/jeb/orlib/gapinfo.html
    /* The format for each of these data files is:
  
     number of agents (m), number of jobs (n)
     for each agent i (i=1,...,m) in turn:
         cost of allocating job j to agent i (j=1,...,n)
     for each agent i (i=1,...,m) in turn:
         resource consumed in allocating job j to agent i (j=1,...,n)
     resource capacity of agent i (i=1,...,m)   
    */ 
    
    std::ifstream infile;
    infile.open("../src/GAPinstances.txt");
    if (infile.is_open()) {
      
        infile >> numVariables; 
        infile >> numTasks;
        
        agentBudget.resize(numVariables);
        profitMatrix.resize(numTasks);
        weightMatrix.resize(numTasks);
        for (int i = 0; i < numTasks; i++) {
            profitMatrix[i].resize(numVariables);
            weightMatrix[i].resize(numVariables);
        }
        
        for (int j = 0; j < numVariables; j++) {
            for (int i = 0; i < numTasks; i++) {
                infile >> profitMatrix[i][j];
            }
        }
        for (int j = 0; j < numVariables; j++) {
            for (int i = 0; i < numTasks; i++) {
                infile >> weightMatrix[i][j];   
            }
        }
        for (int j = 0; j < numVariables; j++) {
            infile >> agentBudget[j];
        }
    }
    else std::cout << "Unable to open file\n"; 
   
    infile.close();

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






