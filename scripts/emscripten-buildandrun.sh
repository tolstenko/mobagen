#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

$DIR/emscripten-install.sh
$DIR/emscripten-generate.sh
$DIR/emscripten-build.sh
open "http://localhost:8000"
$DIR/emscripten-serve.sh