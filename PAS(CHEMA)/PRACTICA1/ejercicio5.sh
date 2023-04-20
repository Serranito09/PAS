 #!/bin/bash
if [ $# == 2 ] ; then
    if [ -d $1 ]; then
        if `echo $2 | grep -q '[0-9]\+'`; then #filtra el texto mostrando las lineas que cumplen un patron, -c cientra el numero de lineas, -l muestra ficheros que contiene patron e -i es no sensible a las mayusculas
        # ^ es el comienzo de la linea, $ fin de la linea, . cualquier caracter
            hours=$2;
            minutes=$((hours*60));
            find $1 -mmin -$minutes -type f #find 
        else
            echo "Introduzca como segundo parametro un número entero"
        fi
    else
       echo "El directorio $1 no existe"
    fi
else
    echo "Son necesarios dos parámetros"
    echo "Uso: ./ejercicio5.sh <ruta_directorio> <num_horas>"
fi

