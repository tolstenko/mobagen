cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
        URL "https://github.com/ruslo/hunter/archive/v0.23.130.tar.gz"
        SHA1 "83f526c350b5dcc9ccdfe6c927d4e951fe78adee"
)
project (Engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
include(${CP_CMAKE_DIR}/macros.cmake)

IF(NOT EXISTS "${PROJECT_SOURCE_DIR}/buildconfig.txt")
  message(FATAL_ERROR "The file buildconfig.txt must exists to load build configurations from it.")
ENDIF()

#if you want to always use what is write on buildconfig, you must to unset the variable cache
#unset(USE_BULLET CACHE)

IF(NOT DEFINED ${USE_BULLET})
  readSettingFile("USE_BULLET=" "ON" STRING_RESULT )
  set( USE_BULLET "${STRING_RESULT}" CACHE BOOL "USE BULLET?" )
  message(STATUS "USE_BULLET from config file: ${USE_BULLET}")
ENDIF()

IF(NOT DEFINED ${USE_GDCM})
  readSettingFile("USE_GDCM=" "OFF" STRING_RESULT )
  set( USE_GDCM "${STRING_RESULT}" CACHE BOOL "USE GDCM?" )
  message(STATUS "USE_GDCM from config file: ${USE_GDCM}")
ENDIF()

IF(NOT DEFINED ${USE_CURL})
  readSettingFile("USE_CURL=" "OFF" STRING_RESULT )
  set( USE_CURL "${STRING_RESULT}" CACHE BOOL "USE CURL?" )
  message(STATUS "USE_CURL from config file: ${USE_CURL}")
ENDIF()

IF(${USE_BULLET})
  hunter_add_package(bullet)
  find_package(bullet CONFIG REQUIRED)
ENDIF()

IF(${USE_CURL})
  find_program (perl_path NAMES perl perl.exe)
  IF (NOT perl_path)
    message(FATAL_ERROR "You must install PERL and add it to PATH in order to build CURL")
  ELSE()
    message(STATUS "Perl was found in PATH: ${perl_path}")
  ENDIF()
ENDIF()

IF (NOT EMSCRIPTEN AND ${USE_CURL})
  set(LIBC ON CACHE BOOL "LIBC")
  hunter_add_package(cpr)
  find_package(cpr CONFIG REQUIRED)
  hunter_add_package(CURL)
  find_package(CURL CONFIG REQUIRED)
ENDIF()

IF (NOT EMSCRIPTEN)
  hunter_add_package(SDL2)
  find_package(SDL2 CONFIG REQUIRED)
ENDIF()

set(NOMINMAX ON CACHE BOOL "workaround for minmax problem with windows.h")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cotire)

set(BUILD_STATIC_LIBS TRUE)
set(BUILD_SHARED_LIBS FALSE)

IF (ANDROID)
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

################################################################################################################################
set( ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build assimp tools" )
set( ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build assimp tests" )
set( ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Build assimp samples" )

set( ASSIMP_BUILD_3DS_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_3DS_EXPORTER)

set( ASSIMP_BUILD_AC_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_AC_EXPORTER)

set( ASSIMP_BUILD_ASE_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_ASE_EXPORTER)

set( ASSIMP_BUILD_ASSBIN_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_ASSBIN_EXPORTER)

set( ASSIMP_BUILD_ASSXML_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_ASSXML_EXPORTER)

set( ASSIMP_BUILD_B3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_B3D_EXPORTER)

set( ASSIMP_BUILD_BVH_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_BVH_EXPORTER)

set( ASSIMP_BUILD_COLLADA_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_COLLADA_EXPORTER)

set( ASSIMP_BUILD_DXF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_DXF_EXPORTER)

set( ASSIMP_BUILD_CSM_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_CSM_EXPORTER)

set( ASSIMP_BUILD_HMP_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_HMP_EXPORTER)

set( ASSIMP_BUILD_IRRMESH_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_IRRMESH_EXPORTER)

set( ASSIMP_BUILD_IRR_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_IRR_EXPORTER)

set( ASSIMP_BUILD_LWO_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_LWO_EXPORTER)

set( ASSIMP_BUILD_LWS_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_LWS_EXPORTER)

set( ASSIMP_BUILD_MD2_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MD2_EXPORTER)

set( ASSIMP_BUILD_MD3_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MD3_EXPORTER)

set( ASSIMP_BUILD_MD5_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MD5_EXPORTER)

set( ASSIMP_BUILD_MDC_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MDC_EXPORTER)

set( ASSIMP_BUILD_MDL_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MDL_EXPORTER)

set( ASSIMP_BUILD_NFF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_NFF_EXPORTER)

set( ASSIMP_BUILD_NDO_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_NDO_EXPORTER)

set( ASSIMP_BUILD_OFF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OFF_EXPORTER)

set( ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OBJ_EXPORTER)

set( ASSIMP_BUILD_OGRE_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OGRE_EXPORTER)

set( ASSIMP_BUILD_OPENGEX_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_OPENGEX_EXPORTER)

set( ASSIMP_BUILD_PLY_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_PLY_EXPORTER)

set( ASSIMP_BUILD_MS3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_MS3D_EXPORTER)

set( ASSIMP_BUILD_COB_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_COB_EXPORTER)

set( ASSIMP_BUILD_BLEND_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_BLEND_EXPORTER)

set( ASSIMP_BUILD_IFC_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_IFC_EXPORTER)

set( ASSIMP_BUILD_XGL_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_XGL_EXPORTER)

set( ASSIMP_BUILD_FBX_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_FBX_EXPORTER)

set( ASSIMP_BUILD_Q3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_Q3D_EXPORTER)

set( ASSIMP_BUILD_Q3BSP_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_Q3BSP_EXPORTER)

set( ASSIMP_BUILD_RAW_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_RAW_EXPORTER)

set( ASSIMP_BUILD_SIB_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_SIB_EXPORTER)

set( ASSIMP_BUILD_SMD_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_SMD_EXPORTER)

set( ASSIMP_BUILD_STL_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_STL_EXPORTER)

set( ASSIMP_BUILD_TERRAGEN_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_TERRAGEN_EXPORTER)

set( ASSIMP_BUILD_3D_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_3D_EXPORTER)

set( ASSIMP_BUILD_X_IMPORTER ON CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_XFILE_EXPORTER)

set( ASSIMP_BUILD_GLTF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_GLTF_EXPORTER)

set( ASSIMP_BUILD_3MF_IMPORTER OFF CACHE BOOL "Build importer" )
add_definitions(-DASSIMP_BUILD_NO_3MF_EXPORTER)

IF(ANDROID)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoc++11-narrowing -std=c++14")
ENDIF()

hunter_add_package(Assimp)
find_package(Assimp CONFIG REQUIRED)

################################################################################################################################

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/ )

set ( WHEREAMI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/whereami/src/ )
set ( WHEREAMI_LIBRARY whereami )

set ( IMGUI_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/addons
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/addons/imguifilesystem)

set ( IMGUI_LIBRARY imgui )

IF (EMSCRIPTEN)
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Engine/example/assets/ -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s TOTAL_MEMORY=536870912 -s USE_SDL=2 -std=c++14 -Oz")
  SET(CMAKE_CXX_FLAGS "--closure 1 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s TOTAL_MEMORY=536870912 -s USE_SDL=2 -std=c++14 -Oz")
  add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

  # CHECK FOR CURL AND GDCM
  set(ENGINE_LIBS
#    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
    ${GDCM_LIBRARIES}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
#    ${ASSIMP_INCLUDE_DIR}
#    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
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

ELSEIF (ANDROID)
  add_definitions( -DGLES2=1 )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoc++11-narrowing -std=c++14")

  # CHECK FOR CURL AND GDCM
  set(ENGINE_LIBS
    SDL2::SDL2
#    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
    ${GDCM_LIBRARIES}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
#    ${ASSIMP_INCLUDE_DIR}
#    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
    ${GDCM_INCLUDE_DIRS}
  )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++14 -fPIC")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -std=c++14 -fPIC")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
    SDL2::SDL2
    ${OPENGL_LIBRARY}
#    ${ASSIMP_LIBRARY}
    ${WHEREAMI_LIBRARY}
    ${IMGUI_LIBRARY}
  )
  set(ENGINE_INCLUDES
      ${GLM_INCLUDE_DIRS}
#      ${ASSIMP_INCLUDE_DIR}
#      ${CMAKE_BINARY_DIR}/dependencies/assimp/include
      ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
      ${WHEREAMI_INCLUDE_DIRS}
      ${IMGUI_INCLUDE_DIRS}
      ${CMAKE_CURRENT_SOURCE_DIR}/engine/
    )

  IF(USE_CURL)
    SET(ENGINE_LIBS
      ${ENGINE_LIBS}
      cpr::cpr
    ) 
  ENDIF()
  
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

include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/examples )

IF (NOT ANDROID)
  option(BUILD_TESTS "BUILD TESTS" ON)
  IF (BUILD_TESTS)
    add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/tests )
  ENDIF ()
ENDIF ()


