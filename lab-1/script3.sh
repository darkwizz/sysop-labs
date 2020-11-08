#!/bin/bash

base=$1
power=$2

if [[ -z "$base" || -z "$power" ]] ; then
	echo "No passed base or power"
fi

if [[ $power -lt 0 ]] ; then
	echo "Result = $( bc -l <<< $base^$power )"
	exit
fi

result=1
for ((i=0;i<power;i++)) ; do
	result=$(( $result * $base ))
done

echo "Result = $result"
