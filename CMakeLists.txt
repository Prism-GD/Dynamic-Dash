cmake_minimum_required(VERSION 3.22)
project(dynamic_dash_native LANGUAGES CXX)

add_library(dynamic_dash SHARED src/dynamic_dash.cpp)
target_include_directories(dynamic_dash PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(dynamic_dash PUBLIC cxx_std_17)
target_compile_options(dynamic_dash PRIVATE -Wall -Wextra -Wpedantic)
