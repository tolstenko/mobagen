file(GLOB TARGET_INC ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB TARGET_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.c )

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_INC} )

find_library(SDL2 SDL2)

#hunter_add_package(SDL2)
#find_package(SDL2 CONFIG REQUIRED)

if(ANDROID)
  add_library(main SHARED ${TARGET_SRC})
elseif(IOS)
  # FIXME
  add_library(main ${TARGET_SRC})
else()
  add_executable(main ${TARGET_SRC})
endif()

target_link_libraries (main engine SDL2)