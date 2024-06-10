#!/usr/bin/bash

who > temp1.txt

while [ 1 == 1 ]
do
    who > temp2.txt
    users=`diff temp2.txt temp1.txt | tail -n+2`
    if [ -z "${users}" ]
    then
        continue
    fi
    echo $users | while  IFS= read -r line
    do
        sep=`echo $line | cut -c1-1`
        if [ $sep = ">" ]
        then
            user=`echo $line | cut -d " " -f 2`
            date=`echo $line | cut -d " " -f 4`
            hour=`echo $line | cut -d " " -f 5`
            echo "$user has disconnected at date $date and hour $hour"
        fi
        if [ $sep = "<" ]
        then
            user=`echo $line | cut -d " " -f 2`
            date=`echo $line | cut -d " " -f 4`
            hour=`echo $line | cut -d " " -f 5`
            echo "$user has connected at date $date and hour $hour"
        fi
    done
    cat temp2.txt > temp1.txt
done