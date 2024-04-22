##!/bin/bash

echo "Verificando si existe el directorio compiled..."
if [ ! -d "compiled" ]; then
    mkdir compiled
fi

echo "Compilando y ejecutando el programa..."

listas=""
pilas=""
colas=""

elementos="tipo_elemento.c"
main="main.c"

clear

echo "¿Qué tipo de pilas desea utilizar?"
echo "1. Arreglos"
echo "2. Punteros"
echo "3. Salir"

read -p "Ingrese el número de la opción deseada: " option
case $option in
    1)
        pilas="pilas_arreglos.c"
        ;;
    2)
        pilas="pilas_punteros.c"
        ;;
    3)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac
clear

echo "¿Qué tipo de listas desea utilizar?"
echo "1. Arreglos"
echo "2. Punteros"
echo "3. Cursores"
echo "4. Salir"

read -p "Ingrese el número de la opción deseada: " option
case $option in
    1)
        listas="listas_arreglos.c"
        ;;
    2)
        listas="listas_punteros.c"
        ;;
    3)
        listas="listas_cursores.c"
        ;;
    4)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac
clear

echo "¿Qué tipo de colas desea utilizar?"
echo "1. Arreglos circular"
echo "2. Arreglos"
echo "3. Punteros"
echo "4. Salir"

read -p "Ingrese el número de la opción deseada: " option
case $option in
    1)
        colas="colas_arreglos_circular.c"
        ;;
    2)
        colas="colas_arreglos.c"
        ;;
    3)
        colas="colas_punteros.c"
        ;;
    4)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac

clear

gcc -o build/program.out $main ../libs/elementos/$elementos ../libs/listas/$listas ../libs/pilas/$pilas ../libs/colas/$colas
./build/program.out