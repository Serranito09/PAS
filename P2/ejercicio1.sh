#!bin/bash

#Crear un script que ejecute los comandos adecuados de grep que permitan realizar las si-
#guientes tareas sobre el fichero de ejemplo peliculas.txt:
#1. Mostrar aquellas lı́neas que contienen la duración de la pelı́cula (uno o más dı́gitos al prin-
#cipio de la lı́nea, un espacio y la secuencia “min”).
#2. Mostrar los paı́ses de las pelı́culas (sin mostrar la lı́nea completa que contiene dicha infor-
#mación). Suponemos que siempre aparecerá rodeado de guiones, p.ej: “-Estados Unidos-”.
#3. Contar cuántas pelı́culas son del 2016 y cuántas del 2017.
# 4. Mostrar aquellas palabras que contengan la letra “d”,“l” o “t”, una vocal y la misma letra
# (por ejemplo, “Universidad”, “expectativas”, “dedicarse”,etc).
# 5. Todas aquellas lı́neas que terminen con 3 puntos (“...”) y no empiecen por espacio, utilizan-
# do el operador de repetición {}.
# 6. Utilizar sed para mostrar entre comillas dobles las vocales con tilde (mayúsculas o minúscu-
# las).

if [ $# -ne 1 ] #control de argumentos
then
    echo "Argumentos erroneos. Uso: ./ejercicio1.sh <fichero_peliculas>"
    exit
fi

if [  -x $1 ] #controlamos que se pase un fichero y no un directorio o cualquier otra cosa
then
    echo "Se esperaba un fichero del tipo peliculas.txt"
    exit
fi

cd FicherosPract2

echo "1) Lineas con la duracion de las peliculas:"
cat $1 | grep ^[1-9] #devuelve las lineas que empiezan por un numero. ^ se usa para indicar que la linea empieza por lo que viene detrás

echo "2) Solo pais de las peliculas:"
cat $1 | grep -o  -E "\-.+\-" #devuelve las parte de las lineas que se encuentra entre guiones. -o indica que no se devuelve toda la linea, solo la parte coindicente.

cont16=0
cont17=0
pelis16=$(cat $1 | grep -o "\(2016\)") #devuelve solo los 2016 que hay en el fichero. \(\) se usa para indicar que debe coincidir exactamente con eso
pelis17=$(cat $1 | grep -o "\(2017\)")
# o poner cat $1 | grep "2016" | wc -l

for i in $pelis16
do
    cont16=$[$cont16+1] #por cada vez que se ha guardado 2016, se suma 1
done

for i in $pelis17
do
    cont17=$[$cont17+1]
done

echo "3) Hay $cont16 pelicula de 2016 y $cont17 de 2017" #mostramos el numero de veces que aparece 2016 y 2017

echo "4) Palabras que contengan d, l o t, una vocal, y misma letra" 
cat $1 | grep -E -o "\w*([d|l|t])[aeiou]\1\w*" #\w* al principio indica que se muestra el inicio de la palabra hasta llegar a la coincidencia, y al final dice que se muestra desde la coincidencia hasta el final de la palabra

echo "5) Lineas que acaben con 3 puntos y no empiecen por espacios"
cat $1 | grep -E "^[^ ]+(..)+\.${3}"

echo "6) Mostrar las vocales mayusculas o minusculas que tengan tildes entre comillas"
cat $1 | sed -r 's/([áéíóúÁÉÍÓÚ])/"\1"/g' #sed sirve para reemplazar en el txt. s = sustituir, [...] indica lo que se quiere sustituir, "&" indica que el caracter anterior se pone entre comillas, g = todas las coincidencias, no solo la primera

# COMANDOS UTILIZADOS
# -E -> no se cuando se usa, quita y pon cuando no te vaya algo (se usa en el comando grep)
# -r -> no se cuando se usa, quita y pon cuando no te vaya algo (se usa en el comando sed)
# para devolver las lineas que empiezan por un caracter -> ^caracter
# para indicar un rango de caracteres posibles -> [caracteres]
# para indicar que solo se devuelve la coincidencia -> -o
# para indicar que tiene que coincidir con algo especificamente -> "\(caracteres\)"
# para devolver desde el principio de la palabra hasta la coincidencia, o desde la coincidencia hasta el final -> \w* (poner al principio o final de la cadena)
# para decir que lo que está entre paréntesis se repite -> "(caracter)\1"
# para indicar un or -> |
# para indicar que las coincidencias con algunos caracteres NO se deben mostrar -> [^caracteres]
# para añadir algo mas a la coincidencia -> +
# para decir que hay uno o varios caracteres mas -> (..)
# para indicar que el caracter a continuacion se interpreta de forma literal -> \caracter
# para devolver las lineas que terminan por un caracter -> caracter$
# para indicar que el caracter anterior debe aparecer un rango de veces ->{n, m}
# sed -> 's/caracteres_a_sustituir/sustitución/flags' 
