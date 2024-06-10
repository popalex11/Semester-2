#!/usr/bin/bash

for var in $@
do
    nrOfLogins=`last -s '-1 month' $var | head -n-2 | wc -l`
    echo "$var $nrOfLogins"  >> temp1.txt
done

sort -k2 -n temp1.txt

rm temp1.txt