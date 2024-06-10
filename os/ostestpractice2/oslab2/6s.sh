#!/usr/bin/bash

index=0

for arg in $@
do
    if [ $index == 0 ]
    then
        index=1
        letter=$arg
    else
        sed 's/[!-/ :-@ {|}]/'"$letter"'/g' $arg
    fi
done