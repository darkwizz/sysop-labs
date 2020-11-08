#!/bin/bash

size=$1
echo "Process growing to $size Kbytes."
gcc -o linkedlistgrow.out linkedlistgrow.c

chmod a+x linkedlistgrow.out
ulimit -v $size
echo "Current available size is $( ulimit -v )"
echo "Starting the linked list grow program"
./linkedlistgrow.out

echo "END"
