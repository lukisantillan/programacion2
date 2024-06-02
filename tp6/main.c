#include "TP6.h"

static int cantidad;

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
  FILE *file = NULL;
  int opcion;
  bool flag_menu = true;
  bool flag_abm = false;

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
      modificacion(filename, legajo);
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
  if (file != NULL)
  {
    fclose(file);
  }
}

int funcion_hash_alumnos(int clave)
{
  // numero primo < a 1000 mas cercano
  return clave % 997;
}

TablaHash punto4(char *filename)
{
  // tamaño 1000 porque no se de cuanto tiene que ser
  TablaHash tabla = th_crear(1000, funcion_hash_alumnos);
  int i = 1;

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
      TipoElemento te = te_crear_con_valor(alumno.legajo, i++);
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

// punto5

Lista Generarlistaclaves(int cantidadclavesagenerar, int valorminimo, int valormaximo)
{
  Lista lista = l_crear();
  for (int i = 0; i < cantidadclavesagenerar; i++)
  {
    int clave = rand() % (valormaximo - valorminimo + 1) + valorminimo;

    while (l_buscar(lista, clave) != NULL)
    {
      clave = rand() % (valormaximo - valorminimo + 1) + valorminimo;
    }

    l_agregar(lista, te_crear(clave));
  }
  return lista;
}

ArbolAVL crearAVL(Lista L)
{
  ArbolAVL resultado = avl_crear();
  Iterador ite = iterador(L);
  while (hay_siguiente(ite))
  {
    TipoElemento ele = siguiente(ite);
    avl_insertar(resultado, ele);
  }
  return resultado;
}

bool esPrimo(int num)
{
  if (num <= 1)
    return false;

  for (int i = 2; i <= sqrt(num); i++)
    if (num % i == 0)
      return false;

  return true;
}

int encontrarPrimoMasCercano(int num)
{
  if (num <= 1)
    return 2;
  else if (esPrimo(num))
    return num;

  int menorPrimo = num - 1;
  int mayorPrimo = num + 1;

  while (true)
  {
    if (esPrimo(menorPrimo))
      return menorPrimo;
    else if (esPrimo(mayorPrimo))
      return mayorPrimo;
    menorPrimo--;
    mayorPrimo++;
  }
}

int funcionHashPunto5(int clave)
{
  return clave % encontrarPrimoMasCercano(cantidad);
}

TablaHash crearTablaHash(Lista L)
{
  TablaHash resultado = th_crear(cantidad, funcionHashPunto5);
  Iterador ite = iterador(L);
  while (hay_siguiente(ite))
  {
    TipoElemento ele = siguiente(ite);
    th_insertar(resultado, ele);
  }
  return resultado;
}

int main()
{
  // TODO: en el menu hay que preguntar por el nombre del archivo
  // TODO: en el menu hay que preguntar si quiere hacer cambios en el archivo
  abm_alumnos("alumnos.dat");

  TablaHash tabla = punto4("alumnos.dat");

  printf("\n");

  mostrarAlumnosActivos("alumnos.dat");
  th_mostrar_solo_ocupados(tabla);
  TipoElemento te = th_recuperar(tabla, 195311);
  if (te != NULL)
  {
    printf("Legajo: %d\nPosicion en el archivo: %d", te->clave, te->valor);
  }
  else
  {
    printf("Elemento no encontrado\n");
  }

  return 0;
}

// gcc -o output ../libs/hash/tabla_hash_lista_colisiones.c ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c ../libs/nodos/nodo.c ../libs/arboles/arbol-binario.c ../libs/colas/colas_arreglos.c ../libs/arboles/arbol-avl.c ../libs/arboles/arbol-binario-busqueda.c main.c