cmake_minimum_required(VERSION 3.15.3)

MESSAGE(STATUS "MSYS=${MSYS}")
MESSAGE(STATUS "CYGWIN=${CYGWIN}")
MESSAGE(STATUS "MINGW=${MINGW}")
MESSAGE(STATUS "WIN32=${WIN32}")

#CHECK MINGW
IF(NOT DEFINED MINGW)
  SET(MINGW OFF)
ENDIF()

# check if mingw
IF("${CMAKE_GENERATOR}" MATCHES "(M|m?)in(G|g?)(W|w?)")
  SET(MINGW ON)
  MESSAGE(STATUS "MinGW Detected")
ENDIF()

# CHECK OR APPLE MACHINE
IF(NOT DEFINED APPLE)
  set(APPLE OFF)
  MESSAGE(STATUS "NOT APPLE MACHINE")
ENDIF()

find_program(LSB_RELEASE_EXEC lsb_release)
if(LSB_RELEASE_EXEC)
  execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
          OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
          OUTPUT_STRIP_TRAILING_WHITESPACE
          )
  IF(LSB_RELEASE_ID_SHORT)
    message(STATUS "ubuntu detected")
  ENDIF()
ENDIF()

set (HUNTER_SKIP_LOCK ON CACHE BOOL "HUNTER_SKIP_LOCK")
include(cmake/gate/cmake/HunterGate.cmake)
option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.248.tar.gz"
        SHA1 "a637ec52a1b82beb5f55ab4aa75fac30bcee8904"
)
project(Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
include(${CP_CMAKE_DIR}/macros.cmake)

# read build configs
IF(NOT EXISTS "${PROJECT_SOURCE_DIR}/buildconfig.mk")
  message(FATAL_ERROR "The file buildconfig.mk must exists to load build configurations from it.")
ENDIF()

ReadVariables(buildconfig.mk)

message(STATUS "USE_BULLET from config file: ${USE_BULLET}")
message(STATUS "USE_GDCM from config file: ${USE_GDCM}")
message(STATUS "USE_CURL from config file: ${USE_CURL}")

IF(APPLE)
  add_definitions(-DAPPLE)
ENDIF()

IF(USE_CURL)
  message(STATUS "######################### ADDING OpenSSL #######################################")
  hunter_add_package(OpenSSL)
  find_package(OpenSSL REQUIRED)

  message(STATUS "######################### ADDING CURL #######################################")
  hunter_add_package(CURL)
  find_package(CURL CONFIG REQUIRED)

  message(STATUS "######################### ADDING CPR - CURL for PEOPLE #######################################")
  hunter_add_package(cpr)
  find_package(cpr CONFIG REQUIRED)

  add_definitions(-DUSE_CURL)
ENDIF()


#if (USE_CURL AND MINGW)
#  find_package(CURL REQUIRED)
#endif ()
#
#IF(USE_CURL AND APPLE)
#  find_program (perl_path NAMES perl perl.exe)
#  IF (NOT perl_path)
#    message(FATAL_ERROR "You must install PERL and add it to PATH in order to build CURL")
#  ELSE()
#    message(STATUS "Perl was found in PATH: ${perl_path}")
#  ENDIF()
#
#  message(STATUS "######################### ADDING OPENSSL #######################################")
#  hunter_add_package(OpenSSL)
#  find_package(OpenSSL REQUIRED)
#
#  message(STATUS "######################### ADDING CURL #######################################")
#  hunter_add_package(CURL)
#  find_package(CURL CONFIG REQUIRED)
#ENDIF()

# zlib support
message(STATUS "######################### ADDING ZLIB #######################################")
hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)

message(STATUS "######################### ADDING MINIZIP #######################################")
hunter_add_package(minizip)
find_package(minizip CONFIG REQUIRED)

IF(USE_BULLET)
  message(STATUS "######################### ADDING BULLET #######################################")
  hunter_add_package(bullet)
  find_package(bullet CONFIG REQUIRED)
ENDIF()

set(LIBC ON CACHE BOOL "LIBC")

IF(NOT EMSCRIPTEN)
  message(STATUS "######################### ADDING SDL2 #######################################")
  hunter_add_package(SDL2)
  find_package(SDL2 CONFIG REQUIRED)
ENDIF()

set(NOMINMAX ON CACHE BOOL "workaround for minmax problem with windows.h")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_STATIC_LIBS TRUE)
set(BUILD_SHARED_LIBS FALSE)

IF(ANDROID)
  include(${CP_CMAKE_DIR}/android.cmake)
  add_definitions(-DSDL_JOYSTICK=0) # to avoid bugs with android + joystick
ENDIF ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_definitions(-DGLEW_STATIC)
add_definitions(-UGLEW_BUILD)

add_subdirectory( dependencies )

#message(STATUS "######################### ADDING ASSIMP #######################################")
#hunter_add_package(Assimp)
#find_package(Assimp CONFIG REQUIRED)

IF(USE_GDCM)
  message(STATUS "######################### ADDING GDCM #######################################")
  if(POLICY CMP0024)
    cmake_policy(SET CMP0024 OLD)
  endif()
  find_package( GDCM REQUIRED PATHS ${CMAKE_CURRENT_BINARY_DIR}/dependencies/gdcm/ )

  SET(GDCM_LIBRARIES
          gdcmCommon
          gdcmDICT
          gdcmDSED
          gdcmIOD
          gdcmMSFF
          gdcmMEXD
          gdcmjpeg8
          gdcmjpeg12
          gdcmjpeg16
          gdcmexpat
          gdcmopenjp2
          gdcmcharls
          gdcmzlib
          #gdcmuuid
          socketxx
          )
ENDIF()

set ( ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include )
set ( ASSIMP_LIBRARY assimp )

set(ENGINE_INCLUDES
        ${ASSIMP_INCLUDE_DIR}
        ${CMAKE_BINARY_DIR}/dependencies/assimp/include)

#set ( ASSIMP_LIBRARY Assimp::assimp )

add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
add_definitions(-DGLM_FORCE_SWIZZLE)

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/ )

set ( IMGUI_INCLUDE_DIRS
        ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/)

set ( IMGUI_LIBRARY imgui )

IF (EMSCRIPTEN)
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Engine/example/assets/ -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s TOTAL_MEMORY=536870912 -s USE_SDL=2 -std=c++14 -Oz")
  #SET(CMAKE_CXX_FLAGS "--closure 1 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -Oz ")
  SET(CMAKE_CXX_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=2")
  add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

  set(ENGINE_LIBS
          ${ASSIMP_LIBRARY}
          ${IMGUI_LIBRARY}
          ${GDCM_LIBRARIES}
          )

  set(ENGINE_INCLUDES
          ${ENGINE_INCLUDES}
          ${GLM_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
          ${IMGUI_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/engine/
          ${GDCM_INCLUDE_DIRS}
          )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/index.html ${CMAKE_BINARY_DIR}/bin/index.html COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/midasminer.html ${CMAKE_BINARY_DIR}/bin/midasminer.html COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/doceditor.html ${CMAKE_BINARY_DIR}/bin/doceditor.html COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/animation.html ${CMAKE_BINARY_DIR}/bin/animation.html COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/uploader.html ${CMAKE_BINARY_DIR}/bin/uploader.html COPYONLY)

ELSEIF(ANDROID)
  add_definitions( -DGLES2=1 )

  set(ENGINE_LIBS
          SDL2::SDL2
          SDL2::SDL2main
          ${ASSIMP_LIBRARY}
          ${IMGUI_LIBRARY}
          ${GDCM_LIBRARIES}
          )

  set(ENGINE_INCLUDES
          ${ENGINE_INCLUDES}
          ${GLM_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
          ${IMGUI_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/engine/
          ${GDCM_INCLUDE_DIRS}
          )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fPIC")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -fPIC")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
          SDL2::SDL2
          SDL2::SDL2main
          ${OPENGL_LIBRARY}
          ${ASSIMP_LIBRARY}
          ${IMGUI_LIBRARY}
          )
  set(ENGINE_INCLUDES
          ${ENGINE_INCLUDES}
          ${GLM_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
          ${IMGUI_INCLUDE_DIRS}
          ${CMAKE_CURRENT_SOURCE_DIR}/engine/
          )

  IF(USE_GDCM)
    SET(ENGINE_LIBS
            ${ENGINE_LIBS}
            ${GDCM_LIBRARIES}
            )
    SET(ENGINE_INCLUDES
            ${ENGINE_INCLUDES}
            ${GDCM_INCLUDE_DIRS}
            )
  ENDIF()
ENDIF()

IF(USE_BULLET)
  SET(ENGINE_LIBS
          ${ENGINE_LIBS}
          bullet::BulletCollision
          bullet::BulletDynamics
          bullet::BulletSoftBody
          bullet::LinearMath
          )
ENDIF()

SET(ENGINE_LIBS ${ENGINE_LIBS} ZLIB::zlib)

#IF(USE_CURL AND MINGW)
#  SET(ENGINE_INCLUDES ${ENGINE_INCLUDES} ${CURL_INCLUDE_DIR})
#  SET(ENGINE_LIBS ${ENGINE_LIBS} ${CURL_LIBRARIES})
#ELSEIF(USE_CURL AND APPLE)
#  SET(ENGINE_LIBS ${ENGINE_LIBS} CURL::libcurl OpenSSL::SSL OpenSSL::Crypto)
#ELSE()
#  SET(ENGINE_LIBS ${ENGINE_LIBS} CURL::libcurl BoringSSL::ssl BoringSSL::crypto)
#ENDIF()

IF(USE_CURL)
  SET(ENGINE_LIBS ${ENGINE_LIBS} CURL::libcurl OpenSSL::SSL OpenSSL::Crypto cpr::cpr)
ENDIF()

include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/examples )

IF (NOT ANDROID)
  option(BUILD_TESTS "BUILD TESTS" ON)
  IF (BUILD_TESTS)
    add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/tests )
  ENDIF ()
ENDIF ()
