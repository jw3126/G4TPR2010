cmake_minimum_required(VERSION 3.5)
project(G4TPR2010)
set(CMAKE_CXX_STANDARD 14)


# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

find_package(Geant4 REQUIRED gdml ui_all vis_all)
include_directories(${PROJECT_SOURCE_DIR}/include)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)


# copy macro file for visualization init
configure_file(${PROJECT_SOURCE_DIR}/init.mac
        ${PROJECT_BINARY_DIR}/init.mac
        COPYONLY
        )

configure_file(${PROJECT_SOURCE_DIR}/geometry.gdml
        ${PROJECT_BINARY_DIR}/geometry.gdml
        COPYONLY
        )

add_library(CommonSourceCode ${sources} ${headers})
target_link_libraries(CommonSourceCode ${Geant4_LIBRARIES})
add_executable(G4TPR2010 main.cpp) # ${sources} ${headers})
#target_link_libraries(G4TPR2010 ${Geant4_LIBRARIES})
target_link_libraries(G4TPR2010 CommonSourceCode)

# Make test executable
file(GLOB TEST_SOURCES test/test_util.cpp)

add_executable(TESTS test/catch_main.cpp ${TEST_SOURCES} test/catch_main.cpp test/test_util.cpp)
target_link_libraries(TESTS Catch)
target_link_libraries(TESTS CommonSourceCode)