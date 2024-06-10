#!/usr/bin/bash

index=0

for var in $@
do
    if [ $index == 0 ]
    then
        par=$var
        index=1
    else
        sed -r "s/([a-z])/${par}\1/g" $var
    fi
done