#!/usr/bin/bash

index=0

for var in $@
do
    if [[ "$index" = "0" ]]
    then
        dir=$var
        index=$((index + 1))
    else
        file=$var
        find $dir -name "$file" | while IFS= read -r line
        do
            size=`stat --printf="%s" $line`
            finalline=`echo $line $size`
            echo $finalline >> temp3.txt
        done
    fi
done

sort -k2 -n -r temp3.txt
rm temp3.txt