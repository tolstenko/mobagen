#!/usr/bin/env bash

DIRECTORY="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

mkdir -p "${DIRECTORY}"/../bin-emscripten/bin/

cd $DIRECTORY/../deps/emsdk

source emsdk_env.sh

#echo EMSDK
#echo $EMSDK
#
#echo EM_CONFIG
#echo $EM_CONFIG
#
#echo EM_CACHE
#echo $EM_CACHE
#
#echo EMSDK_NODE
#echo $EMSDK_NODE

export PATH=${EMSDK}:${EMSDK}/upstream/emscripten:${EMSDK}/upstream/bin:${EMSDK_NODE}:${PATH}

emcc --version
export EMSCRIPTEN=${EMSDK}/upstream/emscripten
export EMSDK=${EMSDK}/upstream/emscripten

cd $DIRECTORY/../bin-emscripten
cmake -DCMAKE_C_COMPILER=emcc -DCMAKE_CXX_COMPILER=em++ -DCMAKE_MAKE_PROGRAM=cmake -DCMAKE_C_ABI_COMPILED=ON -DCMAKE_CXX_ABI_COMPILED=ON -DCMAKE_CROSSCOMPILING=ON -DCMAKE_TOOLCHAIN_FILE=$DIRECTORY/../deps/polly/emscripten-cxx17.cmake -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_STATIC_LIBRARY_SUFFIX=".bc" -DCMAKE_SHARED_LIBRARY_SUFFIX=".bc" -DEMSCRIPTEN=1 -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
