#!/bin/bash
tuberia="./Tuberia"
pasoMensaje="./PasoPorMensaje"
archivos="./Archivos"
memCompartida="./"
# echo Hola Mundo
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
}
funTuberia
funPaso
funArchivos
funMemCompartida
exec bash