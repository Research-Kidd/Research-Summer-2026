cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT_DIR "/home/tristanallison/Research-Summer-2026/Research Students/Tristian Allison/Code/Tutorials/rt")

project(RayTracerTutorial)

file(GLOB sources ${CMAKE_SOURCE_DIR}/src/*.cc) # source files

add_executable(rt main.cc ${sources})

target_include_directories(rt PRIVATE ${CMAKE_SOURCE_DIR}/include)