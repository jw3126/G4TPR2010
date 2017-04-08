cmake_minimum_required(VERSION 3.5)
project(G4TPR2010)
set(CMAKE_CXX_STANDARD 14)


find_package(Geant4 REQUIRED ui_all vis_all)
include_directories(${PROJECT_SOURCE_DIR}/include)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)

# copy macro file for visualization init
configure_file(${PROJECT_SOURCE_DIR}/init.mac
        ${PROJECT_BINARY_DIR}/init.mac
        COPYONLY
        )


add_executable(G4TPR2010 main.cpp ${sources} ${headers})
target_link_libraries(G4TPR2010 ${Geant4_LIBRARIES})
