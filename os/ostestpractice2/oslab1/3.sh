#!/usr/bin/bash

res=`factor $1 | cut -d ":" -f2`
if [ $res = $1 ]; then
    echo "The number is prime!"
else
    echo "The number is not prime!"
fi