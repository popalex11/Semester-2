#!/usr/bin/bash

old=$1
new=$2

cat $old > temp.txt

grades=()

cat $new | while read -r line
do
    index=0
    sum=0
    for token in $line
    do
        if [ $index == 0 ]
        then
            name=$token
            index=1
        else
            sum=`echo "$sum + $token" | bc`
        fi
    done
    grades[$name]=`echo "$sum / 5" | bc`
    echo "$name : ${grades[$name]}"
done

cat temp.txt | while read -r line
do
    name=`echo $line | cut -d " " -f 1`
    echo "$name : ${grades[$name]}"
done

rm temp.txt