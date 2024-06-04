##!/bin/bash

echo "Verificando si existe el directorio build..."
if [ ! -d "build" ]; then
    mkdir build
fi

echo "Compilando y ejecutando el programa..."

listas=""
pilas=""
colas=""
hash=""
elementos="tipo_elemento.c"
main="main.c"
arbolBinario="arbol-binario.c"
arbolBusqueda="arbol-binario-busqueda.c"
arbolAvl="arbol-avl.c"
nodo="nodo.c"

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
echo "¿Qué tipo de Hash desea utilizar?"
echo "1. Lista de Colisiones"
echo "2. Zona Overflow"
echo "3. Salir"

read -p "Ingrese el número de la opción deseada: " option
case $option in
    1)
        hash="tabla_hash_lista_colisiones.c"
        ;;
    2)
        hash="tabla_hash_zona_overflow.c"
        ;;
    3)
        echo "Saliendo..."
        ;;
    *)
        echo "Opción inválida"
        ;;
esac

clear

clear

gcc -o build/program.out $main ../libs/elementos/$elementos ../libs/hash/$hash ../libs/listas/$listas ../libs/pilas/$pilas ../libs/colas/$colas ../libs/nodos/$nodo ../libs/arboles/$arbolBinario ../libs/arboles/$arbolBusqueda ../libs/arboles/$arbolAvl 
./build/program.out