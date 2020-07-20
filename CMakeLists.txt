cmake_minimum_required(VERSION 3.10.0)

#include(cmake/gate/cmake/HunterGate.cmake)
#option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
#HunterGate(
#    URL "https://github.com/cpp-pm/hunter/archive/v0.23.261.tar.gz"
#    SHA1 "1540dad7b97c849784a09e8c452ba811c9f71ba2"
#    LOCAL
#)
project(mobagen)

#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")
#
#set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
#
#include(${CP_CMAKE_DIR}/macros.cmake)
#
#IF (ANDROID)
#  set(HIDAPI OFF CACHE BOOL "" FORCE)
##  include(${CP_CMAKE_DIR}/android.cmake)
#ENDIF ()

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
#
#LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_subdirectory(deps)

set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl/include )
set ( SDL2_LIBRARY SDL2 )

#find_library(SDL2 SDL2)
#include_directories(${SDL2_INCLUDE_DIR})
#add_library(main SHARED main.cpp)
#target_sources(main PRIVATE main.cpp)
#target_link_libraries(main SDL2 ${SDL2_LIBRARY})

#set(ENGINE_LIBS
#    ${SDL2_LIBRARY}
#    )
#
#set(ENGINE_INCLUDES
#    ${SDL2_INCLUDE_DIR}
#    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
#    )
#
#IF (EMSCRIPTEN)
#
#ELSEIF(ANDROID)
#  add_definitions( -DGLES2=1 )
#ELSE()
#  find_package(OpenGL REQUIRED)
#ENDIF()

#include_directories(${ENGINE_INCLUDES})

#ADD_SUBDIRECTORY(engine)

ADD_SUBDIRECTORY(game)