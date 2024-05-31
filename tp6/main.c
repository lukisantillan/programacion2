#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libs/hash/tabla_hash.h"
#include "../libs/elementos/tipo_elemento.h"

typedef struct
{
  int legajo;
  char nombre[50];
  char apellido[50];
  char domicilio[200];
  int estado;
  // TE?
} Alumno;

// punto 4
// TODO: verificar cada vez que se ingresa un legajo que tenga 6 digitos

void ingresarAlumno(char *filename)
{
  FILE *file = fopen(filename, "ab"); // Abre el archivo en modo de adición binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Alumno alumno;

  printf("Ingrese el legajo del alumno: ");
  scanf("%d", &alumno.legajo);
  fflush(stdin);

  printf("Ingrese el nombre del alumno: ");
  fgets(alumno.nombre, sizeof(alumno.nombre), stdin);
  alumno.nombre[strcspn(alumno.nombre, "\n")] = 0; // Elimina el salto de línea
  fflush(stdin);

  printf("Ingrese el apellido del alumno: ");
  fgets(alumno.apellido, sizeof(alumno.apellido), stdin);
  alumno.apellido[strcspn(alumno.apellido, "\n")] = 0; // Elimina el salto de línea
  fflush(stdin);

  printf("Ingrese el domicilio del alumno: ");
  fgets(alumno.domicilio, sizeof(alumno.domicilio), stdin);
  alumno.domicilio[strcspn(alumno.domicilio, "\n")] = 0; // Elimina el salto de línea
  fflush(stdin);
  alumno.estado = 1;

  fwrite(&alumno, sizeof(Alumno), 1, file); // Escribe el registro del alumno en el archivo

  printf("Alumno ingresado exitosamente.\n");

  fclose(file);
}

void bajaLogicaAlumno(char *filename, int legajo)
{
  FILE *file = fopen(filename, "rb+"); // Abre el archivo en modo de lectura/escritura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Alumno alumno;
  bool alumnoEncontrado = false;

  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    if (alumno.legajo == legajo)
    {
      alumnoEncontrado = true;
      alumno.estado = 0;                        // Cambia el estado a inactivo
      fseek(file, -sizeof(Alumno), SEEK_CUR);   // Vuelve al inicio del registro actual
      fwrite(&alumno, sizeof(Alumno), 1, file); // Sobrescribe el registro
      printf("Estado del alumno con legajo %d cambiado a inactivo.\n", legajo);
      break;
    }
  }

  if (!alumnoEncontrado)
  {
    printf("Alumno con legajo %d no encontrado.\n", legajo);
  }

  fclose(file);
}

void mostrarAlumnosActivos(char *filename)
{
  FILE *file = fopen(filename, "rb"); // Abre el archivo en modo de lectura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Alumno alumno;
  printf("Alumnos Activos:\n\n");

  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    if (alumno.estado == 1)
    {
      printf("Legajo: %d\n", alumno.legajo);
      printf("Nombre: %s\n", alumno.nombre);
      printf("Apellido: %s\n", alumno.apellido);
      printf("Domicilio: %s\n", alumno.domicilio);
      printf("--------------------------\n");
    }
  }

  fclose(file);
}

void modificacion(char *filename, int legajo)
{
  FILE *file = fopen(filename, "rb+"); // Abre el archivo en modo de lectura/escritura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Alumno alumno;
  bool alumnoEncontrado = false;

  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    if (alumno.legajo == legajo)
    {
      alumnoEncontrado = true;
      printf("Ingrese el nombre del alumno: ");
      fgets(alumno.nombre, sizeof(alumno.nombre), stdin);
      alumno.nombre[strcspn(alumno.nombre, "\n")] = 0; // Elimina el salto de línea
      fflush(stdin);

      printf("Ingrese el apellido del alumno: ");
      fgets(alumno.apellido, sizeof(alumno.apellido), stdin);
      alumno.apellido[strcspn(alumno.apellido, "\n")] = 0; // Elimina el salto de línea
      fflush(stdin);

      printf("Ingrese el domicilio del alumno: ");
      fgets(alumno.domicilio, sizeof(alumno.domicilio), stdin);
      alumno.domicilio[strcspn(alumno.domicilio, "\n")] = 0; // Elimina el salto de línea
      fseek(file, -sizeof(Alumno), SEEK_CUR);                // Vuelve al inicio del registro actual
      fwrite(&alumno, sizeof(Alumno), 1, file);              // Sobrescribe el registro
      printf("Alumno con legajo %d modificado.\n", legajo);
      break;
    }
  }

  if (!alumnoEncontrado)
  {
    printf("Alumno con legajo %d no encontrado.\n", legajo);
  }

  fclose(file);
}

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
    int legajo;
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
      ingresarAlumno(filename);
      break;

    case 2:
      printf("Ingrese el legajo del alumno a modificar: ");
      scanf("%d", &legajo);
      fflush(stdin);
      modificacion(filename,legajo);
      break;
      
    case 3:
      printf("Ingrese el legajo del alumno a eliminar: ");
      scanf("%d", &legajo);
      fflush(stdin);
      bajaLogicaAlumno(filename, legajo);

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

  FILE *file = fopen(filename, "rb+");
  if (file == NULL)
  {
    printf("Error al abrir el archivo\n");
    return tabla;
  }

  Alumno alumno;
  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    if (alumno.estado == 1)
    {
      TipoElemento te = te_crear_con_valor(alumno.legajo, (void *)&alumno);
      bool inserto = th_insertar(tabla, te);
      if (!inserto)
      {
        printf("Error al insertar alumnos a la tabla hash\n");
        return tabla;
      }
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

  printf("\n");

  mostrarAlumnosActivos("alumnos.dat");
  th_mostrar_solo_ocupados(tabla);

  return 0;
}

// gcc -o output main.c ../libs/hash/tabla_hash_lista_colisiones.c ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c