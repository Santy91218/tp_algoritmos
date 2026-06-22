#include "arbol.h"
#include <stdio.h>

void crearArbolBin(tArbolBin * p)
{
    *p=NULL;
}

tNodo * buscarNodoPorClave(const tArbolBin * p,
                           const void * clave,
                           int (*cmp)(const void *, const void *))
{
    int rc;

    while(*p)
    {
        rc = cmp(clave, (*p)->info);

        if(rc < 0)
            p = &(*p)->izq;
        else if(rc > 0)
            p = &(*p)->der;
        else
            return *p;   // Encontrado
    }

    return NULL; // No encontrado
}

tNodo ** buscarNodoDoblePorClave(tArbolBin * p,
                            const void * clave,
                            int (*cmp)(const void *, const void *))
{
    int rc;

    while(*p)
    {
        rc = cmp(clave, (*p)->info);

        if(rc < 0)
            p = &(*p)->izq;
        else if(rc > 0)
            p = &(*p)->der;
        else
            return p;
    }

    return NULL;
}

int insertarEnArbolBin(tArbolBin * p, void * info, unsigned tam, int (*cmp)(const void *, const void*))
{
    tNodo * nuevo;
    int rc;

    while(*p!=NULL)
    {
        if((rc=cmp(info,(*p)->info))<0)
        {
            p=&(*p)->izq;
        }
        else if(rc>0)
        {
            p=&(*p)->der;
        }
        else
            return 0;
    }
    if(!reservarMemoriaNodo(nuevo, sizeof(tNodo), nuevo->info, tam))
        return 0;

    nuevo->tam=tam;
    memcpy(nuevo->info, info,tam);
    nuevo->der=nuevo->izq=NULL;
    *p=nuevo;
    return 1;
}

void recorrerInOrden(const tArbolBin * p,void (*mostrar)(const void *))
{
    if(*p==NULL)
        return;
    recorrerInOrden(&(*p)->izq, mostrar);
    mostrar((*p)->info);
    recorrerInOrden(&(*p)->der, mostrar);
}

void recorrerInOrdenPlus(const tArbolBin * p, size_t tam,void (*accion)(const void *, unsigned, void *), void * parametros)
{
    if(*p==NULL)
        return;
    recorrerInOrdenPlus(&(*p)->izq, tam, accion, parametros);
    const void * aux = (*p)->info;
    unsigned nro = *(unsigned*)((char*)(*p)->info + tam);
    accion(aux , nro , parametros);
    recorrerInOrdenPlus(&(*p)->der,tam ,accion, parametros);
}


void recorrerPreOrden(const tArbolBin * p,void (*mostrar)(const void *))
{
    if(*p==NULL)
        return;
    mostrar((*p)->info);
    recorrerInOrden(&(*p)->izq, mostrar);
    recorrerInOrden(&(*p)->der, mostrar);
}

void recorrerPostOrden(const tArbolBin * p,void (*mostrar)(const void *))
{
    if(*p== NULL)
        return;
    recorrerInOrden(&(*p)->izq, mostrar);
    recorrerInOrden(&(*p)->der, mostrar);
    mostrar((*p)->info);
}

tNodo * mayorNodoArbolBin(tArbolBin * p)
{
    if(!(*p))
        return NULL;
    if((*p)->der==NULL)
        return (*p);
    return mayorNodoArbolBin(&(*p)->der);
}

tNodo * menorNodoArbolBin(tArbolBin * p)
{
    if(!(*p))
        return NULL;
    if((*p)->izq==NULL)
        return (*p);
    return menorNodoArbolBin(&(*p)->izq);
}

tNodo ** mayorDirNodoArbolBin(tArbolBin * p)
{
    if(!(*p))
        return NULL;
    if((*p)->der==NULL)
        return (p);
    return mayorDirNodoArbolBin(&(*p)->der);
}

tNodo ** menorDirNodoArbolBin(tArbolBin * p)
{
    if(!(*p))
        return NULL;
    if((*p)->izq==NULL)
        return (p);
    return menorDirNodoArbolBin(&(*p)->izq);
}

int mayorAlturaArbolBin(tArbolBin * p)
{
    if(!*p)
        return 0;
    return MAX(mayorAlturaArbolBin(&(*p)->izq),mayorAlturaArbolBin(&(*p)->der))+1;
}

void eliminarArbol(tArbolBin * p)
{
    if(!*p)
        return;

    eliminarArbol(&(*p)->izq);
    eliminarArbol(&(*p)->der);

    free((*p)->info);
    free(*p);
    *p=NULL;
    return;
}

int eliminarRaiz(tArbolBin * p)
{
    tNodo ** rem, *elim;

    if(!*p)
        return 0;

    free((*p)->info);
    if(!(*p)->der && !(*p)->izq)
    {
        free(*p);
        return 1;
    }

    if(mayorAlturaArbolBin(&(*p)->izq)>mayorAlturaArbolBin(&(*p)->der))
    {
        rem = mayorDirNodoArbolBin(&(*p)->izq);
    }
    else
        rem = menorDirNodoArbolBin(&(*p)->der);

    elim = *rem;
    (*p)->info = elim->info;
    (*p)->tam = elim->tam;

    if(elim->der)
        *rem=elim->der;
    else
        *rem=elim->izq;
    free(elim);
    return 1;
}

int cortarHojas(tArbolBin * p)
{
    return 0;
}

int contarHojas(tArbolBin * p)
{
    return 0;
}

void accionNodoNAltura(tArbolBin * p, unsigned altura, void (*accion)(const void *))
{
    return;
}
