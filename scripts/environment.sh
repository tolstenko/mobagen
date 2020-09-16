#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

source $DIR/../deps/emsdk/emsdk_env.sh
export PATH=${EMSDK}/upstream/bin:${PATH}
