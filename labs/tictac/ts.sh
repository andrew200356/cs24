#!/bin/bash

while IFS= read -r line
do
  echo "$line" | ./move-check
done < tests.txt