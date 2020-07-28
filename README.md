# opw

`opw` is a wrapper library in C++ for commercial and open source solvers

## Setup 

(1) Install at least one of the currently supported solvers: IBM CPLEX and GNU Linear Programming Kit (GLPK)

(2) Install Boost

## Building
```
$ opw/build$ cmake ..

$ opw/build$ make
```

## Running
```
Usage:
opw input [options]
```

To solve the Generalized Assigment Problem using GLPK with default options for the solver, simply run from inside the `build/` directory:

```
$ ./opw --input=../tests/GeneralizedAssignmentProblem/gap_test.txt --debug=2 --model=gap --solver=glpk
```
