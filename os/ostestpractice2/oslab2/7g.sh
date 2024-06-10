#!/usr/bin/bash

for arg in $@
do
    ping -c 1 $arg | grep -q "64 bytes from"
    if [ $? == 0 ]
    then
        echo "$arg is up"
    else
        echo "$arg is down"
    fi
done