cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV 3 REQUIRED)

add_definitions ("-Wall")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable (focus main.cpp common.cpp)

target_link_libraries(focus ${OpenCV_LIBS})

