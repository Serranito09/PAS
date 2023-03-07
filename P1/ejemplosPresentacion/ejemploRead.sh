#!/bin/bash

echo -n "Introduzca nombre de fichero a borrar: "

read fichero

rm -i $fichero

echo "Fichero $fichero se ha borrado!"

