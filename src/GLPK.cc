/* Normally all GLPK API routines start array indexing from 1, not from 0 (except the specially stipulated cases). 

This means, for example, that if some vector x of the length n is passed as an array to some GLPK API routine, the latter expects vector components to be placed in locations x[1], x[2], . . . , x[n], and the location x[0] normally is not used.

To avoid indexing errors it is most convenient and most reliable to declare the array x as follows:

    double x[1+n];
*/


#include "GLPK.h"
#include "Model.h"


GLPK::GLPK() : Solver() {
    
    //env = glp_init_env();
    problem = glp_create_prob();
    glp_init_iocp(&parm);
}

GLPK::~GLPK() {
    
    glp_free_env();
}

void GLPK::deleteAndRecreateProblem() {
    
    glp_delete_prob(problem);
    problem = glp_create_prob();
}

void GLPK::printSolverName() {
    printf("Solver used is GLPK\n");
}

int GLPK::getNumRows() {
    return glp_get_num_rows(problem);
}

int GLPK::getNumCols() {
    return glp_get_num_cols(problem);
}

void GLPK::changeObjectiveSense(bool isMax) {
    glp_set_obj_dir(problem, isMax ? GLP_MAX : GLP_MIN);
}


int GLPK::getNodeCount() {
    return 0;
}

/*
//print coefficients matrix
void printmat(vector<vector<double> > coefs) {
    unsigned int i, j;
    for (i = 0; i < coefs.size(); ++i) {
        for (j = 0; j < coefs.size(); ++j) {
            printf("%f ", coefs[i][j]);
        }
        printf("\n");
    }
}
*/



/**
 * lower      -> lower bound of variable
 * upper      -> upper bound of variable
 * obj        -> objective function coefficient
 * name       -> if not empty set the variable name
 */
void GLPK::addVariable(const double lower, const double upper, const double obj, string name) {

    int new_col;
    new_col = glp_add_cols(problem, 1);
    glp_set_col_name(problem, new_col, name.c_str());
    if (lower == upper) {
    glp_set_col_bnds(problem, new_col, GLP_FX, lower, upper);
    }
    else {
    glp_set_col_bnds(problem, new_col, GLP_DB, lower, upper);
    }

    glp_set_obj_coef(problem, new_col, obj);
    
    //TODO
    //deal with name == NULL

    addKey(name, new_col);
}

void GLPK::setVariableWarmStart(string colName, double value) {}

void GLPK::setVariablesWarmStart(vector<string> colNames, vector<double> values) {}

void GLPK::refineMIPStart() {}



/**
 * numCols    -> number of variables to be added
 * lower      -> array of size (numCols), lower bound of variables
 * upper      -> array of size (numCols), upper bound of variables
 * obj        -> Array of size (numCols), objective function coefficients
 * name       -> if not empty set the variable name (includes index in the end starting from zero)
 */
void GLPK::addVariables(int numCols, const double lower, const double upper, const double *obj, string& name) {}



/**
 * numCols    -> number of variables to be added
 * ub         -> upper bound of all variables
 * lb         -> lower bound of all variables
 * obj        -> Array of size (numCols), objective function coefficients
 * name       -> if not empty set the variable name (includes index in the end starting from zero)
 */
void GLPK::addIntegerVariables(int numCols, double lb, double ub, const double* obj, string& name) {}

void GLPK::addIntegerVariable(const double lower, const double upper, const double obj, string name) {
    
    int new_col;
    new_col = glp_add_cols(problem, 1);
    glp_set_col_name(problem, new_col, name.c_str());
    glp_set_col_bnds(problem, new_col, GLP_DB, lower, upper);
    glp_set_obj_coef(problem, new_col, obj);
    glp_set_col_kind(problem, new_col, GLP_IV);

    //TODO
    //deal with name == NULL

    addKey(name, new_col);
}

/* obj      -> objective function coefficient
 * name     -> if not empty, set variable name
 */

void GLPK::addBinaryVariable(const double obj, string name) {
    
    int new_col;
    new_col = glp_add_cols(problem, 1);
    glp_set_col_name(problem, new_col, name.c_str());
    glp_set_col_bnds(problem, new_col, GLP_DB, 0, 1);
    glp_set_obj_coef(problem, new_col, obj);
    glp_set_col_kind(problem, new_col, GLP_BV);
    
    
    //TODO
    //deal with name == NULL
    
    
    addKey(name, new_col);
}


/**
 * numCols    -> number of variables to be added
 * obj        -> Array of size (numCols), objective function coefficients
 * name       -> if not empty set the variable name (includes index in the end starting from zero)
 */
void GLPK::addBinaryVariables(int numCols, const double* obj, string& name) {

    int first_new_col;
    
    // this function returns the ordinal number of 
    // the first of the new added columns
    first_new_col = glp_add_cols(problem, numCols);
    
    for (int i = 0; i < numCols; i++) {
        string n = name + lex(i);
        glp_set_col_name(problem, first_new_col + i, n.c_str());
        glp_set_col_bnds(problem, first_new_col + i, GLP_DB, 0, 1);
        glp_set_obj_coef(problem, first_new_col + i, obj[i]);
        glp_set_col_kind(problem, first_new_col + i, GLP_BV);
        addKey(n, first_new_col + i);
    }
}

/**
 * colNames - Variable names of the corresponding constraint
 * elements - non zero coefficients
 * rhs      - right hand side
 * sense    - 'L': <=
 *            'E': ==
 *            'G': >=
 * name     - constraint name
 */
void GLPK::addRow(vector<string> colNames, vector<double> elements, double rhs, char sense, string name) {
  
    int numNonZero = (int)colNames.size();

    vector<int> col_indices(numNonZero+1); //+1 por causa do GLPK 
    vector<double> elements_a(numNonZero+1);
    for (int i = 0; i < numNonZero; i++) {
        elements_a[i+1] = elements[i];

        col_indices[i+1] = getColIndex(colNames[i].c_str());
        if (col_indices[i+1] == -1) printf("In addRow, colIndice was not found for variable %s. Is the name wrong?\n", colNames[i].c_str());
    }
    
    //for (int i = 0; i < numNonZero; i++) printf("%d\n", col_indices[i+1]);

    int new_row;
    new_row = glp_add_rows(problem, 1);
    glp_set_row_name(problem, new_row, name.c_str());
    if (sense == 'L') {
        glp_set_row_bnds(problem, new_row, GLP_UP, -1 * DBL_MAX, rhs);
    }
    else if (sense == 'E') {
        glp_set_row_bnds(problem, new_row, GLP_FX, rhs, rhs);
    }
    else if (sense == 'G') {
        glp_set_row_bnds(problem, new_row, GLP_LO, rhs, DBL_MAX);
    }

    //set coeficients
    glp_set_mat_row(problem, new_row, numNonZero, &col_indices[0], &elements_a[0]); 

    //TODO
    //deal with name == NULL
}

void GLPK::setPriorityInBranching(vector<string> colNames, int priority) {}

void GLPK::setPriorityInBranching(vector<string> colNames, vector<int> priorities) {}

void GLPK::relax() {}

void GLPK::doSolve() {
    status = glp_intopt(problem, &parm);
}

int GLPK:: getStatus() {
    return status;
}

double GLPK::getObjValue() {
    double objValue = 0;
    objValue = glp_get_obj_val(problem);
    return objValue;
}

double GLPK::getBestBound() { return 0; }

void GLPK::getColSolution() {
    int numCols = getNumCols();
    colSolution.resize(numCols);
    for (int i = 0; i < numCols; i++) {
        colSolution[i] = glp_get_col_prim(problem, i+1);
    }
    // return colSolution;
}

// PARAMS

void GLPK::setLPMethod(int lp) {
    //  1 - Primal
    //  2 - Dual
    
    // if (lp == 1) parm.meth = GLP_PRIMAL;
    // else if (lp == 2) parm.meth = GLP_DUAL;
}

 // in milliseconds
void GLPK::setTimeLimit(double time) {
    if (time > 0) {
        parm.tm_lim = time;
    }
}

// Nao achei respectiva função no GLPK
void GLPK::setNodeLimit(int lim) {}

void GLPK::setLPTolerance(double tolerance) {}

void GLPK::setMIPTolerances(double tolerance) {}

void GLPK::setRandomSeed(int seed) {}

void GLPK::setNumericalEmphasis(int value) {}

void GLPK::enablePresolve(bool enable) {
    if (enable) parm.presolve = GLP_ON;
}

void GLPK::disableDefaultCuts(bool disable) {}

void GLPK::setSolverCuts(int solverCuts, int clique, int cover, int disj, int landp, int flowcover, int flowpath, int gomory, int gub, int implbd, int mir, int mcf, int zerohalf) {}

void GLPK::setMIPEmphasis(int t) {}

void GLPK::setSolverParallelism (int t, int m) {}

void GLPK::setSolverLocalBranching(int t) {}

void GLPK::setBranchingPolicy(int t) {}

void GLPK::setNodeHeuristic(int t) {}

void GLPK::setProbingLevel(int t) {}


// DEBUG

void GLPK::debugInformation(int debug) {}

void GLPK::debugLevel(int debugLevel) {}

void GLPK::exportModel(const char* filename) {
    glp_write_lp(problem, NULL, filename);
}


///////////////////////////////
//                           //
//                           //
// STATUS FUNCTIONS          //
///////////////////////////////

bool GLPK::solutionExists() {
    return isOptimal() || isSolutionLimit() || isMIPTimeLimitFeasible() || isBestNumerical() || status == GLP_FEAS;
}

bool GLPK::isOptimal() {
    return isIntegerOptimal() || status == GLP_OPT;
}

bool GLPK::isIntegerOptimal() {
    return status == GLP_OPT;
}

bool GLPK::isInfeasible() {
    return status == GLP_INFEAS || status == GLP_NOFEAS;
}

bool GLPK::isInfeasibleDueToScaling() { return 0; }

bool GLPK::isUnbounded() {
    return status == GLP_UNBND;
}

bool GLPK::isInfeasibleOrUnbounded() { return 0; }

bool GLPK::isSolutionLimit() {
    return status;
}

bool GLPK::isTimeLimit() {
    return status == GLP_ETMLIM || isMIPTimeLimitFeasible() ||
        isMIPTimeLimitInfeasible();
}

bool GLPK::isMIPTimeLimitFeasible() { return 0; }

bool GLPK::isMIPTimeLimitInfeasible() { return 0; }

bool GLPK::isObjectiveLimitReached() {
    //for the dual simplex only
    return status == GLP_EOBJLL || status == GLP_EOBJUL;
}

bool GLPK::isIterationLimitReached() {
    return status == GLP_EITLIM;
}

bool GLPK::isBestNumerical() { return 0; }

bool GLPK::isNumericalDifficulties() { return 0; }


///////////////////////////////////
//                               //
//                               //
//STATUS FUNCIONS                //
///////////////////////////////////




