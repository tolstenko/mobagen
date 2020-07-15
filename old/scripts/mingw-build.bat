echo on

where sh
where cmake
cmake --version
echo %PATH%
cmake -DCMAKE_SH="CMAKE_SH-NOTFOUND" -B%cd%\build -H%cd% -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=%cd%\dependencies\polly\mingw-cxx17.cmake
cmake --build build
