cmake_minimum_required (VERSION 3.5)

set (CMAKE_CXX_STANDARD 11)

find_package(OpenCV 3 REQUIRED)

add_definitions ("-Wall")

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable (ant main.cpp)

target_link_libraries(ant ${OpenCV_LIBS})

