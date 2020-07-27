cmake_minimum_required(VERSION 2.8)

# Use a static runtime for MSVC build (http://www.vtk.org/Wiki/CMake_FAQ).
set(CMAKE_USER_MAKE_RULES_OVERRIDE
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/cxx_flag_overrides.cmake)

project(OPW)

#set(OPW_VERSION_MAJOR 0)
#set(OPW_VERSION_MINOR 1)
#set(PACKAGE_VERSION ${OPW_VERSION_MAJOR}.${OPW_VERSION_MINOR})

#set(OPW_COMPILED ssd${OPW_VERSION_MAJOR}${OPW_VERSION_MINOR})
set(OPW_COMPILED opw)

# Static so I can copy the executable to another version
# Check link for other possible options:
#
# http://stackoverflow.com/questions/13636513/linking-libstdc-statically-any-gotchas
#
set(CMAKE_CXX_FLAGS "-g -Wall -O2 -static-libstdc++ -static-libgcc -std=c++11")
#set(CMAKE_CXX_FLAGS "-g -Wall -O2 -std=c++11")

# Output file is located in build folder
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)


add_subdirectory(src)
