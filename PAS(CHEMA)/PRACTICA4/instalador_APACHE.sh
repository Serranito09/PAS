#!/bin/bash
mkdir $HOME/tmp1
cd $HOME/tmp1

# Si por lo que sea la dirección que hay abajo no dispone del fichero, buscar otra con Google
wget -O httpd-2.4.53.tar.bz2 https://downloads.apache.org/httpd/httpd-2.4.53.tar.bz2
tar jxvf httpd-2.4.53.tar.bz2

# Bajamos y descomprimimos la última versión de las librerías APR
wget -O apr-1.6.5.tar.bz2 http://ftp.cixug.es/apache/apr/apr-1.6.5.tar.bz2
wget -O apr-util-1.6.1.tar.bz2 http://ftp.cixug.es/apache/apr/apr-util-1.6.1.tar.bz2
tar jxvf apr-1.6.5.tar.bz2
tar jxvf apr-util-1.6.1.tar.bz2

# Instalamos el compilador gcc
apt-get update
apt-get install build-essential

# Instalamos la herramienta make
apt-get install make

# Movemos las librerías a la carpeta de apache, para que éste las utilice
mv apr-1.6.5 ./httpd-2.4.53/srclib/apr
mv apr-util-1.6.1 ./httpd-2.4.53/srclib/apr-util

# Instalamos la libreria pcre
apt-get install libpcre3 libpcre3-dev

# Instalamos la libreria expat
apt-get install libexpat1-dev

#Compilamos apache
cd httpd-2.4.53
./configure --prefix=$HOME/httpd --with-included-apr
make
make install

#Borrar el directorio temporal de instalación
rm -rf $HOME/tmp1


