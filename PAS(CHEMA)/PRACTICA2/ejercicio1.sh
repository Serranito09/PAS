#!/bin/bash
#ejercicio1.sh

for user in $(ps haux | sed -rne '1!s/^([^ ]+)[ ]+[^ ]+[ ]+([^ ]+).*/\1/p' | sort | uniq) #Agrupa los nombres que se repiten en uno solo
do
    contador=0.0
    for x in $(ps haux | sed -rne '1!s/^(['$user']+)[ ]+[^ ]+[ ]+([^ ]+).*/\2/p' | sort | uniq) #Pasa por cada valor
    do
        contador=$(echo "$contador+$x" | bc) #Realiza una suma de decimales que de forma normal no podría ocurrir
    done
    echo "El user <$user> consume <$contador>" #Imprime el tiempo que tarda por user
done
