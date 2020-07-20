#!/usr/bin/env bash

export ANDROID_HOME=${HOME}/Android
export ANDROID_NDK_HOME=$ANDROID_HOME/ndk
export PATH=${ANDROID_HOME}/tools:${ANDROID_HOME}/tools/bin:${ANDROID_HOME}/platform-tools:${PATH}

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${DIR}/platforms/android/ || exit

./gradlew assembleDebug

adb -d install app/build/outputs/apk/debug/app-debug.apk
