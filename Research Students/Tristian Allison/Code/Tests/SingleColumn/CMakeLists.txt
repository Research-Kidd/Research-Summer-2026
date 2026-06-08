cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(SingleColumn) # Any name is fine

find_package(Geant4 REQUIRED ui_all vis_all) # Necessary since the entire program is build off of this

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include) # points to directory which holds .h, .hh, .hpp

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc) # find all source files to be included in compilation

file(GLOB MACRO_FILES "macros/*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${CMAKE_BINARY_DIR}/)

add_executable(sim main.cc ${sources}) # creates the executable file
target_link_libraries(sim ${Geant4_LIBRARIES}) # link libraries to executable

add_custom_target(SingleColumn DEPENDS sim) # project depends on exectuble