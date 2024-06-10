#!/usr/bin/bash

for arg in $@
do
    nrOfUpperCase=`cat $arg | tr -dc [:upper:] | wc -c`
    nrOfLowerCase=`cat $arg | tr -dc [:lower:] | wc -c`
    echo "The number of uppercase letters in the file $arg is $nrOfUpperCase"
    echo "The number of lowercase letters in the file $arg is $nrOfLowerCase"
done