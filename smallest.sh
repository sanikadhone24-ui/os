#!/bin/bash

smallest=""
min=1000

for file in *
do
    len=${#file}

    if [ $len -lt $min ]
    then
        min=$len
        smallest=$file
    fi
done

echo "Smallest file name is: $smallest"
echo "Length is: $min"
