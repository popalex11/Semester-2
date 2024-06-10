#!/usr/bin/bash

for var in $@
do
    sed -i 's/.*[0-9].*//g' $var
done
