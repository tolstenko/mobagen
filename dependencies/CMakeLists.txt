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
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
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
ENDIF ()

IF(USE_GDCM)
  set(GDCM_BUILD_DOCBOOK_MANPAGES OFF CACHE BOOL "Do not build gdcm manpages")
  set(GDCM_DOCUMENTATION OFF CACHE BOOL "Do not build gdcm manpages")
  set(BUILD_DOC OFF CACHE BOOL "Do not build gdcm manpages")
  add_subdirectory( gdcm )
ENDIF()


# Avoid assimp bug for android
IF (ANDROID)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-narrowing")
ENDIF()

set( ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Build assimp tools" )
set( ASSIMP_BUILD_TESTS OFF CACHE BOOL "Build assimp tests" )
set( ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "Build assimp samples" )
set( ASSIMP_NO_EXPORT ON CACHE BOOL "ASSIMP_NO_EXPORT" )
set( ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT OFF CACHE BOOL "ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT" )

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

add_subdirectory( assimp )

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
#execute_process( COMMAND make -C ${CMAKE_CURRENT_SOURCE_DIR}/openssl depend && make -C ${CMAKE_CURRENT_SOURCE_DIR}/openssl && make -C ${CMAKE_CURRENT_SOURCE_DIR}/openssl install_sw )

#include(ExternalProject)
#ExternalProject_Add(
#    openssl
#    SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/openssl"
#    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/dependencies/openssl/config no-shared no-engine no-hw no-dso --prefix=${CMAKE_BINARY_DIR}
#    BUILD_COMMAND make depend && make
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

