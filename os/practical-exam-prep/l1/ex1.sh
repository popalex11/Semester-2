

if [ $# -ne 2 ]; then
	echo "Usage: $0 <integer1> <integer2>"
	exit 1
fi

if ! [[ "$1" =~ ^-?[0-9]+$ ]] || ! [[ "$2" =~ ^-?[0-9]+$ ]]; then
    echo "Error: Both arguments must be integers"
    exit 1
fi
	
sum=$(($1 + $2)) 
diff=$(($1 - $2))
product=$(($1 * $2))

echo "Sum: $sum; Difference: $diff; Product: $product;"

