#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $DIR/../dependencies/emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
cd $DIR/../

cmake -Bbuild-emscripten -H. -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_STATIC_LIBRARY_SUFFIX=".bc" -DCMAKE_SHARED_LIBRARY_SUFFIX=".bc" -DEMSCRIPTEN=1 -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/emscripten-cxx11.cmake
cmake --build build-emscripten
cmake --build build-emscripten

rm -rf $DIR/../emscripten.zip
zip -r $DIR/../emscripten.zip $DIR/../build-emscripten/bin/*
