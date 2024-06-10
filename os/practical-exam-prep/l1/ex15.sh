#!/bin/bash

list=()


echo "Enter words (type 'stop' to end):"

while true; do
	read word
	
	if [ "$word" = "stop" ]; then
		break
	fi
	
	list+=("$word")
	
done

echo ""
echo "You entered the following words: "

for w in "${list[@]}"; do
	echo "$w"
done
