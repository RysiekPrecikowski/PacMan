cmake_minimum_required(VERSION 3.17)
project(cpp)

set(CMAKE_CXX_STANDARD 20)




add_executable(cpp
        src/main.cpp
        headers/Engine.h
        src/Engine.cpp
        src/utils/console.cpp
        headers/console.h
        headers/game_state.h
        src/states/state_manager.cpp
        headers/state_manager.h
        src/states/state_playing.cpp
        headers/state_playing.h
        src/map_elements/Resources.cpp
        headers/Resources.h
        src/map_elements/labirynth.cpp
        headers/labirynth.h
        src/map_elements/Entity.cpp
        headers/Entity.h
        src/creatures/PacMan.cpp
        headers/PacMan.h
        headers/Directions.h
        src/creatures/Ghost.cpp
        headers/Ghost.h
        src/creatures/All_ghosts.cpp
        headers/All_ghosts.h
        src/creatures/Moving.cpp
        headers/Moving.h)
target_include_directories(cpp PRIVATE headers)
set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(cpp ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
