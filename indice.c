#include"indice.h"
#include"arbol.h"
void ind_crear(t_indice* ind, size_t tam_clave, int (*cmp)(const void*, const void*))
{
    ind->raiz_arbol=NULL;
    ind->tam=tam_clave;
    ind->comparacion=cmp;
}
int ind_insertar(t_indice* ind, void *clave, unsigned nro_reg)
{
    void * aux = malloc(ind->tam + sizeof(unsigned));
    if(!aux)
        return 0;
    memcpy(aux, clave, ind->tam);
    memcpy((char*)aux + ind->tam, &nro_reg, sizeof(unsigned));
    insertarEnArbolBin(&ind->raiz_arbol, aux ,ind->tam + sizeof(unsigned) , ind->comparacion);
    free(aux);
    return 1;
}

int ind_eliminar(t_indice* ind, void *clave, unsigned *nro_reg)
{
    tNodo ** aux = buscarNodoDoblePorClave(&ind->raiz_arbol, clave, ind->comparacion);
    if(!aux || !(*aux))
        return 0;
    void * datos = (*aux)->info;
    memcpy(nro_reg, (char*)datos + ind->tam, sizeof(unsigned));
    eliminarRaiz(aux);
    return 1;
}

int ind_buscar(const t_indice* ind, void *clave, unsigned *nro_reg)
{
    tArbolBin arbol_aux = ind->raiz_arbol;
    void * clave_aux;
    tNodo ** aux = buscarNodoDoblePorClave(&arbol_aux, clave, ind->comparacion);
    if(!aux || !(*aux))
    {
        unsigned error = 0;
        memcpy(nro_reg, &error, sizeof(unsigned));
        return 0;
    }
    clave_aux = (*aux)->info;
    memcpy(nro_reg,(char*)clave_aux + ind->tam, sizeof(unsigned));
    return 1;
}
int ind_grabar(const t_indice* ind, const char* path)
{
    FILE * pj = fopen(path, "wb");
    if(!pj)
        return 0;
    grabar_in_orden(ind->raiz_arbol, pj);
    fclose(fp);
    return 1;
}
void ind_vaciar(t_indice* ind)
{
    eliminarArbol(&ind->raiz_arbol);
    ind->tam=0;
    ind->comparacion=NULL;
}
int ind_recorrer(const t_indice* ind, void (*accion)(const void *, unsigned, void *), void* param)
{
    if(ind->raiz_arbol==NULL)
        return 0;
    recorrerInOrdenPlus(&ind->raiz_arbol, ind->tam, accion, param);
    return 1;
}

void grabar_in_orden(tArbolBin * arb, void * param)
{
    if(!arb)
        return;

    grabar_in_orden(arb->izq, param);
    fwrite(arb->info, ind->tam, 1, fp);
    grabar_in_orden(arb->der, param);
    return;
}


int ind_cargar(t_indice* ind, const char* path)
{
    int registros;
    FILE * fp = fopen(path, "rb");
    if(!fp)
        return 0;
    fseek(fp,0,SEEK_END);
    registros = ftell(fp)/ind->tam + sizeof(unsigned);
    void * vec = malloc(registros * (ind->tam));
    if(!vec)
    {
        fclose(fp);
        return 0;
    }
    fseek(fp, 0, SEEK_SET);
    fread(vec, ind->tam, registros, fp);

    ///comienza la insercion en el arbol

    fclose(fp);
    return 1;
}

int insertar_y_balancear(t_indice * ind ,void * vec, int inicio, int fin)
{
    void * aux = vec;
    char * aux_clave, * aux_reg;
    unsigned reg;
    int medio;
    if(inicio > fin)
        return 0;

    medio = (inicio + fin)/2;
    aux = (char*)aux + (medio*(ind->tam + sizeof(unsigned)));
    memcpy(&reg, (char*)aux + ind->tam, sizeof(unsigned));

    ind_insertar(ind, aux,reg);
    insertar_y_balancear(ind, vec, inicio, medio-1);
    insertar_y_balancear(ind, vec, medio+1, fin);
    return 1;
}
