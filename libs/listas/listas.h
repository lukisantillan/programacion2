#ifndef LISTAS_H
#define LISTAS_H

#include <stdbool.h>
#include "../elementos/tipo_elemento.h"

struct ListaRep;
typedef struct ListaRep *Lista;

struct IteradorRep;
typedef struct IteradorRep *Iterador;

/**
 * @brief Crea una nueva lista vacía.
 * 
 * @return Lista La lista creada.
 */
Lista l_crear();

/**
 * @brief Verifica si la lista está vacía.
 * 
 * @param lista La lista a verificar.
 * @return true si la lista está vacía, false en caso contrario.
 */
bool l_es_vacia(Lista lista);

/**
 * @brief Verifica si la lista está llena.
 * 
 * @param lista La lista a verificar.
 * @return true si la lista está llena, false en caso contrario.
 */
bool l_es_llena(Lista lista);

/**
 * @brief Obtiene la longitud de la lista.
 * 
 * @param lista La lista de la cual se quiere obtener la longitud.
 * @return int La longitud de la lista.
 */
int l_longitud(Lista lista);

/**
 * @brief Agrega un elemento al final de la lista.
 * 
 * @param lista La lista a la cual se quiere agregar el elemento.
 * @param elemento El elemento a agregar.
 * @return true si se pudo agregar el elemento, false en caso contrario.
 */
bool l_agregar(Lista lista, TipoElemento elemento);

/**
 * @brief Borra un elemento de la lista dado su clave. En caso de haber más de un elemento con la misma clave, se borra el primero.
 * 
 * @param lista La lista de la cual se quiere borrar el elemento.
 * @param clave La clave del elemento a borrar.
 * @return true si se pudo borrar el elemento, false en caso contrario.
 */
bool l_borrar(Lista lista, int clave);

/**
 * @brief Busca un elemento en la lista dado su clave.
 * 
 * @param lista La lista en la cual se quiere buscar el elemento.
 * @param clave La clave del elemento a buscar.
 * @return TipoElemento El elemento encontrado, o NULL si no se encontró.
 */
TipoElemento l_buscar(Lista lista, int clave);

/**
 * @brief Inserta un elemento en una posición específica de la lista.
 * 
 * @param lista La lista en la cual se quiere insertar el elemento.
 * @param elemento El elemento a insertar.
 * @param pos La posición en la cual se quiere insertar el elemento.
 * @return true si se pudo insertar el elemento, false en caso contrario.
 */
bool l_insertar(Lista lista, TipoElemento elemento, int pos);

/**
 * @brief Elimina un elemento de la lista dado su posición.
 * 
 * @param lista La lista de la cual se quiere eliminar el elemento.
 * @param pos La posición del elemento a eliminar.
 * @return true si se pudo eliminar el elemento, false en caso contrario.
 */
bool l_eliminar(Lista lista, int pos);

/**
 * @brief Recupera un elemento de la lista dado su posición.
 * 
 * @param lista La lista de la cual se quiere recuperar el elemento.
 * @param pos La posición del elemento a recuperar.
 * @return TipoElemento El elemento recuperado, o NULL si no se pudo recuperar.
 */
TipoElemento l_recuperar(Lista lista, int pos);

/**
 * @brief Muestra por pantalla los elementos de la lista.
 * 
 * @param lista La lista a mostrar.
 */
void l_mostrar(Lista lista);

/**
 * @brief Crea un iterador para recorrer la lista.
 * 
 * @param lista La lista a iterar.
 * @return Iterador El iterador creado.
 */
Iterador iterador(Lista lista);

/**
 * @brief Verifica si hay un siguiente elemento en el iterador.
 * 
 * @param iterador El iterador a verificar.
 * @return true si hay un siguiente elemento, false en caso contrario.
 */
bool hay_siguiente(Iterador iterador);

/**
 * @brief Obtiene el elemento actual del iterador y avanza al siguiente.
 * 
 * @param iterador El iterador del cual se quiere obtener el siguiente elemento.
 * @return TipoElemento El siguiente elemento del iterador.
 */
TipoElemento siguiente(Iterador iterador);

#endif // LISTAS_H
