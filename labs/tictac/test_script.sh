#!/bin/bash

i=1
while read -r line
do
    echo "Running test $i: $line"
    echo "$line" | ./move-check
    ((i++))
done < tests.txt