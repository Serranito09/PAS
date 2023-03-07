#!/bin/bash

# Sin here documents
echo "****************"
echo "* Mi script V1 *"
echo "****************"
echo "Introduzca su nombre"

# Usando here documents
cat << EOF
****************
* Mi script V1 *
****************
Introduzca su nombre
EOF
