/**
 * Options.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "Options.h"

/**
 * INITIAL METHODS
 *
 */

Options* Options::instance = new Options();

Options* Options::getInstance () {
	return instance;
}

void Options::factory() {
	delete instance;
	instance = new Options();
}

Options::Options() {
    assignDefaultValues();
}

Options::~Options() {
    for (int i = 0; i < (int)options.size(); i++) {
        delete(options[i]);
    }
}

void Options::finalise() {
    delete(instance);
}


/////////////////////////
/////////////////////////
/////////////////////////
/////////////////////////
// PRIVATE METHODS //////
/////////////////////////

void Options::assignDefaultValues() {



    vector<string> solverValues;
    solverValues.push_back("cplex");
    
    vector<string> modelValues;
    modelValues.push_back("toy");
    modelValues.push_back("motivating");
    modelValues.push_back("knapsackProblem");
    modelValues.push_back("assignmentProblem");
    modelValues.push_back("concreteMixerTruckRouting");
    vector<string> empty;
   
    //double dmax = std::numeric_limits<double>::max();
    double imax = std::numeric_limits<int>::max();

    options.push_back(new StringOption("settings_file", "Input file with options. If not empty, only some other options such as 'output' or 'debug' are allowed.", 1, "", empty));
    options.push_back(new StringOption("output",        "Output file where solution will be written", 1, "", empty));

    // Debug options
    options.push_back(new IntOption ("debug",             "Level of debug information [0-4, 0 means no debug]", 1, 2, 4, 0));
    options.push_back(new BoolOption("first_node_only",   "Solve only first node", 1, 0));
    options.push_back(new StringOption("lp_filename",       "Name of the LP exported file if export_model = 1", 1, "bc_model.lp", empty));
    options.push_back(new BoolOption("export_model",      "If (1) exports model to lp file", 1, 0));
    options.push_back(new IntOption ("export_cplex_cuts", "Number of intermediate models with cplex cuts to export to lp file", 1, 0, imax, 0));

    // File options
    options.push_back(new StringOption("input",  "Input file", 1, "", empty));
    options.push_back(new StringOption("output", "Output file where solution will be written", 1, "", empty));
    
    options.push_back(new StringOption("model",  "Which model to solve", 1, "toy", modelValues));
    
    // Solver options 
    options.push_back(new StringOption("solver",             "Choose which solver to use [Default: cplex)", 1, "cplex", solverValues));
    options.push_back(new IntOption   ("solver_debug_level", "Choose the solver debug level [Default: 2]", 1, 2, 5, 0));
    options.push_back(new IntOption   ("time_limit",         "Time limit for the solver (in seconds, if zero time limit is not set)", 1, 21600, imax,  0));
    options.push_back(new BoolOption  ("presolve",           "Presolve is (0) disabled or (1) enabled [Default: 1]",                               1,  1));
    options.push_back(new IntOption   ("mip_emphasis",       "MIP emphasis (0 to 4) [Default: 0]",                                    1,     0,    4,  0));
    options.push_back(new IntOption   ("lp_method",          "Set LP method [Default: 0]",                                            1,     0,    6,  0));
    options.push_back(new IntOption   ("feasibility_pump",   "Solver feasibility pump heuristic [Default: 0]",                        1,     0,    2, -1));
    options.push_back(new IntOption   ("solver_random_seed", "Solver random seed. If 0 do not set [Default: 0]",                      1,     0, imax,  0));
    options.push_back(new IntOption   ("probing_level",      "MIP probing lebel (-1 to 3) [Default: 1]",                              1,     0,    3, -1));
    options.push_back(new IntOption   ("node_heuristic",         "MIP node heuristic frequency (-1 to inf) [Default: 0]",             1,     0, imax, -1));
    options.push_back(new IntOption   ("branching_policy",       "From -1 to 4, choose branching policy [Default: 0]",                1,     0,    4, -1));
    options.push_back(new BoolOption  ("solver_local_branching", "Solver local branching routine [Default: 0]",                                    1,  0));
    options.push_back(new IntOption   ("solver_parallelism",     "(1) on, (0) off, (2) non-deterministic [Default: 0]",               1,     0,    2,  0));
    options.push_back(new IntOption   ("solver_threads",         "Number of threads [Default: 0]",                                    1,     0, imax,  0));  
    options.push_back(new IntOption   ("mip_strategy",       "Dynamic switch or branch-and-cut [Default: 0 (auto)]",                  1,     0,    2,  0));  


    // Solver cuts
    options.push_back(new IntOption  ("solver_cuts",    "All cuts are (-1) disabled, (0) automatic or (1-3) enabled            [Default: -1]", 1,  0, 3, -1));
    options.push_back(new IntOption  ("gomory_cuts",    "(-1 to 2) Overrides or (-2) not the option for gomory fractional cuts [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("zerohalf_cuts",  "(-1 to 2) Overrides or (-2) not the option for zero-half cuts         [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("cover_cuts",     "(-1 to 3) Overrides or (-2) not the option for cover cuts             [Default: -2]", 1, -2, 3, -2));
    options.push_back(new IntOption  ("landp_cuts",     "(-1 to 3) Overrides or (-2) not the option for lift-and-project cuts  [Default: -2]", 1, -2, 3, -2));
    options.push_back(new IntOption  ("mir_cuts",       "(-1 to 2) Overrides or (-2) not the option for MIR cuts               [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("disj_cuts",      "(-1 to 3) Overrides or (-2) not the option for disjunctive cuts       [Default: -2]", 1, -2, 3, -2));
    options.push_back(new IntOption  ("flowcover_cuts", "(-1 to 2) Overrides or (-2) not the option for flow cover cuts        [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("mcf_cuts",       "(-1 to 2) Overrides or (-2) not the option for MCF cuts               [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("clique_cuts",    "(-1 to 3) Overrides or (-2) not the option for cliques cuts           [Default: -2]", 1, -2, 3, -2));
    options.push_back(new IntOption  ("flowpath_cuts",  "(-1 to 2) Overrides or (-2) not the option for flow path cuts         [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("gub_cuts",       "(-1 to 2) Overrides or (-2) not the option for GUB cuts               [Default: -2]", 1, -2, 2, -2));
    options.push_back(new IntOption  ("implbd_cuts",    "(-1 to 2) Overrides or (-2) not the option for implied bound cuts     [Default: -2]", 1, -2, 2, -2));



    // HERE ADD YOUR OPTIONS



    allowedWithSettingsFile.resize(0);
    allowedWithSettingsFile.push_back("debug");
    allowedWithSettingsFile.push_back("output");
    allowedWithSettingsFile.push_back("lp_filename");
    allowedWithSettingsFile.push_back("export_model");
    allowedWithSettingsFile.push_back("export_cplex_cuts");


    for (int i = 0; i < (int)options.size(); i++) {
        optionsMap[options[i]->getName()] = i;
    }

}

/////////////////////////
/////////////////////////
/////////////////////////
/////////////////////////
// GETS /////////////////
/////////////////////////

bool Options::wasChanged(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        return options[optionsMap[name]]->wasChanged();
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return false;
}


bool Options::getBoolOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        BoolOption* b = dynamic_cast<BoolOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get boolean value from option %s which is not boolean.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return false;
}

int Options::getIntOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        IntOption* b = dynamic_cast<IntOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get integer value from option %s which is not integer.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return 0;
}

double Options::getDoubleOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        DoubleOption* b = dynamic_cast<DoubleOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get double value from option %s which is not double.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return 0;
}

string Options::getStringOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        StringOption* b = dynamic_cast<StringOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get string value from option %s which is not string.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return 0;
}

vector<int> Options::getArrayOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        ArrayOption* b = dynamic_cast<ArrayOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get array from option %s which is not an array option.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return vector<int>();
}

vector<double> Options::getDoubleArrayOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        DoubleArrayOption* b = dynamic_cast<DoubleArrayOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get array from option %s which is not a double array option.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return vector<double>();
}


vector<vector<int>> Options::getMatrixOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        MatrixOption* b = dynamic_cast<MatrixOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get matrix from option %s which is not a matrix option.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return vector<vector<int>>();
}

vector<vector<double>> Options::getDoubleMatrixOption(string name) {
    if (optionsMap.find(name) != optionsMap.end()) {
        DoubleMatrixOption* b = dynamic_cast<DoubleMatrixOption*>(options[optionsMap[name]]);
        if (b != 0) return b->getValue();
        else Util::stop("Error: Attempting to get double matrix from option %s which is not a double matrix option.", name.c_str());
    } else Util::stop("Error: Attempting to get value from non-existing option %s.", name.c_str());
    return vector<vector<double>>();
}



/////////////////////////
/////////////////////////
/////////////////////////
/////////////////////////
// PARSER ///////////////
/////////////////////////

void Options::parseOptions(int numOptions, char* pairs[]) {

    // Empty argv
    if (numOptions == 1) {
        printHelp();
        Util::stop("");
    }
    
    vector<string> optionsFound;
    vector<string> optionsValues;
    int foundSettingsFile = 0;

    for (int i = 1; i < numOptions; i++) {
        string op = pairs[i];

        int fail = 0;
        if (op.size() < 2) fail = 1;
        if (op[0] != '-' || op[1] != '-') fail = 1;
        if (fail == 0) op.erase(0, 2);
        
        vector<string> temp = Util::split(op, "=");

        if (!fail && temp.size() == 2) {
            if (temp[0] == "settings_file") foundSettingsFile = 1;
            optionsFound.push_back(temp[0]);
            optionsValues.push_back(temp[1]);
        } else {
            Util::stop("Error: Invalid option %s", op.c_str());
        }
    }

    if (foundSettingsFile) {
        for (unsigned i = 0; i < optionsFound.size(); i++) {
            if (!Util::contains(allowedWithSettingsFile, optionsFound[i]) && optionsFound[i] != "settings_file") {
                Util::stop("\nWhen you provide a settings_file, the only other options that can be provided via command line are:\n\n%s\n", Util::join(allowedWithSettingsFile, ", ").c_str());
            }
        }
        for (unsigned i = 0; i < optionsFound.size(); i++) {
            if (optionsFound[i] != "settings_file") {
                changeOptionValue(optionsFound[i], optionsValues[i]);
            } else {
                readSettingsFile(optionsValues[i]);
            }
        }
    } else {
        for (unsigned i = 0; i < optionsFound.size(); i++) {
            changeOptionValue(optionsFound[i], optionsValues[i]);
        }
    }

    specificChecks();

}

void Options::readSettingsFile(string filename) {

    vector<string> lines;

    std::ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
    } else {
        Util::stop("\nError: Settings file %s could not be open, either because it doesn't exist or due to some other error.\n", filename.c_str());
    }
    file.close();
    
    vector<string> optionsFound;

    for (unsigned l = 0; l < lines.size(); l++) {
        if (Util::startsWith(lines[l], "#")) continue;
        if (lines[l].empty()) continue;
        vector<string> temp = Util::split(lines[l], " ");
        if (temp.size() != 2) Util::stop("\nError: In settings file %s, line '%s' is invalid.\nIt must contain a valid parameter name and the value.", filename.c_str(), lines[l].c_str());
        if (Util::contains(allowedWithSettingsFile, temp[0])) Util::stop("\nOption %s, defined in the settings file, can only be assigned via command line.", temp[0].c_str());
        if (Util::contains(optionsFound, temp[0])) Util::stop("\nOption %s was defined more than once in the settings file.", temp[0].c_str());

        optionsFound.push_back(temp[0]);
        changeOptionValue(temp[0], temp[1]);
            
        //printf("Line:");
        //for (unsigned i = 0; i < temp.size(); i++) printf(" %s", temp[i].c_str());
        //printf("\n");
    }
}

void Options::specificChecks() {
    if (Options::getInstance()->getStringOption("input").empty()) Util::stop("Error: Input file was not provided");
    
}

void Options::changeOptionValue(string optionName, string value) {
    if (optionsMap.find(optionName) != optionsMap.end()) {
        int index = optionsMap[optionName];
        options[index]->checkOption(value, optionName);
    } else {
        Util::stop("Error: Option %s was not recognised.", optionName.c_str());
    }
}

////////////////////////////
////////////////////////////
////////////////////////////
// PRINT INFORMATION ///////
////////////////////////////

void Options::print() {
    
    int debug = getIntOption("debug");    
    if (debug > 0) {
        printf("---------\n");
        
        bool modified = false;
        for (int i = 0; i < (int)options.size(); i++) {
            if (options[i]->wasChanged()) {
                modified = true;
                break;
            }
        }
        
        printf("%s", debug > 1 ? "All options:\n" : modified ? "Modified options:\n" : "");

        for (int i = 0; i < (int)options.size(); i++) {
            if (debug > 1 || options[i]->wasChanged()) {
                printf("%s=%s\n", options[i]->getName().c_str(), options[i]->getValueAsString().c_str());
            }
        }
        
        if (debug < 1 || modified)
            printf("\n");

    }

}

void Options::printHelp() {
    printf("Usage:\n");
    printf("optLib <data-file> [options]\n");
    printf("\n");
    printf("Options:\n");
    for (int i = 0; i < (int)options.size(); i++) {
        if (options[i]->getShowOutput())
            printf(" --%-20s %s\n", options[i]->getName().c_str(), options[i]->getDescription().c_str());
    }
}



string Options::getAllOptionsAsText() {
    string ret = "";
    for (int i = 0; i < (int)options.size(); i++) {
        char buffer[8000];
        sprintf(buffer, "%s: %s\n", options[i]->getName().c_str(), options[i]->getValueAsString().c_str());
        ret = ret + buffer;
    }
    return ret;
}

string Options::getOutputOptionsAsText() {
    string ret = "";
    for (int i = 0; i < (int)options.size(); i++) {
        if (options[i]->getShowOutput()) {
            char buffer[8000];
            sprintf(buffer, "%s: %s\n", options[i]->getName().c_str(), options[i]->getValueAsString().c_str());
            ret = ret + buffer;
        }
    }
    return ret;
}


string Options::getModifiedOptionsAsText() {
    string ret = "";
    for (int i = 0; i < (int)options.size(); i++) {
        if (options[i]->wasChanged()) {
            char buffer[8000];
            sprintf(buffer, "%s: %s\n", options[i]->getName().c_str(), options[i]->getValueAsString().c_str());
            ret = ret + buffer;
        }
    }
    return ret;
}


