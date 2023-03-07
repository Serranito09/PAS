#!/bin/bash

let sum=0

for num in 1 2 3 4 5
do
	sum=$[$sum+$num]
	echo $sum
done 

echo "La suma de los 5 elementos es $sum."
