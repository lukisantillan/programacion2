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
  int *i = malloc(sizeof(int));
  *i = 1;

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
      i++;
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
void AlmacenarTiempos(TablaHash t, ArbolAVL avl, Lista L, Lista resultadoAVL, Lista resultadoHash, Lista rell)
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
      start = clock();
      eleAux = avl_buscar(avl, ele->clave);
      end = clock();
      double *tiempoAVL = malloc(sizeof(double));
      *tiempoAVL = (double)(end - start) / CLOCKS_PER_SEC;
      TipoElemento eleResuAVL = te_crear_con_valor(ele->clave, tiempoAVL);
      l_agregar(resultadoAVL, eleResuAVL);

      // Medir tiempo de búsqueda en Tabla Hash
      start = clock();
      eleAux = th_recuperar(t, ele->clave);
      end = clock();
      double *tiempoHash = malloc(sizeof(double));
      *tiempoHash = (double)(end - start) / CLOCKS_PER_SEC;
      TipoElemento eleResuHash = te_crear_con_valor(ele->clave, tiempoHash);
      l_agregar(resultadoHash, eleResuHash);
      acumulador++;
    }
  }
  printf("Los elementos de busqueda que coincidieron fueron %i, de %i, por lo tanto los resultados se basan en esos \n", acumulador, longitud);
}

void diferenciaTiempos(Lista tiempoAvl, Lista tiempoHash)
{
  TipoElemento ele_avl, ele_hash;
  int longitud = l_longitud(tiempoAvl);
  int menorTiempoAvl = 0;
  int menorTiempoHash = 0;
  int igualdad = 0;
  Iterador ite_avl = iterador(tiempoAvl);
  Iterador ite_hash = iterador(tiempoHash);
  while (hay_siguiente(ite_avl) && hay_siguiente(ite_hash))
  {
    ele_avl = siguiente(ite_avl);
    ele_hash = siguiente(ite_hash);
    double *valorAvl = malloc(sizeof(double));
    valorAvl = ele_avl->valor;
    double *valorHash = malloc(sizeof(double));
    valorHash = ele_hash->valor;
    if (*valorAvl < *valorHash)
    {
      menorTiempoAvl++;
    }
    else if (*valorAvl > *valorHash)
    {
      menorTiempoHash++;
    }
    else if (*valorAvl == *valorHash)
    {
      igualdad++;
    }
  }
  printf("RECORDAR QUE LAS BUSQUEDAS SE BASARON EN LOS VALORES QUE COINCIDIAN\n");
  printf("\t\t -- La cantidad de elementos que coincidieron en el total de las iteraciones fueron : %i--\n", longitud);
  printf("El tiempo de busqueda fue menor en %i de %i claves en AVL\n", menorTiempoAvl, longitud);
  printf("El tiempo de busqueda fue menor en %i de %i claves en Hash\n", menorTiempoHash, longitud);
  printf("El tiempo de busqueda fue igual en %i de %i\n", igualdad, longitud);
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

int main()
{
  // TODO: en el menu hay que preguntar por el nombre del archivo
  // TODO: en el menu hay que preguntar si quiere hacer cambios en el archivo
  //   abm_alumnos("alumnos.dat");

  //   TablaHash tabla = punto4("alumnos.dat");

  //   printf("\n");

  //   mostrarAlumnosActivos("alumnos.dat");
  //   th_mostrar_solo_ocupados(tabla);
  //   TipoElemento te = th_recuperar(tabla, 195311);
  //   if (te != NULL)
  //   {
  //     printf("Legajo: %d\nPosicion en el archivo: %d", te->clave, te->valor);
  //   }
  //   else
  //   {
  //     printf("Elemento no encontrado\n");
  //   }
  Lista resultadosHash = l_crear();
  Lista resultadosAvl = l_crear();
  int repeticiones;

  //VALIDAR QUE SEA MAYOR A 0;
  printf("Ingrese la cantidad de veces que quiere repetir el proceso: \n");
  scanf("%i", &repeticiones);
  int minimo;
  int maximo;
  //VALIDAR QUE LA CANTIDAD DE CLAVES A GENERAR NO SEAN > 10000
  printf("Ingrese la cantidad de claves a generar: \n");
  scanf("%i", &cantidad);

  
  printf("Ingrese el numero menor del rango de las claves a generar: \n");
  scanf("%i", &minimo);

  //VALIDAR QUE SEA MAYOR AL MENOR Y QUE SEA MENOR A 100.000.
  printf("Ingrese el numero mayor del rango de las claves a generar: \n");
  scanf("%i", &maximo);

  for (int i = 0; i < repeticiones; i++)
  {
    int cantidadBus;
    //VALIDAR QUE NO SEA MAYOR A LA CANTIDAD DE CLAVES GENERADAS
    printf("Ingrese la cantidad de claves a a generar (Para la busqueda en las estructuras): \n");
    scanf("%i", &cantidadBus);
    srand(time(NULL));
    Lista clavesParaRellenar = Generarlistaclaves(cantidad, minimo, maximo);
    Lista clavesParaBuscar = Generarlistaclaves(cantidadBus, minimo, maximo);
    ArbolAVL arbol = crearAVL(clavesParaRellenar);
    TablaHash hash5 = crearTablaHash(clavesParaRellenar);
    AlmacenarTiempos(hash5, arbol, clavesParaBuscar, resultadosAvl, resultadosHash, clavesParaRellenar);
    printf("------------------------\n");
  }

  diferenciaTiempos(resultadosAvl, resultadosHash);
  return 0;
}

// gcc -o output ../libs/hash/tabla_hash_lista_colisiones.c ../libs/elementos/tipo_elemento.c ../libs/listas/listas_arreglos.c ../libs/nodos/nodo.c ../libs/arboles/arbol-binario.c ../libs/colas/colas_arreglos.c ../libs/arboles/arbol-avl.c ../libs/arboles/arbol-binario-busqueda.c main.c