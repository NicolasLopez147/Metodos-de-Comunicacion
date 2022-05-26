#!/bin/bash
# Carpetas de los programas
tuberia="./Tuberia"
pasoMensaje="./PasoPorMensaje"
archivos="./Archivos"
memCompartida="./"
# Cada funcion imprime el nombre del metodo de comunicacion, va a la ruta,
# ejecuta el make y vuelve a la carpeta original
function funTuberia(){
    echo "-----------------------Tuberia-------------------------"
    cd $tuberia
    make
    cd ..
}
function funPaso(){
    echo "--------------------Paso por mensaje-------------------"
    cd $pasoMensaje
    make
    cd ..
}
function funArchivos(){
    echo "-----------------------Archivos------------------------"
    cd $archivos
    make
    cd ..
}
function funMemCompartida(){
    echo "-------------------Memoria compartida------------------"
    cd $memCompartida
    make
    cd ..
}
funTuberia
funPaso
funArchivos
funMemCompartida
# Permite utilizar correr todos los comandos en la terminal de origen 
exec bash