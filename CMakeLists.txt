cmake_minimum_required(VERSION 2.8)
project(OPTLIB)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)



if(DEFINED SSD_COMPILED)
  set(OPTLIB_EXTERNAL_BUILD 1)
else()
  set(OPTLIB_COMPILED optlib)
endif()

# Static so I can copy the executable to another version
# Check link for other possible options:
#
# http://stackoverflow.com/questions/13636513/linking-libstdc-statically-any-gotchas
#
if(MSVC)
	set(CMAKE_CXX_FLAGS "-O2 -EHsc")
	# get rid of useless warnings
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CLANG TRUE)
  message("CLANG ")
  set(CMAKE_CXX_FLAGS "-stdlib=libc++ -std=c++11")
else()
	set(CMAKE_CXX_FLAGS "-g -Wall -O2 -static-libstdc++ -static-libgcc -std=c++11")
endif()

# Output file is located in the bin directory under the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(src)
