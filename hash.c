#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define LARGO_INICIAL 5

typedef void (*hash_destruir_dato_t)(void *);

typedef enum estado {
	libre,
	ocupado,
	borrado
} estado_t;

typedef struct hash_campo {
    char* clave;
    void* valor;
    estado_t estado; 
} hash_campo_t;

typedef struct hash {
	size_t cantidad;                  
    size_t largo;                     
    size_t carga;                     
    hash_campo_t* tabla; 
    hash_destruir_dato_t destruir_dato; 
} hash_t;

typedef struct hash_iter {	//no estoy seguro si estos son los atributos del iterador.
	hash_t* hash;
	size_t posicion;
} hash_iter_t;

/* Crea el hash*/
//preguntar por la carga del hash abierto.
hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));
	if(hash == NULL) return NULL;
	hash_campo_t* tabla = malloc(sizeof(hash_campo_t) * LARGO_INICIAL);
	if(tabla == NULL) return NULL;
	hash->tabla = tabla;
	hash->cantidad = 0;
	hash->largo = LARGO_INICIAL;
	hash->carga = 0;
	hash->destruir_dato = destruir_dato;
	return hash;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)*/
bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
	return false;
}

/* Borra un elemento del hash y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura hash fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void* hash_borrar(hash_t* hash, const char* clave) {
	return NULL;
}

/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada*/
void* hash_obtener(const hash_t* hash, const char* clave) {
	return NULL;
}

/* Determina si clave pertenece o no al hash.
 * Pre: La estructura hash fue inicializada*/
bool hash_pertenece(const hash_t* hash, const char* clave) {
	return false;
}

/* Devuelve la cantidad de elementos del hash.
 * Pre: La estructura hash fue inicializada*/
size_t hash_cantidad(const hash_t* hash) {
	return 0;
}

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura hash fue inicializada
 * Post: La estructura hash fue destruida*/
void hash_destruir(hash_t* hash) {
	free(hash->tabla);
	free(hash);
}

/* Iterador del hash */

// Crea iterador
hash_iter_t* hash_iter_crear(const hash_t* hash) {
	return NULL;
}

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t* iter) {
	return false;
}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char* hash_iter_ver_actual(const hash_iter_t* iter) {
	return NULL;
}

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t* iter) { 
	return false;
}

// Destruye iterador
void hash_iter_destruir(hash_iter_t* iter) {

}