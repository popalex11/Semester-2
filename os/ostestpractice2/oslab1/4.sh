#!/usr/bin/bash

sum=0
curr=1

while [ $curr != 0 ]; do
    read curr
    sum=$((sum + curr))
done
echo $sum