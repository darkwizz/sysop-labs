#!/bin/bash

min=$1
max=$2

if [[ -z "$min" || -z "$max" ]]
then
	echo "Min or Max is not set"
	exit
fi

if [[ $min -ge $max ]]
then
	echo "Min is not less than Max"
	exit
fi

let "number = $RANDOM % ($max - $min) + $min"
# alternative way => number=$(( $RANDOM % ($max - $min) + $min ))
# echo $number

answer=""
while [[ $answer -ne $number  ]]
do
	read -p "Enter your guess: " answer
	if [[ $answer -gt $number ]]
	then
		echo "Try smaller"
	elif [[ $answer -lt $number ]]
	then
		echo "Try larger"
	fi
done
echo "Congratulations"
