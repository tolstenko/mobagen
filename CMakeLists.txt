cmake_minimum_required(VERSION 3.10.2)

MESSAGE(STATUS "MSYS=${MSYS}")
MESSAGE(STATUS "CYGWIN=${CYGWIN}")
MESSAGE(STATUS "MINGW=${MINGW}")
MESSAGE(STATUS "WIN32=${WIN32}")

#CHECK MINGW
IF(NOT DEFINED MINGW)
  SET(MINGW OFF)
ENDIF()
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
        URL "https://github.com/ruslo/hunter/archive/v0.23.29.tar.gz"
        SHA1 "797be99a8a4f4666766257563fad8aa3aa032da2"
)
project(Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
include(${CP_CMAKE_DIR}/macros.cmake)

# read build configs
IF(NOT EXISTS "${PROJECT_SOURCE_DIR}/buildconfig.txt")
  message(FATAL_ERROR "The file buildconfig.txt must exists to load build configurations from it.")
ENDIF()

IF(NOT DEFINED ${USE_BULLET})
  readSettingFile("USE_BULLET=" "ON" STRING_RESULT )
  string(COMPARE EQUAL "${STRING_RESULT}" "ON" is_equal)
  if(is_equal)
    set(USE_BULLET ON)
  else()
    set(USE_BULLET OFF)
  endif()
  message(STATUS "USE_BULLET from config file: ${USE_BULLET}")
ENDIF()

IF(NOT DEFINED ${USE_GDCM})
  readSettingFile("USE_GDCM=" "OFF" STRING_RESULT )
  string(COMPARE EQUAL "${USE_GDCM}" "ON" is_equal)
  if(is_equal)
    set(USE_GDCM ON)
  else()
    set(USE_GDCM OFF)
  endif()
  message(STATUS "USE_GDCM from config file: ${USE_GDCM}")
ENDIF()

IF(NOT DEFINED ${USE_CURL})
  readSettingFile("USE_CURL=" "OFF" STRING_RESULT )
  string(COMPARE EQUAL "${STRING_RESULT}" "ON" is_equal)
  if(is_equal)
    set(USE_CURL ON)
  else()
    set(USE_CURL OFF)
  endif()
  message(STATUS "USE_CURL from config file: ${USE_CURL}")
ENDIF()

IF(APPLE)
  add_definitions(-DAPPLE)
ENDIF()

IF(USE_CURL)
  add_definitions(-DUSE_CURL)
ENDIF()

IF(USE_CURL AND (APPLE OR MINGW))
  find_program (perl_path NAMES perl perl.exe)
  IF (NOT perl_path)
    message(FATAL_ERROR "You must install PERL and add it to PATH in order to build CURL")
  ELSE()
    message(STATUS "Perl was found in PATH: ${perl_path}")
  ENDIF()

  IF(APPLE)
    message(STATUS "######################### ADDING OPENSSL #######################################")
    hunter_add_package(OpenSSL)
    find_package(OpenSSL REQUIRED)

    message(STATUS "######################### ADDING CURL #######################################")
    hunter_add_package(CURL)
    find_package(CURL CONFIG REQUIRED)
  ENDIF()

  IF(MINGW)
    find_package(CURL REQUIRED)
  ENDIF()
ENDIF()

# zlib support
message(STATUS "######################### ADDING ZLIB #######################################")
hunter_add_package(ZLIB)
find_package(ZLIB CONFIG REQUIRED)

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

add_subdirectory(dependencies)

if(USE_GDCM)
  include(${CMAKE_CURRENT_BINARY_DIR}/dependencies/gdcm/GDCMConfig.cmake )
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
endif()

set ( ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include )
set ( ASSIMP_LIBRARY assimp )

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
          ${GLM_INCLUDE_DIRS}
          ${ASSIMP_INCLUDE_DIR}
          ${CMAKE_BINARY_DIR}/dependencies/assimp/include
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
          ${GLM_INCLUDE_DIRS}
          ${ASSIMP_INCLUDE_DIR}
          ${CMAKE_BINARY_DIR}/dependencies/assimp/include
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
          ${GLM_INCLUDE_DIRS}
          ${ASSIMP_INCLUDE_DIR}
          ${CMAKE_BINARY_DIR}/dependencies/assimp/include
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

IF(USE_CURL AND MINGW)
  SET(ENGINE_INCLUDES ${ENGINE_INCLUDES} ${CURL_INCLUDE_DIR})
  SET(ENGINE_LIBS ${ENGINE_LIBS} ${CURL_LIBRARIES})
ENDIF()

IF(USE_CURL AND APPLE)
  SET(ENGINE_LIBS ${ENGINE_LIBS} CURL::libcurl OpenSSL::SSL OpenSSL::Crypto)
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
