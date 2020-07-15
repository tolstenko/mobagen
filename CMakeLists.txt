cmake_minimum_required(VERSION 3.14.3)

#set (HUNTER_SKIP_LOCK ON CACHE BOOL "HUNTER_SKIP_LOCK")
include(cmake/gate/cmake/HunterGate.cmake)
option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.261.tar.gz"
    SHA1 "1540dad7b97c849784a09e8c452ba811c9f71ba2"
)
project(mobagen)

IF(NOT EMSCRIPTEN)
  message(STATUS "######################### ADDING SDL2 #######################################")
  hunter_add_package(SDL2)
  find_package(SDL2 CONFIG REQUIRED)
ENDIF()

