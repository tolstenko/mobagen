#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source $DIR/../dependencies/emsdk/emsdk_env.sh

cmake --build $DIR/../bin-emscripten

rm -rf $DIR/../emscripten.zip
zip -r $DIR/../emscripten.zip $DIR/../bin-emscripten/bin/*
