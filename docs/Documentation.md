# Optimisation Library

## The code

The code starts in the *main* function, located in the *main.cc* file, inside the *src* folder.

### *main.cc*

It is the file where the *int main* function is found, responsible for starting and ending the application, as well as configuring the environment for the execution and solution of the problem, based on the options received by the parameters.

* Parameters
  * int argc: (argument count) is an integer and has the number of arguments with which the function was called.
  * char *argv[]: (argument values) is an array of strings, each string in this array is one of the command line parameters.

* Returns
  * 0 (zero) on success

* Actions
  * Instantiate and call the function [factory](#options.h).
  * Instantiate and call the function [parseOptions](#options.h), sending *argc* and *argv*.
  * Instantiate and call the function [print](#options.h).
  * Instantiate and call the function [execute](#execute.h).
  * Report a runtime error
  * Call the function [finalise](#options.h).

### Headers

#### CPLEX.h

This is the abstraction of the [CPLEX class](#cplex.cc).

It is the CPLX solver, so there are all the functions and properties to call ILOG CPLEX API and solve some problem.

* Dependencies
  * ilcplex/ilocplex.h
  * ilcplex/cplex.h
  * [Solver.h](#solver.h)

#### Data.h

This is the abstraction of the [Data class](#data.cc).

* Dependencies
  * [Util.h](#util.h)

* Properties
  * int debug: defines if the execution is in debug mode

* Public functions
  * Data(): constructor
  * ~Data(): destructor
  * void readData(): gets the default data
  * void print(): prints the defaut data

#### DataCapitalBudgeting.h

This is the abstraction of the [DataCapitalBudgeting class](#datacapitalbudgeting.cc).

* Dependencies
  * [Util.h](#util.h)
  * [Data.h](#data.h)

* Properties
  * int numVariables: the number of decision variables
  * vector<int> futureValue: the array of next value of each variable
  * vector<int> initialInvestment: the array with the initial investment of each variable
  * int maxInvestment: the maximum investment

* Public functions
  * DataCapitalBudgeting(): constructor
  * ~DataCapitalBudgeting(): destructor
  * void readData(): sets the data and parameters of the optimization problem
  * void print(): prints the data of the optimization problem
  * int getNumVariables(): gets the number of decision variables
  * int getMaxInvestment(): gets the maximum investment
  * int getInitialInvestment(int i): gets the initial investment.
  * int getFutureValue(int i): gets the future value of the variable. 

#### Execute.h

This is the abstraction of the [Execute class](#execute.cc).

* Dependencies
  * [Data.h](#data.h)
  * [Model.h](#model.h)

* Properties
  * Data [data](#util.h): the Data object
  * Model [model](#model.h): ths Model object
  * double totalTime: the execution time duration

* Public functions
  * Execute(): constructor
  * ~Execute(): destructor
  * void execute(): executes the solution of the problem

#### Model.h

This is the abstraction of the [Model class](#model.cc).

* Dependencies
  * [Solver.h](#solver.h)
  * [Data.h](#data.h)
  * [Solution.h](#solution.h)

* Properties
  * Solver* [solver](#solver.h): the Solver object
  * Solution* [solution](#solution.h): the Solution object
  * vector<string> warmStartNames: the array of warm start name
  * vector<double> warmStartValues: the array of warm start values
  * string solverModelFilename: the filename where the model is
  * double goodEnoughSolution: the good enough value of the solution based on a tolerance value
  * double timeLimit: the limit of time to solve the problem
  * int isMax: if the objective sense of the model is maximization
  * int captureCuts: the number of caputure cuts
  * double totalTime: the total time of the execution
  * double solvingTime: the total time to solve de optimization problem
  * double callbackTime: the callback time
  * double callbackDataTime: the callback data time
  * double callbackCutsTime: the callback cuts time
  * double maxFlowTime: the max flow time
  * double bfsTime: the bfs time 
  * int maxFlowCalls: the maximum number of flow calls
  * int maxFlowsSolved: the maximum number of flows solver_debug_level
  * int callbackCalls: the number of callback calls
  * int cutsAdded: the number of cuts added
  * double bestSolutionTime: the time of the best solution
  * double firstNodeTime: the time of the first node
  * double firstNodeBound: the first node bound
  * bool firstNodeSolved: the first node solved
  * double bestSolutionSoFar: the best solution util a moment
  * int totalNodes: the total number of nodes
  * int bestSolutionNodes: the nodes with the best solution
  * double solverStartTime: the start time that initiate to use the solver, so you can measure the bestSolutionTime by hand
  * int debug: defines if the execution is in debug mode
  * int counter: the counter
  * int maxExportedSolverModels: the maximum number of exported solver models
  * int numExportedSolverModels: the number of exported solver models

* Protected functions 
  * void setSolverParameters(int isMaximisation, string modelFilename = "bc_model.lp", string solverModelFile = "cplexModel"): sets the solver parameters
  * void reserveSolutionSpace(const Data* data): reserves a memory space to the solution
  * void readSolution(const Data* data): gets the solution information
  * void assignWarmStart(const Data* data): sets the assign warm start
  * void createModel(const Data* data): creates a model formatted to the solver based on the data 
  * void solve(const Data* data): solves the optimization problem

* Public functions
  * Model(): constructor
  * ~Model(): destructor
  * void execute(const Data* data): executes the process of solving the optimization problem
  * Solution* getSolution(): gets the solution of the problem
  * void printSolution(): prints the solution of the problem
  * vector<SolverCut> separationAlgorithm(vector<double> sol): gets the array of solver cuts
  * void incumbentCallbackFunction(const double& objval, const double* sol): the incumbent callback function
  * void bestSolutionValueCallbackFunction(double value): sets the best solution value callback function
  * void firstNodeBoundCallbackFunction(double bound): sets the first node bound callback function
  * int isSolutionGoodEnough(double value): gets the information that the solution is good enough
  * string getSolverModelFilename(): gets the filename of the solver model
  * Solver* getSolver(): gets the solver
  * double getTotalTime(): gets the total time
  * double getSolvingTime(): gets the solving time
  * double getCallbackTime(): gets the callback time
  * double getMaxFlowTime(): gets the maximum flow time
  * double getBfsTime(): gets the bfs time
  * double getCallbackDataTime(): gets the callback data time
  * double getCallbackCutsTime(): gets the callback cuts time
  * int getMaxFlowCalls(): gets the maximum number of flow calls
  * int getMaxFlowsSolved(): gets the maximum number of flows solved
  * int getCallbackCalls(): gets the callback calls
  * int getCutsAdded(): gets the number of cuts added
  * double getBestSolutionTime(): gets the time of the best solution
  * double getFirstNodeTime(): gets the time of the first node
  * double getFirstNodeBound(): gets the first node bound
  * int getTotalNodes(): gets the total number of nodes
  * int getBestSolutionNodes(): gets the nodes of the best solution
  * int getCounter(): gets the counter
  * int shouldExportMoreSolverModels(): defines if the system should export more solver models
  * void addExportedSolverModel(): adds exported solver model
  * int getCurrentSolverModel(): gets the current solver model
  * void setTimeLimit(double time): sets the time limit
  * void overrideDebug(int d): sets the override debug
  * void setCaptureCuts(int c): sets the caputure cuts
  * int shouldCaptureCuts(): defines if the system should capture cuts
  * void getExtraCuts(vector<SolverCut>& sc): gets the extra cuts

#### ModelCapitalBudgeting.h

This is the abstraction of the [ModelCapitalBudgeting class](#modelcapitalbudgeting.cc).

* Dependencies
  * [Model.h](#model.h)
  * [Solution.h](#solution.h)

* Properties
  * string x: the string that describes the solution
  * int V: the solution value
  * vector<double> sol_x: the value of the variables
  
* Private functions
  * void reserveSolutionSpace(const Data* data): reserves memory space to the solution
  * void readSolution(const Data* data): gets the solution
  * void assignWarmStart(const Data* data)
  * void createModel(const Data* data): creates a model formatted to the solver based on the data 
  * void printSolutionVariables(int digits = 5, int decimals = 2): prints the value of the variables in the solution

* Public functions
  * ModelCapitalBudgeting(): constructor
  * ~ModelCapitalBudgeting(): destructor
  * void execute(const Data *data): executes the process of solving the Capital Budgeting problem

#### Option.h

This is the abstraction of the [Option class](#option.cc).

* Dependencies
  * [Util.h](#util.h)

* Super Class: Option

* Sub Classes:
  * BoolOption
  * IntOption
  * DoubleOption
  * StringOption
  * ArrayOption
  * DoubleArrayOption
  * MatrixOption

* Properties
  * string name: the name of the option
  * string description: the description of the option
  * bool showOutput: if the output will be shown

* Public functions
  * Option(): constructor
  * Option(string name, string description, bool showOutput): constructor
  * ~Option(): destructor
  * void checkOption(string str, string optionName): validates the option
  * bool wasChanged(): verifies if an option was was changed
  * string getValueAsString(): gets the value of the option as a string
  * string getName(): gets the name of the option
  * string getDescription(): gets the description of the option
  * bool getShowOutput(): verifies if the output will be shown

#### Options.h

This is the abstraction of the [Options class](#options.cc).

This is the abstraction of the Options class.

* Dependencies
  * [Util.h](#util.h)
  * [Option.h](#option.h)

* Private functions
  * void assignDefaultValues(): assigns default configuration values
  * void readSettingsFile(string filename): reads the settings file
  * void changeOptionValue(string optionName, string value): changes the value of an option
  * void specificChecks(): validates the input parameter

* Public functions
  * getInstance(): gets the singleton instance
  * Options(): constructor
  * ~Options(): destructor
  * void factory(): creates an instance of the class
  * static void finalise(): deletes the instance of the class
  * void parseOptions(int numOptions, char* pairs[]): converts parameters to options
  * void print(): prints the used options
  * void printHelp(): prints the list of available options and the descriptions
  * string getAllOptionsAsText(): gets and prints the list of all options names and values
  * string getOutputOptionsAsText(): gets and prints the list of all output options names and values
  * string getModifiedOptionsAsText(): gets and prints the list of modified options names and values
  * bool getBoolOption(string name): gets a boolean option if it exists
  * int getIntOption(string name): gets an integer option if it exists
  * double getDoubleOption(string name): gets a double option if it exists
  * string getStringOption(string name): gets a string option if it exists
  * vector<int> getArrayOption(string name): gets an integer array option if it exists
  * vector<double> getDoubleArrayOption(string name): gets a double array option if it exists
  * vector<vector<int>> getMatrixOption(string name): gets a matrix option if it exists
  * bool wasChanged(string name): verifies if an option was was changed

#### Solution.h

This is the abstraction of the [Solution class](#solution.cc).

* Dependencies
  * [Util.h](#util.h)
  * [Data.h](#data.h)

* Properties
  * double value: the value of the solution of the optimization problem
  * double bestBound: the best solution  of the optimization problem
  * bool solutionExists: the boolean to say that the solution exists
  * bool isOptimal: the boolean to say that the solution is optimal
  * bool isInfeasible: the boolean to say that the solution is infeasible
  * bool isUnbounded: the boolean to say that the solution is unbounded
  * int debug: defines if the execution is in debug mode

* Public functions
  * Solution(): constructor
  * ~Solution(): destructor
  * void setSolutionStatus(bool exists, bool optimal, bool infeasible, bool unbounded): sets the properties values (if the solution exists, is optimal, is infeasible and unbounded)
  * void resetSolution(): resets the current solution information
  * void print(int overrideDebug = -1): prints all the informations of the solution
  * void setValue(double v): sets value to the property *V*
  * void void setBestBound(double bb): sets value to the property *bestBound*
  * double getGap(): gets the gap of the solution founded
  * double getValue(): gets the value of the solution
  * double getBestBound(): gets te best bound of the solution
  * bool isFeasible(): gets the information that the solution is feasible
  * bool isSolutionOptimal(): gets the information that the solution is optimal
  * bool doesSolutionExist(): gets the information about the existance of the solution

#### Solver.h

This is the abstraction of the [Solver class](#solver.cc).

It is the default class for the solver, so there are all the functions and properties to call some solver API.

* Dependencies
  * [Util.h](#util.h)

#### Util.h

This is the abstraction of the [Util class](#util.cc).

* Dependencies
  * stdlib.h
  * stdio.h
  * utility
  * numeric
  * limits
  * string
  * vector
  * set
  * algorithm
  * map
  * utility
  * stdexcept
  * iostream
  * fstream
  * sstream
  * math.h
  * type_traits  

* Time functions
  * static float getTime(): gets the current time
  * static double getWallTime(): gets the wall time
  * static float getClockTime(): gets the clock time
  * static const string getCurrentDateTime(): gets the current date and time

* Open and close files functions
  * static bool openFile(FILE**, const char*, const char*): opens a file
  * static bool closeFile(FILE**): closes a file
  * static bool fileExists(string): verifies if the file exists

* Exception handler functions
  * static void throwInvalidArgument(string msg, ...): throws an invalid argument exception
  * static void stop(string msg, ...): stops the process

* Boolena success functions
  * static int stringToDouble(string text, double& number): verifies if string can be converted to a number
  * static double stringToDouble(string text): converts string to double

* General functions
  * static int numDigits(int number): gets the number of digits of a number

* Vector functions
  * static std::vector<T> subVector(std::vector<T> v, int first, int last): tamplate function to get a sub vector

* String functions
  * string lex(int l): convert an integer to string
  * static vector<string> split(const string& i_str, const string& i_delim, int eliminateEmptySubstrings = 1): splits a string in more strings
  * static string join(const vector<string>& strings, const string& separator): joins strings with a chosen separator
  * static string toLowerCase(string data): converts the string to lowercase
  * static string toUpperCase(string data): converts the string to uppercase
  * static int isNumber(string s): verifies if a string is a number
  * static int isEqual(string s, string c): verifies if two strings are equal
  * static int startsWith(string s, string start): verifies if a string starts with another chosen string
  * static int contains(vector<string> v, string s): verifies if a string contains another chosen string

* Print functions
  * static void printIntVector(const vector<int> &vec, int tot = 3, int numPerLine = 0): prints an integer vector
  * static void printUnsignedVector(const vector<unsigned> &vec, int tot = 3, int numPerLine = 0): prints an unsigned vector
  * static void printDoubleVector(const vector<double> &vec, int tot = 5, int dec = 2, int numPerLine = 0): prints a double vector
  * static void printTwoDoubleVectors(const vector<double> &vec1, const vector<double> &vec2, int tot1 = 5, int dec1 = 2, int tot2 = 5, int dec2 = 2): prints two double vectors
  * static void printDoubleMatrix(const vector<vector<double> > &vec, int tot = 5, int dec = 2): prints a double matrix
  * static void printIntMatrix(const vector<vector<int> > &vec, int tot = 5, int printRowNames = 0): prints an integer matrix
  * static void printNonZeroDoubleVector(const vector<double> &vec, int tot = 5, int dec = 2, int numPerLine = 0): prints a non zero double vector
  * static void printStringVector(const vector<string> vec, string initialText = "", string separator = " "): prints a string vector
  * static void printGraph(const vector<vector<int>> &graph): prints a graph
  * static void printGraph(const vector<vector<double>> &graph, int dec = 2): prints a graph with determined number of decimal places
  * static void printFileIntVector(FILE* file, const vector<int> &vec, int numPerLine = 0): prints a integer vector in a file
  * static void printFileUnsignedVector(FILE* file, const vector<unsigned> &vec, int numPerLine = 0): prints a unsigned vector in a file
  * static void printFileDoubleVector(FILE* file, const vector<double> &vec, int dec = 2, int numPerLine = 0): prints a double vector in a file
  * static void printFileNonZeroDoubleVector(FILE* file, const vector<double> &vec, int dec = 2, int numPerLine = 0): prints a non zero double vector in a file

* Ramdon number functions
  * static void initialiseSeed(int seed = 0): initializes a seed to generate random numbers
  * static double getSeed(): gets a seed to generate a random number
  * static int randomNumber(int): gets a random integer number
  * static unsigned long randomLong(unsigned long);: gets a random long number
  * static double randomNumber(double); gets a random double number
  * static int randomAlexandre(int, double*): gets a random integer number using bits
  * static float randomNumberAlexandre(double*): gets a random float number using bits
  * static unsigned long randomLongAlexandre(unsigned long, double*): gets a random long number using bits
  * static std::vector<double> randomN(int, bool, double): gets a random double vector

### Implementations

#### CPLEX.cc

This class is responsible to solve optimization problems using ILOG CPLEX.

* Dependencies
  * [CPLEX.h](#cplex.h)
  * [Model.h](#model.h)

#### Data.cc

This class is responsible to create and manage a default data object.

* Dependencies
  * [Data.h](#data.h)
  * [Options.h](#options.h)

* Data()
  * Constructor
  * Actions:
    * sets debug according to the *debug* option
* ~Data()
  * Destructor

#### DataCapitalBudgeting.cc

This class is responsible to create and manage a data object for the Capital Budgeting problem.

* Dependencies
  * [DataCapitalBudgeting.h](#datacapitalbudgeting.h)
  * [Options.h](#options.h)

* DataCapitalBudgeting()
  * Constructor
  * Actions:
    * Sets numVariables to 0 (zero)
    * Sets maxInvestment to 0 (zero)
* ~DataCapitalBudgeting() 
  * Destructor
* void readData()
  * Actions:
    * Sets the number of variables of the Capital Budgeting problem
    * Sets the maximum investment parameter of the Capital Budgeting problem
    * Sets the array of future values of the Capital Budgeting problem
    * Sets the array of inicial investment of the Capital Budgeting problem
* void print()
  * Actions:
    * Prints the number of variables, the maximum investment and the list of future values and initial investment, if the *debug* option is activated
* int getNumVariables()
  * Returns:
    * The number of decision variables
* int getMaxInvestment()
  * Returns:
    * The maximum investment
* int getInitialInvestment(int i)
  * Parameters:
    * i: index of the variable
  * Actions:
    * Verifies if the index exists
  * Returns:
    * The initial investment of a variable
* int getFutureValue(int i)
  * Parameters:
    * i: index of the variable
  * Actions:
    * Verifies if the index exists
  * Returns:
    * The future value of a variable

#### Execute.cc

This class is responsible to execute the main process to solve an optimization problem.

* Dependencies
  * [Execute.h](#execute.h)
  * [Options.h](#options.h)
  * [DataCapitalBudgeting.h](#datacapitalbudgeting.h)
  * [ModelCapitalBudgeting.h](#modelcapitalbudgeting.h)

* Execute()
  * Constructor
  * Actions:
    * Sets totalTime to 0 (zero)
    * Sets model to NULL
    * Sets data to NULL
* ~Execute()
  * Destructor
  * Actions:
    * Deletes *model* instance
    * Deletes *data* instance
* void execute()
  * Actions: 
    * Calls the function [getTme()](#util.h) and sets the start time
    * Sets the *data* and the *model* according to the *model* option (it can be [DataCapitalBudgeting](#datacapitalbudgeting.h) and [ModelCapitalBudgeting](#modelcapitalbudgeting), or a defautl [Data](#data.h) and [Model](#model.h))
    * Calls the function [readData()](#data.h)
    * Calls the function [print()](#data.h)
    * Calls the function [getTme()](#util.h) and calculates the total time

#### Model.cc

This class is responsible to create and manage a default model object.

* Dependencies
  * [Model.h](#model.h)
  * [CPLEX.h](#cplex.h)
  * [Options.h](#options.h)

* void setSolverParameters(int isMaximisation, string modelFilename = "bc_model.lp", string solverModelFile = "cplexModel")
  * Parameters:
    * isMaximisation: if the objective sense is maximization
    * modelFilename: the filename where the model is [Default: "bc_model.lp"]
    * solverModelFile: the solver model file [Default: "cplexModel"]
  * Actions:
    * Sets the value of *isMax*
    * Calls the function [changeObjectiveSense(isMax)](#solver.h)
    * Sets the value of *solverModelFilename*
    * Calls the function [debugInformation(debug)](#solver.h)
    * Calls the function [enablePresolve](#solver.h), sending the *presolve* option 
    * Calls the function [setMIPEmphasis](#solver.h), sending the *mip_emphasis* option 
    * Calls the function [setMIPStrategy](#solver.h), sending the *mip_strategy* option 
    * Calls the function [setSolverParallelism](#solver.h), sending the *solver_threads* option 
    * Calls the function [setNodeHeuristic](#solver.h), sending the *node_heuristic* option 
    * Calls the function [setSolverLocalBranching](#solver.h), sending the *solver_local_branching* option 
    * Calls the function [setProbingLevel](#solver.h), sending the *probing_level* option 
    * Calls the function [setTimeLimit(timeLimit)](#solver.h)
    * Sets the value of variables based on the options
    * Calls the function [setSolverCuts](#solver.h), sending options
    * Calls the function [setLPMethod](#solver.h), sending the *lp_method* option 
    * Calls the function [setFeasibilityPump](#solver.h), sending the *feasibility_pump* option 
    * Calls the function [setSolverRandomSeed](#solver.h), sending the *solver_random_seed* option 
    * Calls the function [exportModel(modelFilename.c_str())](#solver.h), if *captureCuts* is activate
    * Calls the function [addSolveCallback](#solver.h)

* Model() 
  * Constructor
  * Actions:
    * Gets the *solver* option
    * If the solver is *cplex*, creates an instance of [CPLEX](#cplex.h), else creates an instance of a default [Solver](#solver.h) 
    * Creates an instance of [Solution](#solution.h) object
    * Sets the inicial value for all the properties
* ~Model()
  * Destructor
  * Actions:
    * Deletes the solver instance
    * Deletes the solution instance
* Solution* getSolution()
  * Return:
    * The solution of the problem
* void printSolution()
  * Actions:
    * Calls the function [print()](#solution.h)
* vector<SolverCut> separationAlgorithm(vector<double> sol)
  * Returns:
    * The array of solver cuts
* string getSolverModelFilename()
  * Returns: 
    * The filename of the solver model
* Solver* getSolver() 
  * Returns: 
    * The solver
* double getTotalTime() 
  * Returns:
    * The total time
* double getSolvingTime() 
  * Returns:
    * The solving time
* double getCallbackTime()
  * Returns:
    * The callback time
* double getMaxFlowTime()
  * Returns:
    * The maximum flow time
* double getBfsTime() 
  * Returns:
    * The bfs time
* double getCallbackDataTime()
  * Returns:
    * The callback data time
* double getCallbackCutsTime()
  * Returns:
    * The callback cuts time
* int getMaxFlowCalls()
  * Returns:
    * The maximum number of flow calls
* int getMaxFlowsSolved()
  * Returns:
    * The maximum number of flows solved
* int getCallbackCalls()
  * Returns:
    * The callback calls
* int getCutsAdded()
  * Returns:
    * The number of cuts added
* double getBestSolutionTime() 
  * Returns:
    * The time of the best solution
* double getFirstNodeTime() 
  * Returns:
    * The time of the first node
* double getFirstNodeBound()
  * Returns:
    * The first node bound
* int getTotalNodes() 
  * Returns:
    * The total number of nodes
* int getBestSolutionNodes()
  * Returns:
   * The nodes of the best solution
* int getCounter()
  * Returns:
    * The counter
* int shouldExportMoreSolverModels()
  * Returns:
    * 1, if the number of exported solver models is lower than the maximum number of exported solver models
    * 0, if the number of exported solver models is greater or equal the maximum number of exported solver models
* void addExportedSolverModel()
  * Actions:
    * Adds 1 in the number of exported solver models
* int getCurrentSolverModel()
  * Returns:
    * The current number of exported solver models
* void setTimeLimit(double time)
  * Actions:
    * Sets the time limit
* void overrideDebug(int d)
  * Actions:
    * Sets the override debug
* void setCaptureCuts(int c)
  * Actions:
    * Sets the caputure cuts
* int shouldCaptureCuts()
  * Returns:
    * the number of capture cuts
* void getExtraCuts(vector<SolverCut>& sc)
  * Parameters:
    * sc: an array of solver cuts
  * Actions:
    * Reads the model files
    * Finds the constraints of the model
    * Closes the files

#### ModelCapitalBudgeting.cc

This class is responsible to create and manage a model object for the Capital Budgeting problem..

* Dependencies
  * [ModelCapitalBudgeting.h](#modelcapitalbudgeting.h)
  * [Options.h](#options.h)
  * [DataCapitalBudgeting.h](#datacapitalbudgeting.h)
  
* void reserveSolutionSpace(const Data* data)
  * Parameters:
    * data: the object with the parameters of the Capital Budgeting problem.
  * Actions:
    * Resizes the sol_x array
* void readSolution(const Data* data)
  * Parameters:
    * data: the object with the parameters of the Capital Budgeting problem.
  * Actions:
    * Calls the function [getNodeCount()](#solver.h)
    * Calls the function [resetSolution()](#solution.h)
    * Calls the function [setSolutionStatus()](#solution.h) and verify it is optimal, feasible and unbounded
    * If the solution does't exist, prints it
    * If the solution exists, calls [setValue()](#solution.h), [setBestBound()](#solution.h) and fills sol_x array
* void createModel(const Data* data): create a model formatted to the solver
  * Parameters:
    * data: the object with the parameters of the Capital Budgeting problem.
  * Actions:
    * Creates a [DataCapitalBudgeting](#datacapitalbudgeting.h) instance
    * Calls the function [getNumVariables](#datacapitalbudgeting.h)
    * Calls the function [changeObjectiveSense()](#solver.h)
    * Sends the decision variables to the solver calling [addBinaryVariable()](#solver.h)
    * Sends the constraints to the solver
* void printSolutionVariables(int digits = 5, int decimals = 2)
  * Parameters:
    * digits: maximum number of digits of the value of the solution
    * decimals: maximum number of decimal places of the value of the solution
  * Actions:
    * Prints the value of each decision variable of the solution, if the *debug* option is activated

* ModelCapitalBudgeting()
  * Constructor
  * Actions:
    * Sets V to 0 (zero)
    * Sets x to "x" 
* ~ModelCapitalBudgeting()
  * Destructor
* void execute(const Data *data)
  * Parameters:
    * data: the object with the parameters of the Capital Budgeting problem.
  * Actions:
    * Calls the function [getTme()](#util.h) and set the start time
    * Calls the function [printSolverName()](#solver.h)
    * Calls the function createModel(data)
    * Calls the function reserveSolutionSpace(data)
    * Calls the function assignWarmStart(data)
    * Calls the function setSolverParameters(1)
    * Calls the function [addInfoCallback(this)](#solver.h)
    * Calls the function solve(data)
    * Calls the function [getTme()](#util.h) and calculate the total time
    * Calls the function printSolutionVariables()

#### Option.cc

This class is responsible to create and manage a setting.

* Dependencies
  * [Option.h](#option.h)

* BoolOption: this is a sub class of *Option* and is responsible to create the instance ans configurate a boolean option.
* IntOption: this is a sub class of *Option* and is responsible to create the instance ans configurate an integer option.
* DoubleOption: this is a sub class of *Option* and is responsible to create the instance ans configurate a double option.
* StringOption: this is a sub class of *Option* and is responsible to create the instance ans configurate a string option.
* ArrayOption: this is a sub class of *Option* and is responsible to create the instance ans configurate an integer array option.
* DoubleArrayOption: this is a sub class of *Option* and is responsible to create the instance ans configurate a double array option.
* MatrixOption: this is a sub class of *Option* and is responsible to create the instance ans configurate a matrix option.

* Option() and Option(string name, string description, bool showOutput)
  * Constructor
  * Parameters: 
      * name
      * description
      * showOutput: show output 
      * defaultValues: default value (some cases)
      * possibleValues: possible values (some cases)
      * max: maximum value (some cases)
      * min: minimum value (some cases).
* ~Option()
  * Destructor.
* void checkOption(string str, string optionName)
  * Parameters:
    * str: a string that will be compared
    * optionName: the name of the option
  * Actions:
    * Verifies if str is valid
    * Sets the value of the option
* bool wasChanged()
  * Returns:
    * true, if the value is equal the default value of the option
    * false, if the value is different of the default value of the option
* string getValueAsString()
  * Returns:
    * "1", if the value is 1
    * "0", if the value ir 0
* string getName()
  * Returns:
    * the name of the option
* string getDescription()
  * Returns:
    * the description of the option
* bool getShowOutput()
* Returns:
    * the show output value

#### Options.cc

This class is responsible to create and manage the list of settings.

* Dependencies
  * [Options.h](#options.h)

* void assignDefaultValues()
  * Actions: 
    * Creates a vector to the solver options values and adds the default value ("cplex")
    * Creates a vector to the model options values and adds the default value ("toy")
    * Sets the maximum value of *int* (*imax*)
    * Creates an instance of all configuration parameters and adds to the Options array
* void readSettingsFile(string filename)
  * Parameters:
    * filename: the name of the sttings file
  * Actions:
    * Opens the file using the *filename* parameter
    * Reads each line of the file
    * Verifies the format of the options in the file
    * Adds the options to an array
    * Calls the function changeOptionValue()
* void changeOptionValue(string optionName, string value)
  * Parameters:
    * optionName: the name of the option that will be wasChanged
    * value: the new value of the option
  * Actions: 
    * Searchs the option in the Options map array
    * Calls the function [checkOption()](#option.h)
* void specificChecks()
  * Actions:
    * Verifies if the *input* option exists

* getInstance()
  * Actions:
    * Gets the singleton instance
  * Returns:
    * The current *Options* instance
* Options() 
  * Constructor
  * Actions:
    * Calls the function assignDefaultValues()
* ~Options()
  * Destructor
* void factory()
  * Actions:
    * Deletes the instance that already exists
    * Creates a new instance of *Options*
* static void finalise()
  * Actions:
    * Deletes the *Options* instance
* void parseOptions(int numOptions, char* pairs[])
  * Parameters:
    * numOptions: the number of parameters received
    * pairs: the list of options
  * Actions: 
    * Verifies if the is only one option and return and error if it is true.
    * Verifies if all parameters are in the correct format, like "--parameter=value"
    * If it is ok, saves the options and the values in two arrays, else, returns an error
    * Verifies the settings flie if it exists
    * Calls the function specificChecks()
* void print()
  * Actions:
    * Prints the list of all options, if the *debug* option is activated
    * Prints the list of modified options, if the *debug* option is activated
* void printHelp()
  * Actions:
    * Prints the list of available options and the descriptions
* string getAllOptionsAsText()
  * Actions:
    * Prints the list of all options names and values
* string getOutputOptionsAsText()
  * Actions:
    * Gets and prints the list of all output options names and values
* string getModifiedOptionsAsText()
  * Actions:
    * Gets and prints the list of modified options names and values
* bool getBoolOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* int getIntOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* double getDoubleOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* string getStringOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* vector<int> getArrayOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* vector<double> getDoubleArrayOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* vector<vector<int>> getMatrixOption(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * The value of the option
* bool wasChanged(string name)
  * Parameters:
    * name: the name of the option
  * Actions:
    * Verifies if the option exists
  * Returns:
    * true, if the option was changed
    * false, if the option wasn't changed

#### Solution.cc

This class is responsible to manage the solution of some optimization problem.

* Dependencies
  * [Util.h](#util.h)
  * [Data.h](#data.h)

* Solution()
  * Constructor
  * Actions:
    * Calls the function resetSolution()
    * Sets debug according to the *debug* option
* ~Solution()
  * Destructor
* void setSolutionStatus(bool exists, bool optimal, bool infeasible, bool unbounded)
  * Parameters:
    * exists: boolean to say that the solution exists
    * optimal: boolean to say that the solution is optimal
    * infeasible: boolean to say that the solution is infeasible
    * unbounded: boolean to say that the solution is unbounded
  * Actions: 
    * Sets the value of solutionExists
    * Sets the value of isOptimal
    * Sets the value of isInfeasible
    * Sets the value of isUnbounded
* void resetSolution()
  * Actions:
    * Sets the inicial value for all the properties
* void print(int overrideDebug = -1)
  * Parameters:
    * overrideDebug: boolean to say that the debug option will be overridden
  * Actions:
    * Prints all the information about the solution
* void setValue(double v)
  * Actions:
    * Sets the value of the solution
* void void setBestBound(double bb)
  * Actions:
    * Sets the value of the best bound
* double getGap()
  * Returns:
    * The gap of the solution founded 
* double getValue()
  * Returns: 
    * The value of the solution
* double getBestBound()
  * Returns: 
    * The best bound of the solution
* bool isFeasible()
  * Returns: 
    * true, if the solution is feasible
    * false, if the solution is infeasible
* bool isSolutionOptimal()
   * Returns: 
    * true, if the solution is optimal
    * false, if the solution is not optimal
* bool doesSolutionExist()
   * Returns: 
    * true, if the solution exists
    * false, if the solution doesn't exist

#### Solver.cc

This class is responsible to solve optimization problems.

* Dependencies
  * [Solver.h](#solver.h)

#### Util.cc

This class is responsible to host all the auxiliary functions.

* Dependencies
  * [Util.h](#util.h)
  * string.h
  * Windows.h
  * stdint.h
  * winsock.h
  * sys/time.h
  * sys/times.h
  * sys/resource.h
  * sys/unistd.h
  * sys/stat.h
  * stdarg.h
  * memory
  * random
  * chrono

* static float getTime()
  * Returns:
    * The current time
* static double getWallTime()
  * Returns:
    * The wall time
* static float getClockTime() 
  * Returns:
    * The clock time
* static const string getCurrentDateTime() 
  * Returns: 
    * The current date and time (format is YYYY-MM-DD.HH:mm:ss)

* static bool openFile(FILE**, const char*, const char*)
  * Actions:
    * Tries to open a file
  * Returns:
    * true, if the file could be opened
    * false, if the file cound not be opened
* static bool closeFile(FILE**)
  * Actions:
    * Tries to close a file
  * Returns:
    * true, if the file could be closed
    * false, if the file cound not be closed
* static bool fileExists(string)
  * Parameters:
    * string: the name of the file
  * Returns:
    * true, if the file exists
    * false, if the file doesn't exists

* static int stringToDouble(string text, double& number)
  * Parameters:
    * text: the string to bem converted
    * number: a number that will be compared
  * Returns:
    * 0, if string can be converted to a number
    * 1, if string can't be converted to a number
* static double stringToDouble(string text)
  * Parameters:
    * text: the string that will be converted
  * Returns:
    * A double value

* static int numDigits(int number)
  * Parameters?
    * number
  * Returns:
    * The nuber of digits of the *number*

* static std::vector<T> subVector(std::vector<T> v, int first, int last)
  * Parameters:
    * v: the vector
    * first: the fisrt value
    * last: the last value
  * Returns:
    * The sub vector

* string lex(int l)
  * Parameters:
    * l: the integer value
  * Returns:
    * The string

* static vector<string> split(const string& i_str, const string& i_delim, int eliminateEmptySubstrings = 1)
  * Parameters:
    * i_str: the string that will be splitted
    * i_delim: the delimitor of split
    * eliminateEmptySubstrings: if the empty substrings will be eliminated
  * Returns:
    * A vector with the splitted string
* static string join(const vector<string>& strings, const string& separator):
  * Parameters:
    * string: the strings that will bem joined
    * separator: the string the will separate the strings
  * Returns:
    * The joined string
* static string toLowerCase(string data)
  * Parameters:
    * data: the string that will be tansformed
  * Returns:
    * The string in lowercase
* static string toUpperCase(string data)
  * Parameters:
    * data: the string that will be tansformed
  * Returns:
    * The string in uppercase
* static int isNumber(string s)
  * Parameters:
    * s: the string that will be verified
  * Returns:
    * true, if the string is a number
    * false, if the string is not a number
* static int isEqual(string s, string c)
  * Returns:
    * true, if both strings are equal
    * false, if both string are not equal
* static int startsWith(string s, string start)
  * Parameters:
    * s: the string that will be verified
    * start: the string that will be compared
  * Returns:
    * true, if the string starts with another chosen string
    * false, if the string doesn't start with another chosen string
* static int contains(vector<string> v, string s)
  * Parameters:
    * v: the vector that will be verified
    * s: the string that will be compared
  * Returns:
    * true, if the vector contains the string 
    * false, if the vector doesn1t contain the string 

* Print functions
  * static void printIntVector(const vector<int> &vec, int tot = 3, int numPerLine = 0)
    * Parameters:
      * &vec: the vector that will be printed
      * tot [Dafult: 3]
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions:
      * Prints each value of a vector
  * static void printUnsignedVector(const vector<unsigned> &vec, int tot = 3, int numPerLine = 0)
    * Parameters:
      * &vec: the vector that will be printed
      * tot [Dafult: 3]
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions:
      * Prints each value of a vector
  * static void printDoubleVector(const vector<double> &vec, int tot = 5, int dec = 2, int numPerLine = 0)
    * Parameters:
      * &vec: the vector that will be printed
      * tot [Dafult: 5]
      * dec: the number of decimal places [Dafult: 2]
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions:
      * Prints each value of a vector
  * static void printTwoDoubleVectors(const vector<double> &vec1, const vector<double> &vec2, int tot1 = 5, int dec1 = 2, int tot2 = 5, int dec2 = 2)
    * Parameters:
      * &vec1: the first vector that will be printed
      * &vec2: the second vector that will be printed
      * tot1 [Dafult: 5]
      * tot2 [Dafult: 5]
      * dec1: the number of decimal places of the first vector [Dafult: 2]
      * dec2: the number of decimal places of the second vector [Dafult: 2]
    * Actions:
      * Prints each value of the vectors
  * static void printDoubleMatrix(const vector<vector<double> > &vec, int tot = 5, int dec = 2)
    * Parameters:
      * &vec: the vector that will be printed
      * tot [Dafult: 5]
      * dec: the number of decimal places [Dafult: 2]
    * Actions:
      * Prints each value of a matrix
  * static void printIntMatrix(const vector<vector<int> > &vec, int tot = 5, int printRowNames = 0)
    * Parameters:
      * &vec: the vector that will be printed
      * tot [Dafult: 5]
      * printRowNames: if the name of the rows will be printed [Dafult: 0]
    * Actions:
      * Prints each value of a matrix
  * static void printNonZeroDoubleVector(const vector<double> &vec, int tot = 5, int dec = 2, int numPerLine = 0)
    * Parameters:
      * &vec: the vector that will be printed
      * tot [Dafult: 5]
      * dec: the number of decimal places [Dafult: 2]
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions:
      * Prints each value of a vector
  * static void printStringVector(const vector<string> vec, string initialText = "", string separator = " ")
    * Parameters:
      * &vec: the vector that will be printed
      * initialText: the initial text [Dafult: ""]
      * separator: the separator of the strings [Dafult: " "]
    * Actions:
      * Prints each value of a vector
  * static void printGraph(const vector<vector<int>> &graph)
    * Parameters:
      * &graph: the graph
    * Actions:
      * Prints the graph
  * static void printGraph(const vector<vector<double>> &graph, int dec = 2)
    * Parameters:
      * &graph: the graph
      * dec: the number of decimal places [Dafult: 2]
    * Actions:
      * Prints the graph
  * static void printFileIntVector(FILE* file, const vector<int> &vec, int numPerLine = 0)
    * Parameters:
      * file: the file where the vector will be printed
      * &vec: the vector that will be printed
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions: 
      * Prints a integer vector in a file
  * static void printFileUnsignedVector(FILE* file, const vector<unsigned> &vec, int numPerLine = 0)
     * Parameters:
      * file: the file where the vector will be printed
      * &vec: the vector that will be printed
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions: 
      * Prints a unsigned vector in a file
  * static void printFileDoubleVector(FILE* file, const vector<double> &vec, int dec = 2, int numPerLine = 0)
     * Parameters:
      * file: the file where the vector will be printed
      * &vec: the vector that will be printed
      * dec: the number of decimal places [Dafult: 2]
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions: 
      * Prints a double vector in a file
  * static void printFileNonZeroDoubleVector(FILE* file, const vector<double> &vec, int dec = 2, int numPerLine = 0)
    * Parameters:
      * file: the file where the vector will be printed
      * &vec: the vector that will be printed
      * dec: the number of decimal places [Dafult: 2]
      * numPerLine: the number of values per line [Dafult: 0]
    * Actions: 
      * Prints a non zero double vector in a file

* static void initialiseSeed(int seed = 0)
  * Parameters: 
    * seed: the seed number [Dafult: 0]
  * Actions:
    * initializes with the seed number, if it is not 0 (zero)
    * initializes with the time of the day, if it is 0 (zero)
* static double getSeed()
  * Returns: 
    * The seed based on the time of the day
* static int randomNumber(int resto)
  * Parameters:
    * resto: maximum random value
  * Returns:
    * A random number between 0 and *resto*
* static unsigned long randomLong(unsigned long resto)
  * Parameters:
    * resto: maximum random value
  * Returns:
    * A random number between 0 and *resto*
* static double randomNumber(double resto)
  * Parameters:
    * resto: maximum random value
  * Returns:
    * A random number between 0 and *resto*
* static int randomAlexandre(int resto, double* semente)
  * Parameters:
    * resto: maximum random value
    * semente: the seed
  * Returns:
    * A random number between 0 and *resto* based on the *semente*
* static float randomNumberAlexandre(double* resto)
  * Parameters:
    * resto: maximum random value
  * Returns:
    * A random number between 0 and *resto*
* static unsigned long randomLongAlexandre(unsigned long resto, double* semente)
  * Parameters:
    * resto: maximum random value
    * semente: the seed
  * Returns:
    * A random number between 0 and *resto* based on the *semente*
* static std::vector<double> randomN(int resto, bool allowNeg, double maxNeg)
  * Parameters:
    * resto: maximum random value
    * allowNeg: if negative numbers will the allowed
    * maxNeg: the maximum negative number 
  * Returns:
    * A random double vector
