IF (ANDROID)
    set(ANDROID_BIN_ROOT ${CMAKE_BINARY_DIR}/android-project)
    add_custom_target(android-install ${ANDROID_ANT} ${ANT_INSTALL_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
    add_custom_target(android-backtrace ${ANDROID_ADB} logcat WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
    add_custom_target(android-build ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})
    add_custom_target(android-start ${ANDROID_ADB} shell am start -n org.libsdl.app/org.libsdl.app.SDLActivity WORKING_DIRECTORY ${ANDROID_BIN_ROOT})

    add_library (uploader ${CMAKE_CURRENT_SOURCE_DIR}/../../dependencies/SDL/src/main/android/SDL_android_main.c main.cpp)
    target_link_libraries (uploader engine)
	#cotire(uploader)

    # add_custom_command(TARGET uploader POST_BUILD COMMAND ${ANDROID_ANT} ${ANT_FLAGS} ${ANT_TARGET} WORKING_DIRECTORY ${ANDROID_BIN_ROOT})

    add_custom_command(TARGET uploader PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/android-project/
            ${ANDROID_BIN_ROOT}/)

    add_custom_command(TARGET uploader PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets/
            ${ANDROID_BIN_ROOT}/assets)

    add_custom_command(TARGET uploader POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/ ${ANDROID_BIN_ROOT}/libs/${ANDROID_NDK_ABI_NAME})
ELSE ()
  IF(NOT EMSCRIPTEN AND USE_CURL)
    add_executable (uploader main.cpp EditorGUI.cpp EditorGUI.hpp)
    hunter_add_package(CURL)
    find_package(CURL CONFIG REQUIRED)
    target_link_libraries (uploader engine CURL::libcurl)
    #cotire(uploader)
    add_custom_command(TARGET uploader PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_SOURCE_DIR}/assets
      $<TARGET_FILE_DIR:uploader>/assets)
  ELSE()
    add_executable (uploader main.cpp EditorGUI.cpp EditorGUI.hpp)
    target_link_libraries (uploader engine)
    #cotire(uploader)
    add_custom_command(TARGET uploader PRE_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${CMAKE_SOURCE_DIR}/assets
      $<TARGET_FILE_DIR:uploader>/assets)
  ENDIF()
ENDIF ()
