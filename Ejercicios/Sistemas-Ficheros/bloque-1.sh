#!/bin/bash

cd ~ 
mkdir -p so/pruebas/
cd so
touch pruebas/vacio.v
ls -li
mkdir otros
ln -P pruebas/vacio.v otros/semi.txt
ls -li otros/semi.txt 
echo "aqui hay 23 caracteres" > otros/semi.txt 
ln -s pruebas/vacio.v simLink.sl 
ls -li simLink.sl 
cat simLink.sl
rm pruebas/vacio.v
cat simLink.sl
cat otros/semi.txt
touch pruebas/vacio.v
