#!/bin/bash

sum=0

echo "Enter numbers (type '0' to end):"

while true; do
	read num
	
	if [ "$num" = 0 ]; then
		break
	fi
	
	sum=$((sum + num))
	
done

echo ""
echo "The sum of the numbers entered is: $sum"
