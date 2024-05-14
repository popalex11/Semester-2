#!/bin/bash



divide() {

    local arr=("$@")
    local length=${#arr[@]}
    

    if [ $length -eq 1 ]; then
        echo ${arr[0]}
        return
    fi
    
    local mid=$((length / 2))
    
    local left_half=("${arr[@]:0:mid}")
    local right_half=("${arr[@]:mid}")
    
    local left_product=$(divide "${left_half[@]}")
    local right_product=$(divide "${right_half[@]}")
    
    echo $((left_product * right_product))
}


read -p "Enter the elements of the array separated by spaces: " -a arr

result=$(divide "${arr[@]}")
echo "Product of the array: $result"
