#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

# brew
if command -v brew 2>/dev/null; then
  echo "brew exists"
else
  echo "please install brew"
  echo "run:"
  echo "ruby -e \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)\""
  exit 1
fi

# cmake
if command -v cmake 2>/dev/null; then
  echo "cmake exists"
else
  echo "installing cmake"
  brew install cmake
fi

# docker
if command -v docker 2>/dev/null; then
  echo "docker exists"
else
  echo "installing docker"
  #echo "Download and install docker https://www.docker.com"
  brew cask install docker
  brew install bash-completion
  brew install docker-completion
  brew install docker-compose-completion
  brew install docker-machine-completion
  open -a Docker
fi

# XCode build
export CC=clang
export CXX=clang++
export TRAVIS_OS_NAME=osx
export BUILD_TYPE=native
#todo: make this portable
export NPROC=`sysctl -n hw.ncpu`
$DIR/cmake-make.sh

# emscripten build
export TRAVIS_OS_NAME=linux
export BUILD_TYPE=emscripten
docker run -dit --name emscripten -e TRAVIS_OS_NAME='linux' -e BUILD_TYPE='emscripten' -v $DIR/../:/mobagen -w /mobagen trzeci/emscripten:sdk-incoming-64bit bash
docker exec -it emscripten apt-get update
docker exec -it emscripten rm /usr/local/bin/cmake
docker exec -it emscripten apt-get install -y cmake wget
docker exec -it emscripten ./scripts/travis-build.sh
docker exec -it emscripten ./scripts/travis-build.sh

# mingw build
export TRAVIS_OS_NAME=linux
export BUILD_TYPE=windows
docker run -dit --name windows -e TRAVIS_OS_NAME='linux' -e BUILD_TYPE='windows' -v $DIR/../:/mobagen -w /mobagen library/ubuntu:bionic bash ;
docker exec -it windows apt-get update ;
docker exec -it windows apt-get install -y cmake wget binutils-mingw-w64* gcc-mingw-w64* g++-mingw-w64* wine-development git mingw-w64 mingw-w64-tools binutils-mingw-w64 binutils-mingw-w64-x86-64 binutils-mingw-w64-i686 mingw-w64-x86-64-dev mingw-w64-i686-dev autoconf automake autotools-dev zip ;
docker exec -it windows ./scripts/travis-build.sh
docker exec -it windows ./scripts/travis-build.sh