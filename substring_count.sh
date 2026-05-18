#!/bin/bash

# Check command line arguments
if [ $# -ne 2 ]
then
    echo "Usage: ./substring_count.sh <string> <substring>"
    exit 1
fi

str=$1
sub=$2

count=$(echo "$str" | grep -o "$sub" | wc -l)

if [ $count -gt 0 ]
then
    echo "Substring found."
    echo "Occurrence count: $count"
else
    echo "Substring not found."
fi