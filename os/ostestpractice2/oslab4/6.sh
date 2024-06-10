#!/usr/bin/bash

rm -f temp.txt

find . | while read -r line
do
    echo $line | rev | cut -d "/" -f 1 | rev >> temp.txt
done

awk -f 6.awk temp.txt

rm -f temp.txt