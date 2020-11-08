#!/bin/bash

size=$1
echo "Process growing to $size Kbytes."
gcc -o linkedlistgrow.out linkedlistgrow.c

chmod a+x linkedlistgrow.out
./linkedlistgrow.out &

process_id=$(ps aux | grep ./linkedlistgrow.out | head -n 1 | awk '{print $2}')
echo "PID is: $process_id"

memory=$(pmap $process_id | tail -1 | awk '{print $2}' | cut -dK -f 1)
echo "Current memory is $memory"

while [[ $memory < $size ]]; do
	echo "Current memory is $memory"
	memory=$(pmap $process_id | tail -1 | awk '{print $2}' | cut -dK -f 1)
	sleep 1
done
kill -9 $process_id
echo "Process has been killed"
