#!/bin/bash

# Check if no arguments are provided
if [ $# -eq 0 ]; then
  echo "Usage: $0 file1 file2 file3 ..."
  exit 1
fi

# Loop through each file
for file in "$@"; do
  # Check if file exists
  if [ ! -f "$file" ]; then
    echo "File '$file' not found. Skipping..."
    continue
  fi

  # Replace uppercase vowels with corresponding lowercase letters
  sed -i 's/A/a/g; s/E/e/g; s/I/i/g; s/O/o/g; s/U/u/g' "$file"

  echo "Restored file: $file"
done

echo "All files restored."

