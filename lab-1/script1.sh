#!/bin/bash

dir=$1
size=$2

# find $dir -name ".*" -prune -o -type f -size +"$size"c -printf '%T@ %p\n' | sort -n -r | head -1

find $dir -name ".*" -prune -o -type f -size +"$size"c -exec ls -1tl {} + | head -1
