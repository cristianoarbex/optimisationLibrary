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


