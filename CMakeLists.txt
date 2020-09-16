cmake_minimum_required(VERSION 3.10.0)

include(cmake/gate/cmake/HunterGate.cmake)
option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.269.tar.gz"
    SHA1 "64024b7b95b4c86d50ae05b926814448c93a70a0"
    LOCAL
)
project(mobagen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
#
#set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")
#
#set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
#
#include(${CP_CMAKE_DIR}/macros.cmake)

add_subdirectory(deps)

IF(EMSCRIPTEN)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

  LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

  message(STATUS "emscripten build")
#  SET(CMAKE_CXX_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=2 -s USE_PTHREADS=1 --proxy-to-worker -s FETCH=1")
  SET(CMAKE_CXX_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=2 --proxy-to-worker -s FETCH=1")
  add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/index.html ${CMAKE_BINARY_DIR}/bin/index.html COPYONLY)
ELSE()
  set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/sdl/include )
  set ( SDL2_LIBRARY SDL2 )
ENDIF()

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

ADD_SUBDIRECTORY(engine)

ADD_SUBDIRECTORY(game)