#!/bin/bash

set -e

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

if [[ $BUILD_TYPE == android ]]; then
  $DIR/cmake-android.sh
elif [[ $BUILD_TYPE == native ]]; then
  $DIR/cmake-make.sh
elif [[ $BUILD_TYPE == emscripten ]] ; then
  $DIR/cmake-emscripten.sh
elif [[ $BUILD_TYPE == windows ]] ; then
  $DIR/cmake-mingw-linux.sh
fi
