
# Optimisation Library

[![Stars](https://img.shields.io/github/stars/cristianoarbex/optimisationLibrary)](https://img.shields.io/github/stars/cristianoarbex/optimisationLibrary)
[![Forks](https://img.shields.io/github/forks/cristianoarbex/optimisationLibrary)](https://img.shields.io/github/forks/cristianoarbex/optimisationLibrary)
[![Issues](https://img.shields.io/github/issues/cristianoarbex/optimisationLibrary)](https://img.shields.io/github/issues/cristianoarbex/optimisationLibrary)

A C++ interface for solving optimization models with solvers - only CPLEX currently implemented.

## About the library

The library is an implementation of a C++ system for solving optimization problems, for which configurations and calls are made to Solvers that return partial and final information regarding the solution of the problem.

### Main Technologies

* [ILOG CPLEX Optimization Studio](https://www.ibm.com/docs/en/icos/12.9.0?topic=cplex)
* [CMake](https://cmake.org/documentation/)

## Installation

### How to install

To install the application, follow the steps below:

1. Access the repository where the code is hosted:

> [optimisationLibrary - github](https://github.com/cristianoarbex/optimisationLibrary)

2. Click on the *Code* button, then click on *HTTPS* and copy the url provided.

3. Clone the repository in the directory you want:

  ```sh
  git clone {url copied}
  ```

## How to use

### Prerequisites

The following software must be installed on the machine that will perform the installation:

* Visual Studio
* CMake
* ILOG CPLEX Optimization Studio 12.10 or earlier

### How to run

The following steps must be followed:

1. Access the project directory via command line.

2. Access the *build* folder:
```sh
cd build
```

3. Run *CMake*:
```sh
cmake ..
```

4. Open *optlib.sln* file created in Visual Studio.

5. In *Configuration Manager*, select:
* optlib
* Release

6. Set optlib as startup project.

7. Build te solution.

8. Check if an executable file named *optlib.exe* has been created in the directory:
```sh
~/build/bin/Release/
```

9. If the cmake's log shows some error, configure it in the visual studio:
* Go to *Build -> Configuration Manager* and in *Active soluction platform* select *<New...>*.
* Fill:
```sh
Type or select the new platform = x64
Copy settings from: <Empty>
```
* Click *Ok*
* Select *x64* as the active solution and select *optlib* and *ZERO_CHECK*
* Click *Close*
* Right click in the project *optlib*, then *Properties*
* Go to Configuration Properties -> C/C++ -> General -> Additional Include Directories and add:
```sh
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\cplex\include
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\concert\include
```
> **WARNING**: <version> is the CPLEX Studio version
* Go to Configuration Properties -> Linker -> Input -> Additional Dependencies and add:
```sh
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\cplex\lib\x64_windows_msvc14\stat_mda\cplex<version>.lib
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\cplex\lib\x64_windows_msvc14\stat_mda\ilocplex.lib
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\concert\lib\x64_windows_msvc14\stat_mda\concert.lib
```
> **WARNING**: <version> is the CPLEX Studio version
* Go to Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions and add:
```sh
WIN32
_CONSOLE
IL_STD
_CRT_SECURE_NO_WARNINGS
```
* Click *Apply* and *Ok*
10. Run the application:
```sh
bin/Release/optlib.exe {options}
```
Or
```sh
x64/Release/optlib.exe {options}
```

*Options*
* settings_file: Input file with options. If not empty, only some other options such as 'output' or 'debug' are allowed [Default: ""].
* output: Output file where solution will be written [Default: ""].
* debug: Level of debug information [0-4, 0 means no debug] [Default: 2].
* first_node_only: Solve only first node [Default: 0].
* lp_filename: Name of the LP exported file if export_model = 1 [Default: "bc_model.lp"].
* export_model: If (1) exports model to lp file [Default: 0].
* export_cplex_cuts: Number of intermediate models with cplex cuts to export to lp file [Default: 0].
* input: Input file [Default: ""].
* output: Output file where solution will be written [Default: ""].
* model: Which model to solve [Default: "toy"].
* solver: Choose which solver to use [Default: cplex].
* solver_debug_level: Choose the solver debug level [Default: 2].
* time_limit: Time limit for the solver (in seconds, if zero time limit is not set) [Default: 21600].
* presolve: Presolve is (0) disabled or (1) enabled [Default: 1].
* mip_emphasis: MIP emphasis (0 to 4) [Default: 0].
* lp_method: Set LP method [Default: 0].
* feasibility_pump: Solver feasibility pump heuristic [Default: 0].
* solver_random_seed: Solver random seed. If 0 do not set [Default: 0].
* probing_level: MIP probing lebel (-1 to 3) [Default: 1].
* node_heuristic: MIP node heuristic frequency (-1 to inf) [Default: 0].
* branching_policy: From -1 to 4, choose branching policy [Default: 0].
* solver_local_branching: Solver local branching routine [Default: 0].
* solver_parallelism: (1) on, (0) off, (2) non-deterministic [Default: 0].
* solver_threads: Number of threads [Default: 0].
* mip_strategy: Dynamic switch or branch-and-cut [Default: 0 (auto)].
* solver_cuts: All cuts are (-1) disabled, (0) automatic or (1-3) enabled [Default: -1].
* gomory_cuts: (-1 to 2) Overrides or (-2) not the option for gomory fractional cuts [Default: -2].
* zerohalf_cuts: (-1 to 2) Overrides or (-2) not the option for zero-half cuts [Default: -2].
* cover_cuts: (-1 to 3) Overrides or (-2) not the option for cover cuts [Default: -2].
* landp_cuts: (-1 to 3) Overrides or (-2) not the option for lift-and-project cuts [Default: -2].
* mir_cuts: (-1 to 2) Overrides or (-2) not the option for MIR cuts [Default: -2].
* disj_cuts: (-1 to 3) Overrides or (-2) not the option for disjunctive cuts [Default: -2].
* flowcover_cuts: (-1 to 2) Overrides or (-2) not the option for flow cover cuts [Default: -2].
* mcf_cuts: (-1 to 2) Overrides or (-2) not the option for MCF cuts [Default: -2].
* clique_cuts: (-1 to 3) Overrides or (-2) not the option for cliques cuts [Default: -2].
* flowpath_cuts: (-1 to 2) Overrides or (-2) not the option for flow path cuts [Default: -2].
* gub_cuts: (-1 to 2) Overrides or (-2) not the option for GUB cuts [Default: -2].
* implbd_cuts: (-1 to 2) Overrides or (-2) not the option for implied bound cuts [Default: -2].

*Examples*
```sh
bin/Release/optlib.exe --input=aaa 
```

```sh
bin/Release/optlib.exe --input=aaa  --debug=1 
```

```sh
bin/Release/optlib.exe --input=aaa --export_model=1
```

```sh
bin/Release/optlib.exe --input=aaa --model=motivating
```

> **WARNING**: The input parameter is mandatory

### How to debug

The following steps must be followed:

1. Open *optlib.sln* file created in Visual Studio.

2. In *Configuration Manager*, select:
* optlib
* Debug

3. Set optlib as startup project.

4. Open optlib debug properties. In *Debugging*, fill *Command Arguments* with the options you want to send by parameters and click *Ok*.

5. Click in *Local Windows Debugger*.

6. If the cmake's log shows some error, configure it in the visual studio:
* Go to *Build -> Configuration Manager*.

* Select *x64* as the active solution and select *optlib* and *ZERO_CHECK*

* Click *Close*

* Right click in the project *optlib*, then *Properties*

* Go to Configuration Properties -> C/C++ -> General -> Additional Include Directories and add:
```sh
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\cplex\include
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\concert\include
```
> **WARNING**: <version> is the CPLEX Studio version

* Go to Configuration Properties -> Linker -> Input -> Additional Dependencies and add:
```sh
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\cplex\lib\x64_windows_msvc14\stat_mda\cplex<version>.lib
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\cplex\lib\x64_windows_msvc14\stat_mda\ilocplex.lib
C:\Program Files\IBM\ILOG\CPLEX_Studio<version>\concert\lib\x64_windows_msvc14\stat_mda\concert.lib
```
> **WARNING**: <version> is the CPLEX Studio version

* Go to Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions and add:
```sh
WIN32
_CONSOLE
IL_STD
_CRT_SECURE_NO_WARNINGS
```

* Click *Apply* and *Ok*

7. Click in *Local Windows Debugger*.

### TODO list

1. Adapt this documentation for the differences between compiling in Linux and Windows.
2. Make sure the library works with CPLEX 20+ in both Linux and Windows.
3. Make an user guide to add models.
