#!/usr/bin/bash

total=0
counter=0

for arg in $@
do
    output=`awk -f 6.awk $arg`
    curr=`echo $output | cut -d ' ' -f 2`
    total=`echo "$total + $curr" | bc`
    counter=$((counter + 1))
done

echo "$total / $counter" | bc
