#include"indice.h"


typedef struct{
        int dni;
}t_clave;
//typedef int t_clave;

int cmpDNI(const void* d1, const void* d2)
{
    int *a=(int*)d1;
    int *b=(int*)d2;
    return (*a) - (*b);
}

void verClave(const void * d1)
{
    t_clave * aux = (t_clave*)d1;
    printf("%d\n", aux->dni);
}

void verIndice(const void * d1, unsigned nro, void * param)
{
    t_clave * aux = (t_clave*)d1;
    printf("%d  e indice: %d\n", aux->dni, nro);
}

int main()
{
    t_indice ind;
    t_clave clavee;
    unsigned registro;
    ind_crear(&ind, sizeof(t_clave), cmpDNI);
    clavee.dni=96;
    ind_insertar(&ind,&clavee,1);
    clavee.dni=87;
    ind_insertar(&ind,&clavee,2);
    clavee.dni=3;
    ind_insertar(&ind,&clavee,3);
    clavee.dni = 45123456;
    ind_insertar(&ind, &clavee, 4);

    clavee.dni = 12987654;
    ind_insertar(&ind, &clavee, 5);

    clavee.dni = 33444555;
    ind_insertar(&ind, &clavee, 6);

    clavee.dni = 52345678;
    ind_insertar(&ind, &clavee, 7);

    clavee.dni = 22111222;
    ind_insertar(&ind, &clavee, 8);

    clavee.dni = 18456123;
    ind_insertar(&ind, &clavee, 9);

    clavee.dni = 40123456;
    ind_insertar(&ind, &clavee, 10);

    clavee.dni = 35888999;
    ind_insertar(&ind, &clavee, 11);

    clavee.dni = 11222333;
    ind_insertar(&ind, &clavee, 12);

    clavee.dni = 49999000;
    ind_insertar(&ind, &clavee, 13);


    ind_recorrer(&ind, verIndice,NULL);


//    clavee.dni=87;
//    printf("Buscando clave %d:\n", clavee.dni);
//    ind_buscar(&ind, &clavee, &registro);
//    printf("%d", registro);
//
//    clavee.dni=96;
//    printf("Buscando clave %d:\n", clavee.dni);
//    ind_buscar(&ind, &clavee, &registro);
//    printf("%d", registro);
//
//    clavee.dni=43;
//    printf("Buscando clave %d:\n", clavee.dni);
//    ind_buscar(&ind, &clavee, &registro);
//    printf("%d", registro);

    ind_vaciar(&ind);
    recorrerInOrden(&ind.raiz_arbol, verClave);

    return 0;
}
