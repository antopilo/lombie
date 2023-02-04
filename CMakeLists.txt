cmake_minimum_required(VERSION 3.1...3.24)

project(lombi VERSION 0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Dependencies/NuakeRenderer)
add_subdirectory(lombie)
