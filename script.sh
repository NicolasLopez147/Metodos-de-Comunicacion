#!/bin/bash
# Carpetas de los programas
tuberia="./Tuberia"
pasoMensaje="./PasoPorMensaje"
archivos="./Archivos"
memCompartida="./MemoriaCompartida"
# Cada funcion imprime el nombre del metodo de comunicacion, va a la ruta,
# ejecuta el make y vuelve a la carpeta original
function funTuberia(){
    echo "-----------------------Tuberia-------------------------"
    cd $tuberia
    make
    make clean
    cd ..
}
function funPaso(){
    echo "--------------------Paso por mensaje-------------------"
    cd $pasoMensaje
    make
    make clean
    cd ..
}
function funArchivos(){
    echo "-----------------------Archivos------------------------"
    cd $archivos
    make
    make clean
    cd ..
}
function funMemCompartida(){
    echo "-------------------Memoria compartida------------------"
    cd $memCompartida
    make
    make clean
    cd ..
}
funArchivos
funMemCompartida
funTuberia
funPaso
# Permite utilizar correr todos los comandos en la terminal de origen 
exec bash