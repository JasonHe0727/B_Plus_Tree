cmake_minimum_required (VERSION 2.8)
project(B_Plus_Tree)
aux_source_directory(. DIRSRC)
add_executable(B_Plus_Tree ${DIRSRC}) 

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
