#!/usr/bin/bash

index=0

for var in $@
do
    echo $index
    if [ $index == 0 ]
    then
        index=1
        par=$var
    else
        echo $par
        sed -i "/${par}/d" $var
    fi
done