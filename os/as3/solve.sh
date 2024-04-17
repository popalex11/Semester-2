#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 file2 file3 ..."
    exit 1
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "File '$file' not found."
        continue
    fi
    
    echo
    echo "Processing file: $file"
    
    while read -r line; do
        if [ ${#line} -gt 20 ]; then
            words=($line)

            line_number=$(grep -n "$line" "$file"| cut -d ":" -f 1)

            echo "Line $line_number: ${words[0]} ${words[-1]}"
        fi
    done < "$file"

done

