#!/usr/bin/bash

file=$1
rights=$2



stat -c "%a" $file > trash.txt

if [ $? != "0" ]
then
    echo "Does not exist"
    exit
fi

f_rights=`stat -c "%a" $file`

if [ rights = f_rights ]
then
    echo "Yes"
else
    echo "No"
fi