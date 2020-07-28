# OPW

`opw` is a wrapper in C++ for modeling, implementing and solving optimization problems.

## Setup 

(1) Install one of the currently supported solvers: the IBM CPLEX and the GNU Linear Programming Kit (GLPK)

(2) Install the Boost C++ Libraries

## Building
```
$ opw/build$ cmake ..

$ opw/build$ make
```

## Running
```
Usage:
opw [input] [options]
```

To solve the Generalized Assigment Problem using GLPK with default options for the solver, simply run from inside the `build/` directory:

```
$ ./opw --input=../tests/GeneralizedAssignmentProblem/gap_test.txt --debug=2 --model=gap --solver=glpk
```
