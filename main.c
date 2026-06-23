#include"indice.h"

typedef struct {
    int dia;
    int mes;
    int anio;
} t_fecha;

// 2. Definición de la estructura principal basada en la imagen
typedef struct {
    long dni;                 // DNI (Clave) - Long
    char apellidos[61];       // Apellidos - Cadena (60) + 1 para '\0'
    char nombres[61];         // Nombres - Cadena (60) + 1 para '\0'
    t_fecha fecha_nac;        // Fecha de Nacimiento - T_Fecha
    char sexo;                // Sexo - Char
    t_fecha fecha_afil;       // Fecha de afiliación - T_Fecha
    char categoria[11];       // Categoría - Cadena (10) + 1 para '\0'
    t_fecha fecha_ult_cuota;  // Fecha de última cuota paga - T_Fecha
    char estado;              // Estado - Char
    t_fecha fecha_baja;       // Fecha de Baja - T_Fecha
} t_afiliado;

typedef struct{
        int dni;
}t_clave;

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

int cargar_y_extraer_archivo(const char * path, t_indice * ind)
{
    /// abro el archivo a bajar
    FILE * f_csv = fopen(path, "rt"), f_bin = fopen("socios.dat", "rb");
    if(!f_csv || !f_bin)
    {
        fclose(f_csv);
        return 0;
    }
    t_clave clave;
    t_afiliado info;
    char * p, cadena[600];
    p = fgets(cadena,1,f_csv);
    while(!p)
    {
    /// parseo la clave, lo otro no me importa
        unsigned reg = 1;
        ///sscanf(cadena,"%d,"ñ{-, &clave.dni);
        if(parseo_csv(cadena,&info))
        {
            /// guardo la clave con el nro de reg autogenerado
            ind_insertar(ind, &clave, reg);
            /// guardo en el nuevo arch bin
            fwrite(info,sizeof(t_afiliado),1,f_bin);
        }
        else
            printf("Error en registro\n");
        reg++;
        p = fgets(cadena,1,f_csv);
    }
    return 1;
}


int parseo_cadena(char * cadena, t_afiliado * aux)
{
    int d_nac, m_nac, a_nac;
    int d_afi, m_afi, a_afi;
    int d_cuo, m_cuo, a_cuo;
    int d_baj, m_baj, a_baj;

    int leidos = sscanf(cadena,
        "%ld;%[^;];%[^;];%d/%d/%d; %c ;%d/%d/%d;%[^;];%d/%d/%d; %c ;%d/%d/%d",
        &aux->dni,
        aux->apellidos,
        aux->nombres,
        &d_nac, &m_nac, &a_nac,
        &aux->sexo,
        &d_afi, &m_afi, &a_afi,
        aux->categoria,
        &d_cuo, &m_cuo, &a_cuo,
        &aux->estado,
        &d_baj, &m_baj, &a_baj
    );

    if (leidos != 18)
        return 0;

    aux->fecha_nac.dia = d_nac;   aux->fecha_nac.mes = m_nac;   aux->fecha_nac.anio = a_nac;
    aux->fecha_afil.dia = d_afi;  aux->fecha_afil.mes = m_afi;  aux->fecha_afil.anio = a_afi;
    aux->fecha_ult_cuota.dia = d_cuo; aux->fecha_ult_cuota.mes = m_cuo; aux->fecha_ult_cuota.anio = a_cuo;
    aux->fecha_baja.dia = d_baj;  aux->fecha_baja.mes = m_baj;  aux->fecha_baja.anio = a_baj;

    return 1;
}
int main()
{
    t_indice ind;

    ind_vaciar(&ind);
    recorrerInOrden(&ind.raiz_arbol, verClave);

    return 0;
}

//    t_clave clavee;
//    unsigned registro;
//    ind_crear(&ind, sizeof(t_clave), cmpDNI);
//    clavee.dni=96;
//    ind_insertar(&ind,&clavee,1);
//    clavee.dni=87;
//    ind_insertar(&ind,&clavee,2);
//    clavee.dni=3;
//    ind_insertar(&ind,&clavee,3);
//    clavee.dni = 45123456;
//    ind_insertar(&ind, &clavee, 4);
//
//    clavee.dni = 12987654;
//    ind_insertar(&ind, &clavee, 5);
//
//    clavee.dni = 33444555;
//    ind_insertar(&ind, &clavee, 6);
//
//    clavee.dni = 52345678;
//    ind_insertar(&ind, &clavee, 7);
//
//    clavee.dni = 22111222;
//    ind_insertar(&ind, &clavee, 8);
//
//    clavee.dni = 18456123;
//    ind_insertar(&ind, &clavee, 9);
//
//    clavee.dni = 40123456;
//    ind_insertar(&ind, &clavee, 10);
//
//    clavee.dni = 35888999;
//    ind_insertar(&ind, &clavee, 11);
//
//    clavee.dni = 11222333;
//    ind_insertar(&ind, &clavee, 12);
//
//    clavee.dni = 49999000;
//    ind_insertar(&ind, &clavee, 13);
//
//
//    ind_recorrer(&ind, verIndice,NULL);
//
//
////    clavee.dni=87;
////    printf("Buscando clave %d:\n", clavee.dni);
////    ind_buscar(&ind, &clavee, &registro);
////    printf("%d", registro);
////
////    clavee.dni=96;
////    printf("Buscando clave %d:\n", clavee.dni);
////    ind_buscar(&ind, &clavee, &registro);
////    printf("%d", registro);
////
////    clavee.dni=43;
////    printf("Buscando clave %d:\n", clavee.dni);
////    ind_buscar(&ind, &clavee, &registro);
////    printf("%d", registro);
