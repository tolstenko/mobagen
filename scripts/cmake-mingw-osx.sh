#!/usr/bin/env bash

set -e
#C:\msys64\mingw64\bin\cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=C:/msys64/mingw64/bin/mingw32-make.exe -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/x86_64-w64-mingw32-gcc.exe -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/x86_64-w64-mingw32-g++.exe -DCMAKE_TOOLCHAIN_FILE=/projects/mobagen/dependencies/polly/mingw-cxx17.cmake -G "CodeBlocks - MinGW Makefiles" C:\projects\mobagen

export CC=/usr/local/bin/x86_64-w64-mingw32-gcc
export CXX=/usr/local/bin/x86_64-w64-mingw32-g++
export CPP=/usr/local/bin/x86_64-w64-mingw32-cpp
export CXXCPP=/usr/local/bin/x86_64-w64-mingw32-cpp
export AR=/usr/local/bin/x86_64-w64-mingw32-gcc-ar
export NM=/usr/local/bin/x86_64-w64-mingw32-gcc-nm
export RANLIB=/usr/local/bin/x86_64-w64-mingw32-gcc-ranlib
export DLLTOOL=/usr/local/bin/x86_64-w64-mingw32-dlltool
export DLLWRAP=/usr/local/bin/x86_64-w64-mingw32-dllwrap
export LD=/usr/local/bin/x86_64-w64-mingw32-ld
export OBJCOPY=/usr/local/bin/x86_64-w64-mingw32-objcopy
export OBJDUMP=/usr/local/bin/x86_64-w64-mingw32-objdump
export PKGCONFIG=/usr/local/bin/x86_64-w64-mingw32-pkg-config

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-mingw
cd $DIR/../bin-mingw
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DMINGW=ON -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=`which x86_64-w64-mingw32-windres` -DDLLTOOL=`which x86_64-w64-mingw32-dlltool` -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS=" -static -static-libgcc -static-libstdc++" ../
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DMINGW=ON -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=`which x86_64-w64-mingw32-windres` -DDLLTOOL=`which x86_64-w64-mingw32-dlltool` -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS=" -static -static-libgcc -static-libstdc++" ../
make $*
make $*
rm -rf ../win64mingw.zip
zip -r ../win64mingw.zip bin/*
chmod 777 ../win64mingw.zip
chmod -R 777 ../bin-mingw/
