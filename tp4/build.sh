##!/bin/bash

echo "Compilando y ejecutando el programa..."
gcc -o compiled/arreglos_circular.out main.c elementos/tipo_elemento.c colas/colas_arreglos_circular.c

clear
echo "Que tipo de colas desea utilzar?"
echo "1. Arreglos circular"
echo "4. Salir"

read -p "Ingrese el número de la opción deseada: " option

clear
case $option in
    1)
        ./compiled/arreglos_circular.out
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