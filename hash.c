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
    const char* clave;
    void* valor;
    estado_t estado; 
} hash_campo_t;

typedef struct hash {
	size_t cantidad;                  
    size_t largo;                     
    size_t carga;                     
    hash_campo_t** tabla; 
    hash_destruir_dato_t destruir_dato; 
} hash_t;

typedef struct hash_iter {	//no estoy seguro si estos son los atributos del iterador.
	hash_t* hash;
	size_t posicion;
} hash_iter_t;

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura hash fue inicializada
 * Post: La estructura hash fue destruida*/
void hash_destruir(hash_t* hash) {
	free(hash->tabla);
	free(hash);
}

size_t funcion_hash(const char* clave, size_t largo_tabla) {
    size_t hashval;
    for (hashval = 0; *clave != '\0'; clave++) hashval = *clave + 31*hashval;
    return hashval % largo_tabla;
}

hash_campo_t* campo_crear() {
	hash_campo_t* campo = malloc(sizeof(hash_campo_t));
	if(campo == NULL) return NULL;
	campo->clave = NULL;
	campo->valor = NULL;
	campo->estado = libre;
	return campo;
}

bool rellenar_tabla(hash_t* hash, int inicio) {
	for(int i=inicio; i<hash->largo; i++) {
		hash_campo_t* campo = campo_crear();
		if(campo == NULL) {
			hash_destruir(hash);
			return false;
		}
		hash->tabla[i] = campo;
	}
	return true;
}

/* Crea el hash*/
//preguntar por la carga del hash abierto.
hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));
	if(hash == NULL) return NULL;
	hash_campo_t** tabla = malloc(sizeof(hash_campo_t*) * LARGO_INICIAL);
	if(tabla == NULL) return NULL;
	hash->tabla = tabla;
	hash->cantidad = 0;
	hash->largo = LARGO_INICIAL;
	hash->carga = 0;
	if(!rellenar_tabla(hash, 0)) return NULL;
	hash->destruir_dato = destruir_dato;
	return hash;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)*/
bool hash_guardar(hash_t* hash, const char* clave, void* dato) {
	size_t posicion = funcion_hash(clave, hash->largo);
	hash_campo_t** tabla = hash->tabla;
	while(tabla[posicion]->estado != libre && posicion < hash->largo) {
		posicion++;
	}
	hash_campo_t* campo = tabla[posicion];
	campo->clave = clave;
	campo->valor = dato;
	campo->estado = ocupado;
	hash->cantidad++;
	return true;
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

void hasheando_por_hay(size_t* posicion, const hash_t* hash, const char* clave) {
	while(hash->tabla[*posicion]->estado != libre && hash->tabla[*posicion]->clave != clave && *posicion < hash->largo) {
		*posicion += 1;
	}
}

/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada*/
void* hash_obtener(const hash_t* hash, const char* clave) {
	size_t posicion = funcion_hash(clave, hash->largo);
	hasheando_por_hay(&posicion, hash, clave);
	if(hash->tabla[posicion]->clave != clave) return NULL;
	return hash->tabla[posicion]->valor;
}

/* Determina si clave pertenece o no al hash.
 * Pre: La estructura hash fue inicializada*/
bool hash_pertenece(const hash_t* hash, const char* clave) {
	size_t posicion = funcion_hash(clave, hash->largo);
	hasheando_por_hay(&posicion, hash, clave);
	return hash->tabla[posicion]->clave == clave;
}

/* Devuelve la cantidad de elementos del hash.
 * Pre: La estructura hash fue inicializada*/
size_t hash_cantidad(const hash_t* hash) {
	return hash->cantidad;
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