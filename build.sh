#!/bin/bash

mkdir -p dist
distfile="dist/$1"
gcc -I3rd/tau -o "$distfile" "$1" && "$distfile"
