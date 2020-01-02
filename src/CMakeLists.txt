include_directories(${MMST_SOURCE_DIR}/src)
link_directories(${MMST_BINARY_DIR}/src)


SET (Boost_USE_STATIC_LIBS    ON)
SET (Boost_USE_STATIC_RUNTIME ON)
find_package(Boost COMPONENTS)
#find_package(Boost COMPONENTS regex REQUIRED)

#find_library(SQLITE_LIBRARY_RELEASE sqlite3 VARIANT static)

find_package(CPLEX)
if (CPLEX_FOUND)
else ()
endif ()



add_executable(${MMST_COMPILED} 
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

target_link_libraries(${MMST_COMPILED} m)
#target_link_libraries(${MMST_COMPILED} ${SQLITE_LIBRARY_RELEASE})
#target_link_libraries(${MMST_COMPILED} sqlite3)
target_link_libraries(${MMST_COMPILED} pthread)
#target_link_libraries(${MMST_COMPILED} boost_regex)
target_link_libraries(${MMST_COMPILED} ${Boost_LIBRARIES})
target_link_libraries(${MMST_COMPILED} cplex-library)
target_link_libraries(${MMST_COMPILED} cplex-concert)
target_link_libraries(${MMST_COMPILED} ilocplex)
target_link_libraries(${MMST_COMPILED} dl)
