#!/bin/bash

# Check if no arguments are provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 file1 file2 file3 ..."
  exit 1
fi

# Loop through each file
for file in "$@"; do
  # Check if file exists
  if [ ! -f "$file" ]; then # -f checks if it's a regular file
    echo "File '$file' not found. Skipping..."
    continue #if the file does no exist "continue" skips the rest of the loop and moves to the next argument
  fi

  # Replace lowercase vowels with corresponding uppercase letters
  sed -i 's/a/A/g; s/e/E/g; s/i/I/g; s/o/O/g; s/u/U/g' "$file" #uses the sed command to perform in-place (-i) replacements in the file ("$file").

  echo "Processed file: $file"
done

echo "All files processed."

