#ifndef COLAS_H
#define COLAS_H

#include <stdbool.h>
#include "../elementos/tipo_elemento.h"

struct ColaRep;
typedef struct ColaRep *Cola;

/**
 * @brief Crea una nueva cola vacía.
 * 
 * @return Cola vacía.
 */
Cola c_crear();

/**
 * @brief Encola un elemento en la cola.
 * 
 * @param cola La cola en la que se va a encolar el elemento.
 * @param elemento El elemento a encolar.
 * @return true si se pudo encolar el elemento, false en caso contrario.
 */
bool c_encolar(Cola cola, TipoElemento elemento);

/**
 * @brief Desencola un elemento de la cola.
 * 
 * @param cola La cola de la que se va a desencolar el elemento.
 * @return El elemento desencolado.
 */
TipoElemento c_desencolar(Cola cola);

/**
 * @brief Verifica si la cola está vacía.
 * 
 * @param cola La cola a verificar.
 * @return true si la cola está vacía, false en caso contrario.
 */
bool c_es_vacia(Cola cola);

/**
 * @brief Verifica si la cola está llena.
 * 
 * @param cola La cola a verificar.
 * @return true si la cola está llena, false en caso contrario.
 */
bool c_es_llena(Cola cola);

/**
 * @brief Muestra los elementos de la cola.
 * 
 * @param cola La cola a mostrar.
 */
void c_mostrar(Cola cola);

/**
 * @brief Recupera el elemento en el frente de la cola sin desencolarlo.
 * 
 * @param cola La cola de la que se va a recuperar el elemento.
 * @return El elemento en el frente de la cola.
 */
TipoElemento c_recuperar(Cola cola);

#endif // COLAS_H
