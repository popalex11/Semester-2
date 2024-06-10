#!/usr/bin/bash

for var in $@
do
    find $var -name '*.txt' > ../temp.txt
    while read -r line
    do
        cat $line
    done < ../temp.txt
done
rm ../temp.txt