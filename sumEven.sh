#!/bin/bash

sumEven()
{
    n=$1
    sum=0
    even=2

    for ((i=1; i<=n; i++))
    do
        sum=$((sum + even))
        even=$((even + 2))
    done

    echo "Sum of first $n even numbers = $sum"
}

sumEven $1