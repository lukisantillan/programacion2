#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "../libs/hash/tabla_hash.h"
#include "../libs/elementos/tipo_elemento.h"

/**
 * Permite ingresar alumnos al archivo.
 *
 * @param filename -  Un puntero al nombre del archivo al que se le quiere ingresar alumnos.
 * @return VOID.
 */
void ingresarAlumno(char *filename);

/**
 * Permite realizar una baja logica de un alumno.
 *
 * @param filename - Un puntero al nombre del archivo al que se le quiere hacer una baja.
 * @param legajo - Un entero, que hace referencia al legajo del alumno. 
 * @return VOID.
 */
void bajaLogicaAlumno(char *filename, int legajo);

/**
 * Devuelve por pantalla los alumnos activos.
 *
 * @param filename -  Un puntero al nombre del archivo al que se quiere leer.
 * @return VOID
 */
void mostrarAlumnosActivos(char *filename);

/**
 * Permite modificar un registro de alumnos.
 *
 * @param filename - Un puntero al nombre del archivo al que se le quiere hacer una modificacion.
 * @param legajo - Un entero, que hace referencia al legajo del alumno. 
 * @return VOID.
 */
void modificacion(char *filename, int legajo);

/**
 * Genera un menú que permite elegir el tipo de acción que se quiere hacer sobre el archivo.
 *
 * @param filename -  Un puntero al nombre del archivo al que se le quiere hacer ABM.
 * @return VOID
 */
void abm_alumnos(char *filename);

/**
 * Crea una nueva tabla hash con un tamaño inicial y una función hash especificada.
 *
 * @param clave -  Entero que representa la clave a hashear.
 * @return Int - Clave que sufrio el cambio hecho por la función Hash
 */
int funcion_hash_alumnos(int clave);

TablaHash punto3(char *filename);