#!/usr/bin/bash

folder=`echo "${@: -1}"`

for arg in $@
do
    if [ $arg != $folder ]
    then
        find $folder -name $arg | rev | cut -d "/" -f 2 | rev  
    fi
done