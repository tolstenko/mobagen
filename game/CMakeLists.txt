file(GLOB TARGET_INC ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB TARGET_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.c )

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_INC} )

find_library(SDL2 SDL2)

#hunter_add_package(SDL2)
#find_package(SDL2 CONFIG REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})

if(ANDROID)
  add_library(main SHARED main.cpp)
  target_sources(main PRIVATE main.cpp)

  target_link_libraries(main SDL2 ${SDL2_LIBRARY})

elseif(IOS)
  # FIXME
  add_library(main ${TARGET_SRC})
else()
  add_executable(main ${TARGET_SRC})
endif()

#target_link_libraries (main engine SDL2 ${SDL2_LIBRARY} ${SDL2_INCLUDE_DIR})