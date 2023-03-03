set(HEADERS World.h 
ASCII/Plate.h  
ASCII/Char.h 
ASCII/PlateRenderer.h 
ASCII/ContextMenuPlate.h ASCII/DebugPlate.h ASCII/InventoryPlate.h ASCII/UIPlate.h
Actions/IAction.h Actions/LootAction.h Actions/WalkAction.h Actions/EatAction.h
Core/InputManager.h 
Core/FileSystem.h 
Core/Globals.h 
Camera.h Player.h 
Inventory/Entity.h Inventory/IItem.h Inventory/Inventory.h)

set(SOURCES main.cpp 
World.cpp 
ASCII/Plate.cpp 
ASCII/Char.cpp 
ASCII/PlateRenderer.cpp 
ASCII/ContextMenuPlate.cpp ASCII/DebugPlate.cpp ASCII/InventoryPlate.cpp ASCII/UIPlate.cpp 
Actions/LootAction.cpp Actions/WalkAction.cpp Actions/EatAction.cpp
Core/FileSystem.cpp 
Core/InputManager.cpp 
Core/Globals.cpp 
Camera.cpp 
Player.cpp 
Inventory/Inventory.cpp)

add_executable(lombie-game ${HEADERS} ${SOURCES})
set_property(TARGET lombie-game PROPERTY CXX_STANDARD 20)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

target_link_libraries(lombie-game PUBLIC NuakeRenderer)
target_include_directories(lombie-game PUBLIC ../Dependencies/NuakeRenderer/ ../Vendors/)