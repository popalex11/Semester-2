#!/bin/bash


if [ -z "$1" ]; then
	echo "Usage: $0 directory_name"
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "Error: $1 is not a valid directory"
	exit 1
fi

for file in "$1"/*; do
	if [ -f "$file" ] && [[ "$file" == *.txt ]]; then
		echo "Filename: $file"
		head -n 3 "$file"
		echo "--------------------"
	fi
done
