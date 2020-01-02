/**
 * main.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "Options.h"
#include "Execute.h"

void finalise() {
    Options::finalise();
}

int main(int argc, char *argv[]) {
 
    try {
        // Read and parse options
        Options::getInstance()->factory();
        Options::getInstance()->parseOptions(argc, argv);
        Options::getInstance()->print();
        
        Execute execute;
        execute.execute();
        
        
    } catch (std::invalid_argument& e) {
        printf("%s\n", e.what());
    }
    
    finalise();

    return 0;
}

