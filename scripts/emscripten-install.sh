#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

$DIR/../deps/emsdk/emsdk install latest
$DIR/../deps/emsdk/emsdk activate latest