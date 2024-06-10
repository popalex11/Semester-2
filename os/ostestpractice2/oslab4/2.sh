#!/usr/bin/bash

file_path=$1

rm -r result
mkdir result

cat $file_path | while read -r line
do
    for token in $line
    do
        to_lower=`echo $token | tr [:upper:] [:lower:]`
        letter=${to_lower:0:1}
        echo $token >> "result/$letter.txt"
    done
done 