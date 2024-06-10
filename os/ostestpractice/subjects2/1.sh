#!/usr/bin/bash

index=0

for var in $@
do
    index=$((index + 1))
    cat $var &
    if [ $index = $# ]
    then
        cat temp.txt >> $var
        continue
    fi
    if [ $? = "0" ]
    then
        cat $var >> temp.txt
    fi
done

rm temp.txt