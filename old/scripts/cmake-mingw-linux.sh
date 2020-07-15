#!/usr/bin/env bash

set -e
#C:\msys64\mingw64\bin\cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=C:/msys64/mingw64/bin/mingw32-make.exe -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/x86_64-w64-mingw32-gcc.exe -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe -DCMAKE_TOOLCHAIN_FILE=/projects/mobagen/dependencies/polly/mingw-cxx17.cmake -G "CodeBlocks - MinGW Makefiles" C:\projects\mobagen

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

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-mingw
cd $DIR/../bin-mingw
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DMINGW=ON -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/linux-mingw-w64.cmake  $DIR/../
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DMINGW=ON -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF -DCMAKE_VERBOSE_MAKEFILE=ON -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/linux-mingw-w64.cmake  $DIR/../
make $*
make $*
rm -rf /mobagen/win64mingw.zip
zip -r /mobagen/win64mingw.zip bin/*
chmod 777 /mobagen/win64mingw.zip
chmod -R 777 /mobagen/bin-mingw/
