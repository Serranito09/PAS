#!/bin/bash
echo "Introduzca el primer numero"
read x
echo "Introduzca el segundo numero"
read y
echo "Suma: $((x+y))"
echo "Resta: $((x-y))"
echo "Multiplicacion: $((x*y))"
echo "Division: $[x/y]"
let potencia=$x**$y
echo "Potencia: $potencia"
echo "Modulo: $(($x%y))"
