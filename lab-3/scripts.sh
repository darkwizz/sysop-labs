#!/bin/bash

# to find all manpages for a command
# apropos -e <command>  => -e mean 'exact match'
apropos -e umask


# find the oldest modification file
find ~ -not -type d -printf "%T+ %p\n" | sort -n | head -1 # | cut -d" " -f2

# find the number of all directories
dir_count=$( find /usr/include -type d | wc -l )
echo "Directories count in /usr/include: $dir_count"


# find the number of all m***.h inside /usr/include (no subdirectories)
h_count=$( find /usr/include -maxdepth 1 -type f -name "m???.h" | wc -l )
echo "m***.h count in /usr/include: $h_count"


# find the number of regular files > 12 KB inside /usr/include
files12k_count=$( find /usr/include -type f -size +12000c | wc -l )
echo "Files > 12 KB count in /usr/include: $files12k_count"


# find the number of files < 1 MB inside /usr/bin
files1M_count=$( find /usr/bin -not -type d -size 1M | wc -l )
echo "Files < 1 MB count in /usr/bin: $files1M_count"
