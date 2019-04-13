#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/

source $DIR/../dependencies/emsdk/emsdk_env.sh

cd $DIR/../bin-emscripten
cmake -DCMAKE_C_ABI_COMPILED=ON -DCMAKE_CXX_ABI_COMPILED=ON -DCMAKE_CROSSCOMPILING=ON -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/emscripten-cxx11.cmake -DCMAKE_MODULE_PATH=$EMSCRIPTEN/cmake/ -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_STATIC_LIBRARY_SUFFIX=".bc" -DCMAKE_SHARED_LIBRARY_SUFFIX=".bc" -DEMSCRIPTEN=1 -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
cmake -DCMAKE_C_ABI_COMPILED=ON -DCMAKE_CXX_ABI_COMPILED=ON -DCMAKE_CROSSCOMPILING=ON -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/emscripten-cxx11.cmake -DCMAKE_MODULE_PATH=$EMSCRIPTEN/cmake/ -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_STATIC_LIBRARY_SUFFIX=".bc" -DCMAKE_SHARED_LIBRARY_SUFFIX=".bc" -DEMSCRIPTEN=1 -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
make
rm -rf /mobagen/bin-emscripten/emscripten.zip
zip -r /mobagen/emscripten.zip bin/*
chmod 777 /mobagen/emscripten.zip
chmod -R 777 /mobagen/bin-emscripten/
