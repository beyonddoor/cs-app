#!/bin/bash

run() {
    mkdir -p dist
    distfile="dist/$1"
    gcc -I3rd/tau -o "$distfile" "$1" && "$distfile"
}

help() {
    cat << _EOF
Usage: 
    --help|-h  print help
    --asm <cfile> compile and dump c source to asm
    --run <cfile> compile and run
_EOF
}

asm() {
    gcc -Og -c "$1" && objdump -d "${1%%.*}.o"
}

case "$1" in
    --run)
        shift 1
        run "$1"
        ;;

    # --help)
    -h)
        help
        ;;

    --asm)
        shift 1
        asm "$1"
        ;;

    *)
        echo "Unknown command $1" 1>&2
        help
        ;;
esac