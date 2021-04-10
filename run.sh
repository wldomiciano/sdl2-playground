#!/usr/bin/env bash

set -e

if [ "$1" == "clang" ]; then
  DEFS='-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang'
fi

clear && rm -rf build && cmake -S . -B build $DEFS

if [[ "$@" =~ "build" ]]; then
  cmake --build build
fi
