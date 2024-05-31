#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libs/hash/tabla_hash.h"
#include "../libs/elementos/tipo_elemento.h"

typedef struct
{
  char nombre[50];
  char apellido[50];
  int legajo;
  char domicilio[200];
  // TE?
} Alumno;

// punto 4
int abm_alumnos(char *filename)
{
  int opcion;
  bool flag = true;
  bool flag2 = false;

  FILE *file;

  while (flag)
  {
    printf("Desea realizar cambios en el archivo de alumnos?\n");
    printf("0. No realizar cambios\n");
    printf("1. Crear nuevo archivo\n");
    printf("2. Modificar archivo actual\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    fflush(stdin);

    switch (opcion)
    {
    case 0:
      return 0;
    case 1:
      printf("Creando nuevo archivo...\n");
      file = fopen(filename, "wb");
      flag = false;
      flag2 = true;
      break;
    case 2:
      printf("Modificando archivo actual...\n");
      file = fopen(filename, "ab");
      flag = false;
      flag2 = true;
      break;
    default:
      printf("Opcion invalida\n");
      break;
    }
  }

  if (file == NULL)
  {
    printf("Error al abrir el archivo\n");
    return 1;
  }

  while (flag2)
  {
    Alumno alumno;
    printf("Ingrese el legajo del alumno (o 0 si desea no cargar mas datos): ");
    // TODO: chequear que tenga 6 digitos
    scanf("%d", &alumno.legajo);
    fflush(stdin);
    if (alumno.legajo == 0)
    {
      flag2 = false;
      break;
    }
    printf("Ingrese el nombre del alumno: ");
    fgets(alumno.nombre, sizeof(alumno.nombre), stdin);
    fflush(stdin);
    printf("Ingrese el apellido del alumno: ");
    fgets(alumno.apellido, sizeof(alumno.apellido), stdin);
    fflush(stdin);
    printf("Ingrese el domicilio del alumno: ");
    fgets(alumno.domicilio, sizeof(alumno.domicilio), stdin);
    fflush(stdin);

    fwrite(&alumno, sizeof(Alumno), 1, file);
  }

  fclose(file);
  return 0;
}

int funcion_hash_alumnos(int clave)
{
  // numero primo < a 1000 mas cercano
  return clave % 997;
}

TablaHash punto3(char *filename)
{
  abm_alumnos(filename);
  // tamaño 1000 porque no se de cuanto tiene que ser
  TablaHash tabla = th_crear(1000, funcion_hash_alumnos);

  FILE *file = fopen(filename, "rb");
  if (file == NULL)
  {
    printf("Error al abrir el archivo\n");
    return;
  }

  Alumno alumno;
  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    TipoElemento te = te_crear_con_valor(alumno.legajo, (void*)&alumno);
    th_insertar(tabla, te);
  }

  fclose(file);

  return tabla;
}

int main()
{
  // TODO: en el menu hay que preguntar por el nombre del archivo
  TablaHash tabla = punto3("alumnos.dat");
  th_mostrar_solo_ocupados(tabla);

  //funcionar funciona pero no se como mostrar los valores de cada elemento
  TipoElemento alumno = th_recuperar(tabla, 195311);
  printf("Legajo: %d\n", ((Alumno*)alumno->valor)->legajo);
  printf("Nombre: %s\n", ((Alumno*)alumno->valor)->nombre);
  printf("Apellido: %s\n", ((Alumno*)alumno->valor)->apellido);
  printf("Domicilio: %s\n", ((Alumno*)alumno->valor)->domicilio);
  
  return 0;
}

// gcc -o output main.c ../libs/hash/tabla_hash_lista_colisiones.c ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c