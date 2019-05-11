#!/usr/bin/env bash

#docker rm --force emscripten
docker run -dit --name emscripten -e TRAVIS_OS_NAME='linux' -e BUILD_TYPE='emscripten' -v `pwd`:/mobagen -w /mobagen trzeci/emscripten:sdk-incoming-64bit bash
docker exec -it emscripten apt-get update
docker exec -it emscripten rm /usr/local/bin/cmake
docker exec -it emscripten apt-get install -y cmake wget
docker exec -it emscripten ./scripts/travis-build.sh
docker exec -it emscripten ./scripts/travis-build.sh