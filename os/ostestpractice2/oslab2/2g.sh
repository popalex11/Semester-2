#!/usr/bin/bash

counter=0
index=0

for var in $@
do
    if [ $index == 0 ]
    then
        par=$var
        index=1
    else
        grep -q $par $var
        if [ $? == 0 ]
        then
            counter=$((counter + 1))
            echo $var
        fi
    fi
done
echo $counter