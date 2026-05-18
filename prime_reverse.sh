#!/bin/bash

echo "Enter a number:"
read num

# Store original number
temp=$num

# Prime number check
flag=0

if [ $num -le 1 ]
then
    flag=1
else
    for ((i=2; i<=num/2; i++))
    do
        if [ $((num%i)) -eq 0 ]
        then
            flag=1
            break
        fi
    done
fi

if [ $flag -eq 0 ]
then
    echo "$num is a Prime Number"
else
    echo "$num is Not a Prime Number"
fi

# Reverse number
rev=0

while [ $temp -gt 0 ]
do
    rem=$((temp%10))
    rev=$((rev*10 + rem))
    temp=$((temp/10))
done

echo "Reverse of number is: $rev"