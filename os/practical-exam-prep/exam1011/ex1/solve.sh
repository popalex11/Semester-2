#!/bin/bash

count=0
for name in $@;do
	if [ -f $name ]; then
		files[$count]=$name
		count=$((count+1))
	fi
done

echo $count
for ((i=0;i<count-1;i++)); do
	echo >>  ${files[count-1]}
	cat ${files[i]} >> ${files[count-1]}
done
