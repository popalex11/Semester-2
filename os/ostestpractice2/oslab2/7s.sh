#!/usr/bin/bash

for arg in $@
do
    sed -i -r "s/([aeiou])/\U\1/g" $arg
done