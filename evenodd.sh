#!/bin/bash


# Check if input file exists
if [ ! -f numbers.txt ]
then
    echo "Input file not found!"
    exit
fi

# Clear previous contents of even and odd files
> even
> odd

# Read numbers from file
for num in $(cat numbers.txt)
do
    if [ $((num % 2)) -eq 0 ]
    then
        echo $num >> even
    else
        echo $num >> odd
    fi
done

echo "Even numbers stored in file 'even'"
echo "Odd numbers stored in file 'odd'"
