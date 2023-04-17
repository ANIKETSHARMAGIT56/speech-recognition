cmake_minimum_required(VERSION 3.26.3)
project(a.out)

add_executable(${PROJECT_NAME} 
${CMAKE_SOURCE_DIR}/src/miniaudio.c
${CMAKE_SOURCE_DIR}/src/audio_functions.c
${CMAKE_SOURCE_DIR}/src/main.cpp
)
include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)
include_directories(${CMAKE_SOURCE_DIR}/include/)

find_library(MATH_LIB m)
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE m curl cpr crypto)