cmake_minimum_required(VERSION 3.21.3)

project(Histogram_Test)

add_executable(${PROJECT_NAME} main.c)

add_subdirectory(Histogram)

include_directories(${PROJECT_NAME} Histogram/src)

target_link_directories(${PROJECT_NAME} PRIVATE Histogram)

target_link_libraries(${PROJECT_NAME} Histogram)