#!/bin/bash

is_prime() {
    num=$1
    if [ $num -le 1 ]; then
        echo "$num is not a prime number."
        exit 1
    fi

    is_prime=true
    for ((i = 2; i <= num / 2; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            is_prime=false
            break
        fi
    done

    if [ "$is_prime" = true ]; then
        echo "$num is a prime number."
    else
        echo "$num is not a prime number."
    fi
}

# Check if argument is provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <number>"
    exit 1
fi

# Check if the argument is a valid natural number
if ! [[ "$1" =~ ^[0-9]+$ ]]; then
    echo "Error: '$1' is not a valid natural number."
    exit 1
fi

# Call the function to check if it is prime
is_prime "$1"
