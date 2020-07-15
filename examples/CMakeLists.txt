file(GLOB TARGET_INC ${CMAKE_CURRENT_SOURCE_DIR}/*.h ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB TARGET_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.c )

SET(TARGET_SRC ${TARGET_SRC} ${TARGET_INC} )

add_executable (simple ${TARGET_SRC})
target_link_libraries (simple engine)