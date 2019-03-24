add_subdirectory( midasminer )
IF (NOT ANDROID)
  add_subdirectory( doceditor )
  add_subdirectory( uploader )
  add_subdirectory( simple )
  add_subdirectory( filedialog )
  add_subdirectory( startpage )
ENDIF()

