#include_directories(${OPTLIB_SOURCE_DIR}/src)
#link_directories(${OPTLIB_BINARY_DIR}/src)
find_package(CPLEX)


# Uncomment below if you plan to use Boost. No need to uncomment 
#   regex unless you also plan to use boost regex.
#SET (Boost_USE_STATIC_LIBS    ON)
#SET (Boost_USE_STATIC_RUNTIME ON)
#find_package(Boost COMPONENTS)
#find_package(Boost COMPONENTS regex REQUIRED)


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

      DataMotivatingProblem.h  DataMotivatingProblem.cc
      ModelMotivatingProblem.h ModelMotivatingProblem.cc

      DataKnapsackProblem.h  DataKnapsackProblem.cc
      ModelKnapsackProblem.h ModelKnapsackProblem.cc

      DataAssignmentProblem.h  DataAssignmentProblem.cc
      ModelAssignmentProblem.h ModelAssignmentProblem.cc

      DataConcreteMixerTruckRouting.h  DataConcreteMixerTruckRouting.cc
      ModelConcreteMixerTruckRouting.h  ModelConcreteMixerTruckRouting.cc
      )

# Added private defininition of throw_exception to Util.h
target_compile_definitions(${OPTLIB_COMPILED} PRIVATE BOOST_NO_EXCEPTIONS)

if(MSVC)
    target_compile_definitions(${OPTLIB_COMPILED} PRIVATE _DLL) # apparently required for DLL CRT 
	target_compile_definitions(${OPTLIB_COMPILED} PRIVATE IL_STD) 
endif()

target_link_libraries(${OPTLIB_COMPILED} cplex-library)
#target_link_libraries(${OPTLIB_COMPILED} cplex-concert)
target_link_libraries(${OPTLIB_COMPILED} ilocplex)

if(NOT MSVC)
	target_link_libraries(${OPTLIB_COMPILED} pthread)
	target_link_libraries(${OPTLIB_COMPILED} dl)
endif()


if(DEFINED OPTLIB_EXTERNAL_BUILD)
  add_custom_command(TARGET ${OPTLIB_COMPILED}  
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${OPTLIB_COMPILED}> ${OPTLIB_DESTINATIONDIR})	 
endif()

#target_link_libraries(${OPTLIB_COMPILED} m)
# Uncomment below if you plan to use Boost. No need to uncomment 
#   regex unless you also plan to use boost regex.
#target_link_libraries(${OPTLIB_COMPILED} boost_regex)
#target_link_libraries(${OPTLIB_COMPILED} ${Boost_LIBRARIES})
