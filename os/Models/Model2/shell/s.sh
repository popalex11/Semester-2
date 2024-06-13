#!/bin/bash
month=`date | cut -d' ' -f 2`
for user in $@;do
    echo "$user: `last | awk -v u=$user '$1==u {print $0}' | grep -w $month | wc -l` sessions"
done | sort -n -k 2