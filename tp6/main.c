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
// TODO: verificar cada vez que se ingresa un legajo que tenga 6 digitos
void abm_alumnos(char *filename)
{
  int opcion;
  bool flag_menu = true;
  bool flag_abm = false;

  FILE *file;

  while (flag_menu)
  {
    printf("0. No realizar cambios en el archivo \n");
    printf("1. Crear nuevo archivo\n");
    printf("2. Modificar archivo actual\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    fflush(stdin);

    switch (opcion)
    {
    case 0:
      flag_menu = false;
      break;
    case 1:
      file = fopen(filename, "wb");
      flag_abm = true;
      flag_menu = false;
      break;
    case 2:
      file = fopen(filename, "ab");
      flag_abm = true;
      flag_menu = false;
      break;
    default:
      printf("Opcion invalida\n");
    }
  }

  if (file == NULL)
  {
    printf("Error al abrir el archivo\n");
    return;
  }

  while (flag_abm)
  {
    Alumno alumno;
    int legajo;
    bool alumnoEncontrado = false;
    printf("0. Salir\n");
    printf("1. Agregar alumno\n");
    printf("2. Modificar alumno\n");
    printf("3. Eliminar alumno\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    fflush(stdin);

    switch (opcion)
    {
    case 0:
      flag_abm = false;
      break;

    case 1:
      // TODO: verificar que el legajo no exista
      printf("Ingrese el legajo: ");
      scanf("%d", &alumno.legajo);
      fflush(stdin);
      printf("Ingrese el nombre: ");
      fgets(alumno.nombre, sizeof(alumno.nombre), stdin);
      fflush(stdin);
      printf("Ingrese el apellido: ");
      fgets(alumno.apellido, sizeof(alumno.apellido), stdin);
      fflush(stdin);
      printf("Ingrese el domicilio: ");
      fgets(alumno.domicilio, sizeof(alumno.domicilio), stdin);
      fflush(stdin);

      fwrite(&alumno, sizeof(Alumno), 1, file);
      printf("Alumno agregado\n");

      break;

    case 2:
    printf("Ingrese el legajo del alumno a modificar: ");
    scanf("%d", &legajo);
    fflush(stdin);

    rewind(file);
    alumnoEncontrado = false;

    while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
    {
        if (alumno.legajo == legajo)
        {
            alumnoEncontrado = true;

            printf("Ingrese el nuevo legajo: ");
            scanf("%d", &alumno.legajo);
            fflush(stdin);
            printf("Ingrese el nuevo nombre: ");
            fgets(alumno.nombre, sizeof(alumno.nombre), stdin);
            fflush(stdin);
            printf("Ingrese el nuevo apellido: ");
            fgets(alumno.apellido, sizeof(alumno.apellido), stdin);
            fflush(stdin);
            printf("Ingrese el nuevo domicilio: ");
            fgets(alumno.domicilio, sizeof(alumno.domicilio), stdin);
            fflush(stdin);

            fseek(file, -sizeof(Alumno), SEEK_CUR); // Mover el puntero al inicio del registro actual
            fwrite(&alumno, sizeof(Alumno), 1, file); // Sobrescribir el registro
            printf("Alumno modificado\n");
            break;
        }
    }

    if (!alumnoEncontrado)
    {
        printf("Alumno no encontrado\n");
    }
    break;

    case 3:
      printf("Ingrese el legajo del alumno a eliminar: ");
      scanf("%d", &legajo);
      fflush(stdin);

      rewind(file);

      FILE *temp = fopen("temp.dat", "wb");
      while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
      {
        if (alumno.legajo != legajo)
        {
          fwrite(&alumno, sizeof(Alumno), 1, temp);
        }
      }
      fclose(file);
      fclose(temp);

      remove(filename);
      rename("temp.dat", filename);
      file = fopen(filename, "ab");

      printf("Alumno eliminado\n");
      break;
    }
  }

  fclose(file);
}

int funcion_hash_alumnos(int clave)
{
  // numero primo < a 1000 mas cercano
  return clave % 997;
}

TablaHash punto3(char *filename)
{
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
    TipoElemento te = te_crear_con_valor(alumno.legajo, (void *)&alumno);
    bool inserto = th_insertar(tabla, te);
    if (!inserto)
    {
      printf("Error al insertar alumnos a la tabla hash\n");
      return;
    }
  }

  fclose(file);

  return tabla;
}

int main()
{
  // TODO: en el menu hay que preguntar por el nombre del archivo
  // TODO: en el menu hay que preguntar si quiere hacer cambios en el archivo
  abm_alumnos("alumnos.dat");

  TablaHash tabla = punto3("alumnos.dat");

  FILE *file = fopen("alumnos.dat", "rb");
  Alumno alumno;
  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    printf("Legajo: %d\n", alumno.legajo);
    printf("Nombre: %s", alumno.nombre);
    printf("Apellido: %s", alumno.apellido);
    printf("Domicilio: %s", alumno.domicilio);
    printf("\n");
  }
  fclose(file);

  th_mostrar_solo_ocupados(tabla);

  return 0;
}

// gcc -o output main.c ../libs/hash/tabla_hash_lista_colisiones.c ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c