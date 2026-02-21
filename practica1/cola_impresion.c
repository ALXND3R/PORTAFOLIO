/*
USO DE MEMORIA ESTATICA (ARRAYS)
NO USAR MALLOC/FREE
CAPACIDAD FIJA DE 10 TRABAJOS

FUNCIONES:

q_init     q_is_empty
q_is_full  q_enqueue
q_dequeue  q_peek
q_print

SI LLENA->NO AGREGA
SI VACIA NO PEEK/DEQUEVE
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct Trabajo
{
    int id;//  NUMERO AUTOINCREMENTAL
    char usuario[32];//NOMBRE DEL USUARIO QUE ENVIO LA IMPRESION
    char documento[42];// TITULO DEL DOCUMENTO
    int total_pgs;// NUMERO TOTAL DE PAGINAS
    int restante_pgs;// PAGINAS RESTANTES POR IMPRIMIR
    int copias;// COPIAS POR IMPRIMIR
    enum prioridad
    {
        NORMAL,
        URGENTE
    }Prioridad;
    enum estado
    {
        EN_COLA,
        IMPRIMIENDO,
        COMPLETADO,
        CANCELADO
    }Estado;

} Trabajo;

typedef struct
{
    Trabajo trabajos[10];
    int frente;
    int final;
    int tamano;

} Cola;


int main()
{


    return 0;
}

void q_init(Cola* cola)
{
    cola->frente=0;
    cola->final=-1;
    cola->tamano=0;
}

int q_is_empty(Cola* cola)
{
    return (cola->tamano==0);
}

int q_is_full(Cola* cola)
{
    return(cola->tamano==10);
}
