#!/usr/bin/env sh

if [ "$1" = "clang" ]; then
  clear && rm -rf build && cmake -S . -B build -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
else
  clear && rm -rf build && cmake -S . -B build
fi
