include_directories(${OPW_SOURCE_DIR}/src)
link_directories(${OPW_BINARY_DIR}/src)

SET (Boost_USE_STATIC_LIBS    ON)
SET (Boost_USE_STATIC_RUNTIME ON)
find_package(Boost COMPONENTS)

find_package(CPLEX)
find_package(GLPK)



add_executable(${OPW_COMPILED} 
      main.cc
      Util.h                  Util.cc
      Option.h                Option.cc
      Options.h               Options.cc
      Data.h                  Data.cc
      Execute.h               Execute.cc
      Model.h                 Model.cc
      Solver.h                Solver.cc

      # solvers
      CPLEX.h                 CPLEX.cc
      GLPK.h                  GLPK.cc
      
      Solution.h              Solution.cc
      
      # models
      DataCapitalBudgeting.h  DataCapitalBudgeting.cc
      ModelCapitalBudgeting.h ModelCapitalBudgeting.cc
      )

target_link_libraries(${OPW_COMPILED} m)
target_link_libraries(${OPW_COMPILED} pthread)
target_link_libraries(${OPW_COMPILED} ${Boost_LIBRARIES})
target_link_libraries(${OPW_COMPILED} cplex-library)
target_link_libraries(${OPW_COMPILED} cplex-concert)
target_link_libraries(${OPW_COMPILED} glpk)
target_link_libraries(${OPW_COMPILED} ilocplex)
target_link_libraries(${OPW_COMPILED} dl)
