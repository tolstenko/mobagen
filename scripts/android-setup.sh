#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

export ANDROID_COMPILE_SDK="29"
export ANDROID_BUILD_TOOLS="29.0.3"
export ANDROID_SDK_TOOLS="6609375"

export ANDROID_HOME=${HOME}/Android
export ANDROID_NDK_HOME=$ANDROID_HOME/ndk

#apt-get --quiet update --yes
#apt-get --quiet install --yes wget tar unzip lib32stdc++6 lib32z1

mkdir -p ${ANDROID_HOME}
cd ${ANDROID_HOME} || exit

wget --quiet --output-document=${ANDROID_HOME}/android-sdk.zip "https://dl.google.com/android/repository/commandlinetools-linux-${ANDROID_SDK_TOOLS}_latest.zip"
unzip -q ${ANDROID_HOME}/android-sdk.zip -d ${ANDROID_HOME}
rm ${ANDROID_HOME}/android-sdk.zip

#wget --quiet --output-document=commandlinetools.zip "https://dl.google.com/android/repository/commandlinetools-linux-${ANDROID_SDK_TOOLS}_latest.zip"
#unzip -q -f commandlinetools.zip -d ${ANDROID_HOME}
#rm commandlinetools.zip

export PATH=${ANDROID_HOME}/tools:${ANDROID_HOME}/tools/bin:${ANDROID_HOME}/platform-tools:${PATH}

echo y | sdkmanager --sdk_root=${ANDROID_HOME} --licenses

touch ${HOME}/.android/repositories.cfg

yes | sdkmanager --sdk_root=${ANDROID_HOME} --update --channel=3

yes | sdkmanager --sdk_root=${ANDROID_HOME} "emulator" "platform-tools" "platforms;android-30" "platforms;android-29" "platforms;android-19" "build-tools;29.0.2" "ndk-bundle" "cmake;3.10.2.4988404" >/dev/null


