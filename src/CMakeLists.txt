include_directories(${OPTLIB_SOURCE_DIR}/src)
link_directories(${OPTLIB_BINARY_DIR}/src)


# Uncomment below if you plan to use Boost. No need to uncomment 
#   regex unless you also plan to use boost regex.
#SET (Boost_USE_STATIC_LIBS    ON)
#SET (Boost_USE_STATIC_RUNTIME ON)
#find_package(Boost COMPONENTS)
#find_package(Boost COMPONENTS regex REQUIRED)

#find_library(SQLITE_LIBRARY_RELEASE sqlite3 VARIANT static)

find_package(CPLEX)
if (CPLEX_FOUND)
else ()
endif ()



add_executable(${OPTLIB_COMPILED} 
      main.cc
      Util.h                  Util.cc
      Option.h                Option.cc
      Options.h               Options.cc
      Data.h                  Data.cc
      Execute.h               Execute.cc
      Model.h                 Model.cc
      Solver.h                Solver.cc
      CPLEX.h                 CPLEX.cc
      Solution.h              Solution.cc
      
      DataCapitalBudgeting.h  DataCapitalBudgeting.cc
      ModelCapitalBudgeting.h ModelCapitalBudgeting.cc
      )

target_link_libraries(${OPTLIB_COMPILED} m)
#target_link_libraries(${OPTLIB_COMPILED} ${SQLITE_LIBRARY_RELEASE})
#target_link_libraries(${OPTLIB_COMPILED} sqlite3)
target_link_libraries(${OPTLIB_COMPILED} pthread)
# Uncomment below if you plan to use Boost. No need to uncomment 
#   regex unless you also plan to use boost regex.
#target_link_libraries(${OPTLIB_COMPILED} boost_regex)
#target_link_libraries(${OPTLIB_COMPILED} ${Boost_LIBRARIES})
target_link_libraries(${OPTLIB_COMPILED} cplex-library)
target_link_libraries(${OPTLIB_COMPILED} cplex-concert)
target_link_libraries(${OPTLIB_COMPILED} ilocplex)
target_link_libraries(${OPTLIB_COMPILED} dl)
