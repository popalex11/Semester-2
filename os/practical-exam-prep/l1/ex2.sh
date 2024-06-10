#!/bin/bash

# Check if exactly two arguments are provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 file1 file2"
    exit 1
fi

# Check if both arguments are valid files
if [ ! -f "$1" ] || [ ! -f "$2" ]; then
    echo "Error: Both arguments must be valid files"
    exit 1
fi

file1=$1
file2=$2
diff_count=0

# Compare the files line by line
while IFS= read -r line1 && IFS= read -r line2 <&3; do
    if [ "$line1" != "$line2" ]; then
        echo "Difference found:"
        echo "File1: $line1"
        echo "File2: $line2"
        echo "-----------------------------------"
        ((diff_count++))
    fi
    if [ "$diff_count" -ge 3 ]; then
        break
    fi
done <"$file1" 3<"$file2"

if [ "$diff_count" -eq 0 ]; then
    echo "The files are identical in the first 3 differing lines."
fi

