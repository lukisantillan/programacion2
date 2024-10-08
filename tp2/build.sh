#!/bin/bash

echo "Compilando y ejecutando el programa..."
gcc -o arreglos.out main.c elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c p2.c p3.c p4.c p5.c p6.c
gcc -o punteros.out main.c elementos/tipo_elemento.c ../libs/listas/listas_punteros.c p2.c p3.c p4.c p5.c p6.c
gcc -o cursores.out main.c elementos/tipo_elemento.c ../libs/listas/listas_cursores.c p2.c p3.c p4.c p5.c p6.c


echo "¿Qué tipo de lista desea utilizar?"
echo "1. Arreglos"
echo "2. Punteros"
echo "3. Cursores"
echo "4. Salir"

read -p "Ingrese el número de la opción deseada: " option

clear
case $option in
    1)
        ./arreglos.out
        ;;
    2)
        ./punteros.out
        ;;
    3)
        ./cursores.out
        ;;
    4)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac