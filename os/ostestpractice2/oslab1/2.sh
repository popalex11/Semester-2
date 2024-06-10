#!/usr/bin/bash

res=`diff $1 $2 | head -n 4 | tail -n 3`
echo $res