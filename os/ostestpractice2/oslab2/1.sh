#!/usr/bin/bash

file="-1"
for var in $@
do
    if [ $file == "-1" ]
    then
        file=$var
    else
        sed -i "s/${var}//g" $file
    fi
done 