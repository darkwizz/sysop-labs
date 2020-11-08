#!/bin/bash

pdf=$1
img=$2
x=$3
y=$4

if [[ -z "$pdf" || -z "$img" || -z "$x" || -z "$y" ]] ; then
	echo "Not all params are passed"
	exit -1
fi

if [[ ! $( convert -version ) ]] ; then
	echo "ImageMagick is not installed"
	exit -1
fi

if [[ $x != "+"* && $x != "-"* ]] ; then
	x="+$x"
	# echo $x
fi

if [[ $y != "+"* && $y != "-"* ]] ; then
	y="+$y"
	# echo $y
fi


# split passed pdf into .png pages
basepdf=$( basename $pdf )
convert $pdf "$basepdf.png"

# combine each page with the passed img
for image in $basepdf-*.png ; do
	magick composite -gravity center -geometry "$x$y" $img $image "overlayed-$image"
done

convert "overlayed-*" "overlayed-$basepdf"
echo "Result file: overlayed-$basepdf"

# cleanup
rm $basepdf-*
rm overlayed-$basepdf-*

