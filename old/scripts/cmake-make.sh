#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Debug}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin
cd $DIR/../bin
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE}
make $*
if [[ $BUILD_TYPE == native ]] && [[ $TRAVIS_OS_NAME == linux ]]; then
  rm -rf ../linux.zip
  zip -r ../linux.zip bin/*
fi
if [[ $BUILD_TYPE == native ]] && [[ $TRAVIS_OS_NAME == osx ]]; then
  rm -rf ../osx.zip
  zip -r ../osx.zip bin/*
fi




