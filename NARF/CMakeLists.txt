cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(iterative)

find_package(PCL 1.3 REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

add_executable (kinect main.cpp kinect.cpp kinect.h)
target_link_libraries (kinect ${PCL_LIBRARIES})
