#!/bin/bash


fichero="$1"
numero_pings="$2"
timeout="$3"

cd FicherosPract2

if [ $# -ne 3 ] || [ ! -e $fichero ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio2.sh <archivo_ips> <numerio_ping> <timeout>"
    exit
fi

#IFS= read -r line
for ip in $(cat $fichero) #guarda en $ip cada linea del fichero $fichero
do


    #el comando ping nos da mucha informacion
    #con tail -1 nos quedamos solo con la ultima linea
    #awk te permite sacar la columna que quieras separada por el caracter que esta entre comillas
        #si tienes rtt min/avg/max/mdev = 15.392/23.753/42.119/10.922


    #awk -> te permite sacar la columna que quieras separada por el caracter que esta entre comillas
    pig=$(ping -c $numero_pings -W $timeout $ip | tail -1| awk -F '/' '{print $5}')

    if [[ $pig < $timeout ]] #Dobles corchetes porque estamos usando el < y no -lt
    then
        echo "La IP $ip no respondio $timeout segundos"
    else
        echo "$ip $pig ms"
    fi
done
