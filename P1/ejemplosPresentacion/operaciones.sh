#!/bin/bash

read -p "Número 1: " num1
read -p "Número 2: " num2

echo "Suma: $[$num1+$num2]"

echo "Resta: $(($num1-$num2))"

let multiplicacion=$num1*$num2
echo "Multiplicacion: $multiplicacion"

echo "División: $[$num1/$num2]"

echo "Potencia: $[$num1**$num2]"

echo "Módulo: $[$num1%$num2]"
