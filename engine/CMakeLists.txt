set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
set(BUILD_SHARED_LIBS TRUE)

file(GLOB TARGET_INC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
    )

file(GLOB TARGET_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    )

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_INC})

IF (ANDROID)
  add_library (engine STATIC ${TARGET_SRC})
ELSE ()
  add_library (engine SHARED ${TARGET_SRC})
ENDIF ()

find_library(SDL2 SDL2)

target_link_libraries (engine ${ENGINE_LIBS} SDL2)

install (TARGETS engine DESTINATION lib)
install (FILES ${TARGET_INC} DESTINATION include/engine)