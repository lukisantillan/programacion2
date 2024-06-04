#include "TP6.h"

static int cantidad;

// Funciones auxiliares
void clearScreen()
{
    system("clear");
}

void waitForKey()
{
    printf("\nPresione Enter para continuar...");
    while (getchar() != '\n')
        ;
    getchar();

    system("clear");
}

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
    printf("Error al abrir el archivo");
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

void mostrarAlumnosInactivos(char *filename)
{
  FILE *file = fopen(filename, "rb"); // Abre el archivo en modo de lectura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Alumno alumno;
  printf("Alumnos Inactivos:\n\n");

  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    if (alumno.estado != 1)
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

  if (file == NULL && opcion != 0)
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
  int *i = malloc(sizeof(int));
  (*i)++;

  FILE *file = fopen(filename, "rb+");
  if (file == NULL)
  {
    printf("Error al abrir el archivo\n");
    // TODO: chequear que si la tabla esta vacia no se corra ningun ejercicio en el menu
    return tabla;
  }

  Alumno alumno;
  while (fread(&alumno, sizeof(Alumno), 1, file) == 1)
  {
    if (alumno.estado == 1)
    {
      *i += 1;
      TipoElemento te = te_crear_con_valor(alumno.legajo, i);
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

// La lista L, deberia ser la lista con las claves a buscar.
// Pasar AVL y HASH ya creados, en el main, no olvidar meter las funciones en el ciclo que dependa de las repeticiones que quieras que se repita.
int AlmacenarTiempos(TablaHash t, ArbolAVL avl, Lista L, Lista resultadoAVL, Lista resultadoHash, Lista rell)
{
  TipoElemento ele, eleAux;
  int longitud = l_longitud(L);
  Iterador it = iterador(L);
  clock_t start, end;
  int acumulador = 0;
  while (hay_siguiente(it))
  {
    ele = siguiente(it);
    if (l_buscar(rell, ele->clave) != NULL)
    {
      // Medir tiempo de búsqueda en AVL
      struct timespec tiempoInicio1, tiempoFin1;
      clock_gettime(CLOCK_MONOTONIC, &tiempoInicio1);

      TipoElemento elementoBuscadoArbol = avl_buscar(avl, ele->clave);

      clock_gettime(CLOCK_MONOTONIC, &tiempoFin1);

      long *tiempoAvl = malloc(sizeof(long));
      *tiempoAvl = (tiempoFin1.tv_sec - tiempoInicio1.tv_sec) * 1000000000L + (tiempoFin1.tv_nsec - tiempoInicio1.tv_nsec);
      TipoElemento eleResuAVL = te_crear_con_valor(ele->clave, tiempoAvl);
      l_agregar(resultadoAVL, eleResuAVL);

      // Medir tiempo de búsqueda en Tabla Hash
      struct timespec tiempoInicio2, tiempoFin2;
      clock_gettime(CLOCK_MONOTONIC, &tiempoInicio2);

      TipoElemento elementoBuscadoTabla = th_recuperar(t, ele->clave);

      clock_gettime(CLOCK_MONOTONIC, &tiempoFin2);

      long *tiempoHash = malloc(sizeof(long));
      *tiempoHash = (tiempoFin2.tv_sec - tiempoInicio2.tv_sec) * 1000000000L + (tiempoFin2.tv_nsec - tiempoInicio2.tv_nsec);
      TipoElemento eleResuHash = te_crear_con_valor(ele->clave, tiempoHash);
      l_agregar(resultadoHash, eleResuHash);
      acumulador++;
    }
  }
  printf("Los elementos de busqueda que coincidieron fueron %i, de %i, por lo tanto los resultados se basan en esos \n", acumulador, longitud);
  return diferenciaTiempos(resultadoAVL, resultadoHash);
}

int diferenciaTiempos(Lista tiempoAvl, Lista tiempoHash)
{
  TipoElemento ele_avl, ele_hash;
  int longitud = l_longitud(tiempoAvl);
  float menorTiempoAvl = 0;
  float menorTiempoHash = 0;
  int acumuladorAvl = 0;
  int acumuladorHash = 0;
  int igualdad = 0;
  Iterador ite_avl = iterador(tiempoAvl);
  Iterador ite_hash = iterador(tiempoHash);
  while (hay_siguiente(ite_avl) && hay_siguiente(ite_hash))
  {
    ele_avl = siguiente(ite_avl);
    ele_hash = siguiente(ite_hash);
    long *valorAvl = ele_avl->valor;
    long *valorHash = ele_hash->valor;
    if (*valorAvl < *valorHash)
    {
      menorTiempoAvl += *valorAvl;
      acumuladorAvl += 1;
    }
    else if (*valorAvl > *valorHash)
    {
      menorTiempoHash += *valorHash;
      acumuladorHash += 1;
    }
    else if (*valorAvl == *valorHash)
    {
      menorTiempoHash += *valorHash;
      acumuladorHash += 1;
      menorTiempoAvl += *valorAvl;
      acumuladorAvl += 1;
    }
  }
  float promedioArbol = menorTiempoAvl / acumuladorAvl;
  float promedioHash = menorTiempoHash / acumuladorHash;
  printf("\nRECORDAR QUE LAS BUSQUEDAS SE BASARON EN LOS VALORES QUE COINCIDIAN\n");
  printf("El promedio de tiempo de busqueda en AVL fue : %.1lf nanosegundos\n", promedioArbol);
  printf("El promedio de tiempo de busqueda en HASH fue : %.1lf nanosegundos\n", promedioHash);
  if (promedioArbol > promedioHash)
  {
    return 1;
  }
  else if (promedioArbol < promedioHash)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

void mostrarArbolRec(NodoArbol raiz, char prefijo[], int esIzquierda)
{
  if (raiz == NULL)
  {
    return;
  }

  printf("%s", prefijo);

  if (esIzquierda)
  {
    printf("|-- ");
  }
  else
  {
    printf("|__ ");
  }

  TipoElemento ele = n_recuperar(raiz);
  printf("%d\n", ele->clave);
  char nuevoPrefijo[1000];
  snprintf(nuevoPrefijo, sizeof(nuevoPrefijo), "%s%s", prefijo, esIzquierda ? "|   " : "    ");

  mostrarArbolRec(n_hijoizquierdo(raiz), nuevoPrefijo, 1);
  mostrarArbolRec(n_hijoderecho(raiz), nuevoPrefijo, 0);
}

// Función para mostrar el árbol
void mostrarArbol(NodoArbol raiz)
{
  if (raiz == NULL)
  {
    return;
  }
  printf("%d\n", n_recuperar(raiz)->clave);

  mostrarArbolRec(n_hijoizquierdo(raiz), "", 1); // Llama a los hijos con prefijos adecuados
  mostrarArbolRec(n_hijoderecho(raiz), "", 0);
}

// Punto 6

// Se desea poder implementar una solución para encontrar de forma rápida los datos de
// las personas que a una fecha determinada se presentaron a vacunar contra el COVID.
// Es decir dada una fecha determinada debería obtener quienes se vacunaron. De cada
// persona se guarda básicamente el DNI, Apellido y Nombre.  Se debe además hacer una
// pantalla de carga donde se pueda especificar la fecha y los datos de las personas que
// se vacunaron en esa fecha.

typedef struct
{
  int dia;
  int mes;
  int anio;
} Fecha;

typedef struct
{
  int dni;
  char nombre[50];
  char apellido[50];

  Fecha fecha;

} Persona;

void ingresarPersona(char *filename)
{
  FILE *file = fopen(filename, "ab"); // Abre el archivo en modo de adición binaria
  if (file == NULL)
  {
    printf("Error al abrir el archivo");
    return;
  }

  Persona persona;
  printf("Ingrese el DNI de la persona: ");
  // Validar que el DNI sea un número positivo, mayor a 0, menor a 8 dígitos
  while (scanf("%d", &persona.dni) != 1 || persona.dni < 1 || persona.dni > 99999999)
  {
    printf("Error: Ingrese un DNI válido (mayor a 0 y menor a 99999999): ");
    fflush(stdin);
  }

  Persona personaExistente;
  FILE *fileExistente = fopen(filename, "rb");
  if (fileExistente != NULL)
  {
    while (fread(&personaExistente, sizeof(Persona), 1, fileExistente) == 1)
    {
      if (personaExistente.dni == persona.dni)
      {
        clearScreen();
        
        printf("Error: La persona con DNI %d ya existe en el archivo.\n", persona.dni);

        // Printeo los datos de la persona existente
        printf("Nombre: %s\n", personaExistente.nombre);
        printf("Apellido: %s\n", personaExistente.apellido);
        printf("Fecha de vacunación: %02d/%02d/%04d\n", personaExistente.fecha.dia, personaExistente.fecha.mes, personaExistente.fecha.anio);

        fclose(fileExistente);
        fclose(file);

        waitForKey();
        return;
      }
    }
    fclose(fileExistente);
  }

  fflush(stdin);
  printf("Ingrese el nombre de la persona: ");
  fgets(persona.nombre, sizeof(persona.nombre), stdin);
  persona.nombre[strcspn(persona.nombre, "\n")] = 0;
  fflush(stdin);

  printf("Ingrese el apellido de la persona: ");
  fgets(persona.apellido, sizeof(persona.apellido), stdin);
  persona.apellido[strcspn(persona.apellido, "\n")] = 0;
  fflush(stdin);

  printf("Ingrese el día de la fecha de vacunación: ");
  while (scanf("%d", &persona.fecha.dia) != 1 || persona.fecha.dia < 1 || persona.fecha.dia > 31)
  {
    printf("Error: Ingrese un día válido (entre 1 y 31): ");
    fflush(stdin);
  }
  fflush(stdin);

  printf("Ingrese el mes de la fecha de vacunación: ");
  while (scanf("%d", &persona.fecha.mes) != 1 || persona.fecha.mes < 1 || persona.fecha.mes > 12)
  {
    printf("Error: Ingrese un mes válido (entre 1 y 12): ");
    fflush(stdin);
  }
  fflush(stdin);

  printf("Ingrese el año de la fecha de vacunación: ");
  while (scanf("%d", &persona.fecha.anio) != 1 || persona.fecha.anio < 2020)
  {
    printf("Error: Ingrese un año válido (mayor o igual a 2020): ");
    fflush(stdin);
  }
  fflush(stdin);

  fwrite(&persona, sizeof(Persona), 1, file);
  printf("Persona ingresada exitosamente.\n");

  fclose(file);
}

void eliminarPersona(char *filename, int dni)
{
  FILE *file = fopen(filename, "rb+");
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Persona persona;
  bool personaEncontrada = false;

  while (fread(&persona, sizeof(Persona), 1, file) == 1)
  {
    if (persona.dni == dni)
    {
      personaEncontrada = true;
      fseek(file, -sizeof(Persona), SEEK_CUR);
      fwrite(&persona, sizeof(Persona), 1, file);
      printf("Persona con DNI %d eliminada.\n", dni);

      waitForKey();
      break;
    }
  }

  if (!personaEncontrada)
  {
    printf("Persona con DNI %d no encontrada.\n", dni);
    waitForKey();
  }

  fclose(file);
}

void modificarPersona(char *filename, int dni)
{
  FILE *file = fopen(filename, "rb+"); // Abre el archivo en modo de lectura/escritura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Persona persona;
  bool personaEncontrada = false;

  while (fread(&persona, sizeof(Persona), 1, file) == 1)
  {
    if (persona.dni == dni)
    {
      personaEncontrada = true;
      printf("Ingrese el nombre de la persona: ");
      fgets(persona.nombre, sizeof(persona.nombre), stdin);
      persona.nombre[strcspn(persona.nombre, "\n")] = 0; // Elimina el salto de línea
      fflush(stdin);

      printf("Ingrese el apellido de la persona: ");
      fgets(persona.apellido, sizeof(persona.apellido), stdin);
      persona.apellido[strcspn(persona.apellido, "\n")] = 0; // Elimina el salto de línea
      fflush(stdin);

      printf("Ingrese el día de la fecha de vacunación: ");
      while (scanf("%d", &persona.fecha.dia) != 1 || persona.fecha.dia < 1 || persona.fecha.dia > 31)
      {
        printf("Error: Ingrese un día válido (entre 1 y 31): ");
        fflush(stdin);
      }
      fflush(stdin);

      printf("Ingrese el mes de la fecha de vacunación: ");
      while (scanf("%d", &persona.fecha.mes) != 1 || persona.fecha.mes < 1 || persona.fecha.mes > 12)
      {
        printf("Error: Ingrese un mes válido (entre 1 y 12): ");
        fflush(stdin);
      }
      fflush(stdin);

      printf("Ingrese el año de la fecha de vacunación: ");
      while (scanf("%d", &persona.fecha.anio) != 1 || persona.fecha.anio < 0)
      {
        printf("Error: Ingrese un año válido (mayor o igual a 0): ");
        fflush(stdin);
      }
      fflush(stdin);

      fseek(file, -sizeof(Persona), SEEK_CUR);    // Vuelve al inicio del registro actual
      fwrite(&persona, sizeof(Persona), 1, file); // Sobrescribe el registro
      printf("Persona con DNI %d modificada.\n", dni);

      waitForKey();
      break;
    }
  }

  if (!personaEncontrada)
  {
    printf("Persona con DNI %d no encontrada.\n", dni);

    waitForKey();
  }

  fclose(file);
}

void mostrarPersonas(char *filename)
{
  FILE *file = fopen(filename, "rb"); // Abre el archivo en modo de lectura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Persona persona;
  printf("Personas:\n\n");

  while (fread(&persona, sizeof(Persona), 1, file) == 1)
  {
    printf("DNI: %d\n", persona.dni);
    printf("Nombre: %s\n", persona.nombre);
    printf("Apellido: %s\n", persona.apellido);
    printf("Fecha de vacunación: %02d/%02d/%04d\n", persona.fecha.dia, persona.fecha.mes, persona.fecha.anio);
    printf("--------------------------\n");
  }

  fclose(file);
}

void mostrarPersonasVacunadasEnFecha(char *filename, Fecha fecha)
{
  FILE *file = fopen(filename, "rb"); // Abre el archivo en modo de lectura binaria
  if (file == NULL)
  {
    perror("Error al abrir el archivo");
    return;
  }

  Persona persona;
  printf("Personas vacunadas el %02d/%02d/%04d:\n\n", fecha.dia, fecha.mes, fecha.anio);

  while (fread(&persona, sizeof(Persona), 1, file) == 1)
  {
    if (persona.fecha.dia == fecha.dia && persona.fecha.mes == fecha.mes && persona.fecha.anio == fecha.anio)
    {
      printf("DNI: %d\n", persona.dni);
      printf("Nombre: %s\n", persona.nombre);
      printf("Apellido: %s\n", persona.apellido);
      printf("--------------------------\n");
    }
  }

  fclose(file);
}

// ingresarPersonas
// modificarPersona
// eliminarPersona
// mostrarPersonas
// mostrarPersonasVacunadasEnFecha
void ABM_Personas(char *filename)
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
    int dni;
    printf("0. Salir\n");
    printf("1. Agregar persona\n");
    printf("2. Modificar persona\n");
    printf("3. Eliminar persona\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    fflush(stdin);

    switch (opcion)
    {
    case 0:
      flag_abm = false;
      break;

    case 1:
      ingresarPersona(filename);
      break;

    case 2:
      printf("Ingrese el DNI de la persona a modificar: ");
      scanf("%d", &dni);
      fflush(stdin);
      modificarPersona(filename, dni);
      break;

    case 3:
      printf("Ingrese el DNI de la persona a eliminar: ");
      scanf("%d", &dni);
      fflush(stdin);
      eliminarPersona(filename, dni);
      break;
    }
  }
  if (file != NULL)
  {
    fclose(file);
  }
}

int main()
{
  // TODO: en el menu hay que preguntar por el nombre del archivo
  // TODO: en el menu hay que preguntar si quiere hacer cambios en el archivo
  //  abm_alumnos("alumnos.dat");

  //  TablaHash tabla = punto4("alumnos.dat");

  //  printf("\n");

  //  mostrarAlumnosActivos("alumnos.dat");
  //  mostrarAlumnosInactivos("alumnos.dat");
  //  th_mostrar_solo_ocupados(tabla);
  //  TipoElemento te = th_recuperar(tabla, 195311);
  //  if (te != NULL)
  //  {
  //    int *valor = te->valor;
  //    printf("Legajo: %d\nPosicion en el archivo: %d\n", te->clave, *valor);
  //  }
  //  else
  //  {
  //    printf("Elemento no encontrado\n");
  //  }

  // //Punto5
  // Lista resultadosHash = l_crear();
  // Lista resultadosAvl = l_crear();
  // int repeticiones;

  // // VALIDAR QUE SEA MAYOR A 0;
  // printf("Ingrese la cantidad de veces que quiere repetir el proceso: \n");
  // scanf("%i", &repeticiones);
  // int minimo;
  // int maximo;
  // // VALIDAR QUE LA CANTIDAD DE CLAVES A GENERAR NO SEAN > 5000
  // printf("Ingrese la cantidad de claves a generar: \n");
  // scanf("%i", &cantidad);

  // printf("Ingrese el numero menor del rango de las claves a generar: \n");
  // scanf("%i", &minimo);

  // // VALIDAR QUE SEA MAYOR AL MENOR Y QUE SEA MENOR A 100.000.
  // printf("Ingrese el numero mayor del rango de las claves a generar: \n");
  // scanf("%i", &maximo);

  // int masArb = 0;
  // int masHash = 0;
  // for (int i = 0; i < repeticiones; i++)
  // {
  //   int cantidadBus;
  //   // VALIDAR QUE NO SEA MAYOR A LA CANTIDAD DE CLAVES GENERADAS
  //   printf("Ingrese la cantidad de claves a a generar (Para la busqueda en las estructuras): \n");
  //   scanf("%i", &cantidadBus);
  //   srand(time(NULL));
  //   Lista clavesParaRellenar = Generarlistaclaves(cantidad, minimo, maximo);
  //   Lista clavesParaBuscar = Generarlistaclaves(cantidadBus, minimo, maximo);
  //   ArbolAVL arbol = crearAVL(clavesParaRellenar);
  //   TablaHash hash5 = crearTablaHash(clavesParaRellenar);
  //   int resuPar = AlmacenarTiempos(hash5, arbol, clavesParaBuscar, resultadosAvl, resultadosHash, clavesParaRellenar);
  //   if (resuPar == 0)
  //   {
  //     masArb++;
  //   }
  //   else if (resuPar == 1)
  //   {
  //     masHash++;
  //   }
  //   printf("------------------------\n");
  // }
  // printf("De %i repeticiones del proceso, en %i, la busqueda fue mas rapida en AVL\n\n", repeticiones, masArb);
  // printf("De %i repeticiones del proceso, en %i, la busqueda fue mas rapida en HASH\n\n", repeticiones, masHash);

  // Punto 6
  ABM_Personas("personas.dat");
  mostrarPersonas("personas.dat");

  int dia, mes, anio;
  printf("Ingrese el día de la fecha de vacunación: ");
  while (scanf("%d", &dia) != 1 || dia < 1 || dia > 31)
  {
    printf("Error: Ingrese un día válido (entre 1 y 31): ");
    fflush(stdin);
  }
  fflush(stdin);

  printf("Ingrese el mes de la fecha de vacunación: ");
  while (scanf("%d", &mes) != 1 || mes < 1 || mes > 12)
  {
    printf("Error: Ingrese un mes válido (entre 1 y 12): ");
    fflush(stdin);
  }
  fflush(stdin);

  printf("Ingrese el año de la fecha de vacunación: ");
  while (scanf("%d", &anio) != 1 || anio < 2020)
  {
    printf("Error: Ingrese un año válido (mayor o igual a 2020): ");
    fflush(stdin);
  }
  fflush(stdin);

  Fecha fecha = {dia, mes, anio};
  mostrarPersonasVacunadasEnFecha("personas.dat", fecha);

  return 0;
}

// gcc -o output ../libs/hash/tabla_hash_lista_colisiones.c ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c ../libs/nodos/nodo.c ../libs/arboles/arbol-binario.c ../libs/colas/colas_arreglos.c ../libs/arboles/arbol-avl.c ../libs/arboles/arbol-binario-busqueda.c main.c