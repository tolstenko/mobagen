#!/usr/bin/env bash

export PATH=/mingw64/bin:/usr/local/bin:/usr/bin:/bin:/c/Windows/System32:/c/Windows:/c/Windows/System32/Wbem:/c/Windows/System32/WindowsPowerShell/v1.0/:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl:$PATH

export MSYSTEM=MINGW64
export MINGW_PREFIX=/mingw64
export SHELL=/usr/bin/bash
export TERM=xterm
export MSYSTEM_PREFIX=/mingw64
export MINGW_PACKAGE_PREFIX=mingw-w64-x86_64
export CONFIG_SITE=/mingw64/etc/config.site
export MSYSTEM_CHOST=x86_64-w64-mingw32
export MSYSTEM_CARCH=x86_64
export MSYSCON=mintty.exe

export CC=/usr/bin/x86_64-w64-mingw32-gcc-win32
export CXX=/usr/bin/x86_64-w64-mingw32-g++-win32
export CPP=/usr/bin/x86_64-w64-mingw32-cpp-win32
export CXXCPP=/usr/bin/x86_64-w64-mingw32-cpp-win32
export AR=/usr/bin/x86_64-w64-mingw32-gcc-ar-win32
export NM=/usr/bin/x86_64-w64-mingw32-gcc-nm-win32
export RANLIB=/usr/bin/x86_64-w64-mingw32-gcc-ranlib-win32
export DLLTOOL=/usr/bin/x86_64-w64-mingw32-dlltool
export DLLWRAP=/usr/bin/x86_64-w64-mingw32-dllwrap
export LD=/usr/bin/x86_64-w64-mingw32-ld
export OBJCOPY=/usr/bin/x86_64-w64-mingw32-objcopy
export OBJDUMP=/usr/bin/x86_64-w64-mingw32-objdump
export PKGCONFIG=/usr/bin/x86_64-w64-mingw32-pkg-config
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

gcc --version

which cmake
cmake -DCMAKE_SH="CMAKE_SH-NOTFOUND" -B${DIR}/../build -H${DIR}/../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/mingw64/bin/mingw32-make.exe -DCMAKE_C_COMPILER=/mingw64/bin/x86_64-w64-mingw32-gcc.exe -DCMAKE_CXX_COMPILER=/mingw64/bin/x86_64-w64-mingw32-g++.exe -DCMAKE_TOOLCHAIN_FILE=${DIR}/../dependencies/polly/mingw-cxx17.cmake -G "MinGW Makefiles"
cmake --build build
