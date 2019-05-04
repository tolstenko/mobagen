#!/usr/bin/env bash

export PATH=/mingw64/bin/:/usr/bin/:$PATH
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

gcc --version
/mingw64/bin/cmake -DCMAKE_SH="CMAKE_SH-NOTFOUND" -B${DIR}/../build -H${DIR}/../ -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=${DIR}/../dependencies/polly/mingw-cxx17.cmake
/mingw64/bin/cmake --build build
