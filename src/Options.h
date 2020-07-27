/**
 * Options.h
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

/*********************************************
 * List of options
 *
 * Format: --optionName=value
 * 
 * Example: ./opw --debug=1
 * ----------------------------------------------
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include "Util.h"
#include "Option.h"

/**
 * Parser of options
 */
class Options {

    private:

        /**
         * Instancia singleton desta classe.
         */
        static Options* instance;
        
        // input file, must be provided (no name for this option)
        string inputFile;

        vector<Option*> options;
        map<string, int> optionsMap;

        // Private methods
        void assignDefaultValues();

        void changeOptionValue(string optionName, string value);

        void specificChecks();

    public:
        
        // Singleton instance
        static Options* getInstance();
        
        // Create and destroy
        Options();
        ~Options();
        void factory();
        static void finalise();

        // parse options
        void parseOptions(int numOptions, char* pairs[]);
        
        // print debug information
        void print();
        void printHelp();
        string getAllOptionsAsText();
        string getOutputOptionsAsText();
        string getModifiedOptionsAsText();

        // input file
        string getInputFile()   { return inputFile; }

        // get option values
        bool                getBoolOption       (string name);
        int                 getIntOption        (string name);
        double              getDoubleOption     (string name);
        string              getStringOption     (string name);
        vector<int>         getArrayOption      (string name);
        vector<double>      getDoubleArrayOption(string name);
        vector<vector<int>> getMatrixOption     (string name);
};    

#endif 


