cmake_minimum_required(VERSION 3.0)
project(LudumDare43)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/EntityComponentMetaSystem/src)
    message(FATAL_ERROR "EntityComponentMetaSystem is missing!\nPlease update \
the EntityComponentMetaSystem submodule by running 'git submodule init' and \
'git submodule update'!")
endif()
if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/GameDevTools/src)
    message(FATAL_ERROR "EntityComponentMetaSystem is missing!\nPlease update \
the EntityComponentMetaSystem submodule by running 'git submodule init' and \
'git submodule update'!")
endif()

set(LD43_SOURCES
    src/main.cpp
    GameDevTools/src/GDT/CollisionDetection.cpp
    GameDevTools/src/GDT/GameLoop.cpp
)

add_executable(LD43 ${LD43_SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -D NDEBUG")

find_package(SFML 2 REQUIRED
    COMPONENTS audio network graphics window system)

target_include_directories(LD43 PUBLIC
    ${SFML_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/EntityComponentMetaSystem/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/GameDevTools/src/
)

target_link_libraries(LD43
    sfml-audio sfml-graphics sfml-window sfml-system)
