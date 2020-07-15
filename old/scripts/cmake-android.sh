#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-android
cd $DIR/../bin-android
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/android-ndk-r18b-api-24-arm64-v8a-clang-libcxx11.cmake
cmake .. -DCMAKE_BUILD_TYPE=${BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=$DIR/../dependencies/polly/android-ndk-r18b-api-24-arm64-v8a-clang-libcxx11.cmake
make $*
make android-build

#STATE=$(adb get-state || exit 0)
#if [ "$STATE" == "device" ]; then
	 # make android-install android-start
#fi;
