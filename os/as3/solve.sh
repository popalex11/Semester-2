#!/bin/bash

# Check if no arguments are passed
if [ $# -eq 0 ]; then
    echo "Usage: $0 file1 file2 file3 ..."
    exit 1
fi

# Loop through each argument (assuming they are files)
for file in "$@"; do
    # Check if the file exists
    if [ ! -f "$file" ]; then
        echo "File '$file' not found."
        continue
    fi

    echo "Processing file: $file"

    # Read each line of the file
    while IFS= read -r line; do
        # Check if line length is greater than 20 characters
        if [ ${#line} -gt 20 ]; then
            # Split the line into an array of words
            words=($line)
            
            # Get the number of the line
            line_number=$(grep -n "$line" "$file" | cut -d ":" -f 1)

            # Display line number, first word, and last word
            echo "Line $line_number: ${words[0]} ${words[-1]}"
        fi
    done < "$file"

done

