set(HEADERS World.h 
ASCII/Plate.h 
ASCII/Char.h
ASCII/PlateRenderer.h
Core/FileSystem.h)

set(SOURCES main.cpp 
World.cpp 
ASCII/Plate.cpp 
ASCII/Char.cpp
ASCII/PlateRenderer.cpp
Core/FileSystem.cpp)

add_executable(lombie-game ${HEADERS} ${SOURCES})
set_property(TARGET lombie-game PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

target_link_libraries(lombie-game PUBLIC NuakeRenderer)
target_include_directories(lombie-game PUBLIC ../Dependencies/NuakeRenderer/ ../Vendors/)