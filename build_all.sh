#!/bin/bash
# Compile every practical into ./bin/
mkdir -p bin
for src in */*.cpp; do
    name=$(basename "$src" .cpp)
    if g++ -Wall -std=c++11 "$src" -o "bin/$name"; then
        echo "OK    $src"
    else
        echo "FAIL  $src"
    fi
done
echo "Run any program with: ./bin/<name>"
