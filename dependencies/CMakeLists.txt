execute_process( COMMAND git submodule update --init --recursive )
set_directory_properties( PROPERTIES CLEAN_NO_CUSTOM 1)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE CACHE BOOL "bla")

set(BUILD_SHARED_LIBS OFF CACHE BOOL "bla")

# set opengl only rendering
set(DIRECTX OFF CACHE BOOL "use directx")
set(VIDEO_OPENGL ON CACHE BOOL "use opengl")
set(VIDEO_OPENGLES OFF CACHE BOOL "use opengles")

IF (EMSCRIPTEN)

ELSEIF (ANDROID)
  # set( SDL_FILESYSTEM FALSE )
  set( PTHREADS OFF CACHE BOOL "Pthread support" )
  add_definitions(-DGL_GLEXT_PROTOTYPES)
ELSE ()
#  add_definitions(-DGLEW_STATIC)
#  add_definitions(-UGLEW_BUILD)
#  set(GLEW_USE_STATIC_LIBS ON CACHE BOOL "bla")
#  set(BUILD_SHARED_LIBS OFF CACHE BOOL "bla")
#  set( glew-cmake_BUILD_SHARED OFF CACHE BOOL "Build the shared glew library" )
#  set( glew-cmake_BUILD_STATIC ON CACHE BOOL "Build the static glew library" )
#  set( glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL "Build the single context glew library" )
#  set( glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL "Build the multi context glew library" )
#
#  hunter_add_package(glew)
#  find_package(glew CONFIG REQUIRED)
#  #add_subdirectory( glew )

  INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/)
  add_library (whereami STATIC ${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/whereami.c ${CMAKE_CURRENT_SOURCE_DIR}/whereami/src/whereami.h)
ENDIF ()

IF(USE_GDCM)
  set(GDCM_BUILD_DOCBOOK_MANPAGES OFF CACHE BOOL "Do not build gdcm manpages")
  set(GDCM_DOCUMENTATION OFF CACHE BOOL "Do not build gdcm manpages")
  set(BUILD_DOC OFF CACHE BOOL "Do not build gdcm manpages")
  add_subdirectory( gdcm )
ENDIF()

#add_subdirectory( assimp )

#set(IMGUI_USE_MINIZIP OFF CACHE BOOL "IMGUI_USE_MINIZIP")
#add_definitions(-DYES_IMGUIADDONS_ALL)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/imgui/ )

add_library (imgui STATIC 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp 
  ${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp 
) 




#execute_process( COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/openssl/config no-shared no-engine no-hw no-dso --prefix=${CMAKE_BINARY_DIR} )
#execute_process( COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/openssl depend -j9 && make -C ${CMAKE_CURRENT_SOURCE_DIR}/openssl -j9 && make -C ${CMAKE_CURRENT_SOURCE_DIR}/openssl install_sw )

#include(ExternalProject)
#ExternalProject_Add(
#    openssl
#    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openssl"
#    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/dependencies/openssl/config no-shared no-engine no-hw no-dso --prefix=${CMAKE_BINARY_DIR}
#    BUILD_COMMAND make depend -j9 && make -j9
#    INSTALL_COMMAND make install_sw
#    BUILD_IN_SOURCE 1
#)

#include(${CP_CMAKE_DIR}/HunterGate.cmake)
#hunter_add_package(OpenSSL)
#find_package(OpenSSL REQUIRED)
#target_link_libraries(foo PUBLIC OpenSSL::SSL OpenSSL::Crypto)



#
#set( OPENSSL_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/openssl/ CACHE PATH "OPENSSL_ROOT_DIR" )
#set( OPENSSL_LIBRARIES ${CMAKE_BINARY_DIR}/lib/ CACHE PATH "OPENSSL_LIBRARIES" )

