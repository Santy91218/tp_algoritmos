#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdlib.h>
#include <string.h>

#define reservarMemoriaNodo( X , Y , Z , W ) ( \
            ( ( X ) = (typeof( X ))malloc( Y ) ) == NULL || \
            ( ( Z ) = malloc( W ) ) == NULL   ? \
                free( X ), 0 : 1  )

#define MAX(x,y) ((x) > (y) ? (x) : (y))


typedef struct sNodo{
        void * info;
        unsigned tam;
        struct sNodo *der, *izq;
}tNodo;

typedef tNodo * tArbolBin;


/// Crear un árbol binario vacío
void crearArbolBin(tArbolBin * p);

///bsucar nodo
tNodo * buscarNodoPorClave(const tArbolBin * p,
                           const void * clave,
                           int (*cmp)(const void *, const void *));

tNodo ** buscarNodoDoblePorClave( tArbolBin * p,
                            const void * clave,
                            int (*cmp)(const void *, const void *));

/// Insertar un elemento en el árbol binario
int insertarEnArbolBin(tArbolBin * p, void * info, unsigned tam, int (*cmp)(const void *, const void*));

/// Recorrer el árbol en orden (izquierda-raíz-derecha)
void recorrerInOrden(const tArbolBin * p, void (*mostrar)(const void *));

/// Recorrer el árbol en preorden (raíz-izquierda-derecha)
void recorrerPreOrden(const tArbolBin * p, void (*mostrar)(const void *));

/// Recorrer el árbol en postorden (izquierda-derecha-raíz)
void recorrerPostOrden(const tArbolBin * p, void (*mostrar)(const void *));

/// Encontrar el nodo mayor (más a la derecha)
tNodo * mayorNodoArbolBin(tArbolBin * p);

/// Encontrar el nodo menor (más a la izquierda)
tNodo * menorNodoArbolBin(tArbolBin * p);

/// Encontrar la dirección del nodo mayor
tNodo ** mayorDirNodoArbolBin(tArbolBin * p);

/// Encontrar la dirección del nodo menor
tNodo ** menorDirNodoArbolBin(tArbolBin * p);

/// Calcular la altura del árbol
int mayorAlturaArbolBin(tArbolBin * p);

/// Eliminar todo el árbol (liberar memoria)
void eliminarArbol(tArbolBin * p);

/// Eliminar la raíz del árbol
int eliminarRaiz(tArbolBin * p);

/// Cortar las hojas del árbol
int cortarHojas(tArbolBin * p);

/// Contar el número de hojas
int contarHojas(tArbolBin * p);

/// Ejecutar una acción en todos los nodos de una altura específica
void accionNodoNAltura(tArbolBin * p, unsigned altura, void (*accion)(const void *));


void recorrerInOrdenPlus(const tArbolBin * p, size_t tam,void (*accion)(const void *, unsigned, void *), void * parametros);

#endif // ARBOL_H_INCLUDED
