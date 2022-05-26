#!/bin/bash
tuberia="./Tuberia"
pasoMensaje="./PasoPorMensaje"
archivos="./Archivos"
memCompartida="./MemoriaCompartida"
# echo Hola Mundo
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
exec bash