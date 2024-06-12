##!/bin/bash

echo "Verificando si existe el directorio build..."
if [ ! -d "build" ]; then
    mkdir build
fi

echo "Compilando y ejecutando el programa..."

listas=""
pilas=""
colas=""
conjuntos=""
elementos="tipo_elemento.c"
main="main.c"
arbolBinario="arbol-binario.c"
arbolBusqueda="arbol-binario-busqueda.c"
arbolAvl="arbol-avl.c"
nodo="nodo.c"

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

echo "¿Qué tipo de implementación de Conjuntos desea utilizar?"
echo "1. LISTAS "
echo "2. AVL "
echo "3. Salir"

read -p "Ingrese el número de la opción deseada: " option
case $option in
    1)
        conjuntos="conjuntos_listas.c"
        ;;
    2)
        conjuntos="conjuntos_avl.c"
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

gcc -o build/program.out $main ../libs/elementos/$elementos ../libs/conjuntos/$conjuntos ../libs/listas/$listas  ../libs/nodos/$nodo ../libs/arboles/$arbolBinario ../libs/arboles/$arbolBusqueda ../libs/arboles/$arbolAvl 
./build/program.out