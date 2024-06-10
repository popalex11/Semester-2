#!/usr/bin/bash

total=0

for arg in $@
do
    awk -f 8.awk $arg | grep [0-9] | while read -r line ; do
        total=`echo "$total + $line" | bc`
        echo $total
    done
done

echo $total